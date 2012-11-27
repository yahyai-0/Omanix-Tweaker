/*
 * Ahmed Al-Yahyai
 * blackheart10001@gmail.com
 * 
 * Omanix Tweaker is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * Omanix Tweaker is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "app.h"
#include <unistd.h>
#include <stdlib.h>
#include <sys/wait.h>
#include <cstdio>
#include <sstream>



App::App() :urls()
{
	
	client = Gnome::Conf::Client::get_default_client();
	
	#ifdef GLIBMM_EXCEPTIONS_ENABLED
	client->add_dir("/apps/omanix-tweaker");
	#else
	std::auto_ptr<Glib::Error> error;
	client->add_dir("/apps/omanix-tweaker", Gnome::Conf::CLIENT_PRELOAD_NONE, error);
	if(error.get())
		std::cerr << error->what() << std::endl;
	#endif //GLIBMM_EXCEPTIONS_ENABLED
		
	creatProgDir();
	serverPkgVer=1;
	numOfUrls=0;
	db=new SQLiteDB;
	
}

App::~App()
{
	delete [] urls;
	delete db;
}

guint App::getClientPkgVer()
{
	guint tmp;
	string path=ProgDir+"/clientPkgVer";
	cerr<<path;
	ifstream fin(path.c_str() , ios::binary);
	if(!fin.is_open())
	{
		cerr<<"Error: Cant open clientPkgVer file\n";
		cerr<<"Recreating the file with PkgVer=0\n";
		fin.close();
		setClientPkgVer (0);
		fin.open(path.c_str() , ios::binary);
	}
	fin.read(reinterpret_cast<char*>(&tmp),sizeof(tmp));
	fin.close();
	return tmp;
}

void App::setClientPkgVer(guint PkgVer)
{
	cerr<<PkgVer;
	string path=ProgDir+"/clientPkgVer";
	ofstream ofs(path.c_str() , ios::binary);
	ofs.write(reinterpret_cast<const char*>(&PkgVer),sizeof(PkgVer));
	ofs.close();
}

guint App::getServerPkgVer()
{
	downloadList("http://sourceforge.net/projects/omanix/files/omanix-tweaker/serverPkgVer.txt/download" , 1);	
	return serverPkgVer;	
}

void App::downloadList(string url , guint Method)
{
	SoupSession *session;
	SoupMessage *msg;
	
	session = soup_session_async_new_with_options(SOUP_SESSION_ADD_FEATURE_BY_TYPE, SOUP_TYPE_GNOME_FEATURES_2_26, NULL);
	msg = soup_message_new (SOUP_METHOD_GET, url.c_str());
	soup_session_send_message (session ,msg);

	if ( SOUP_STATUS_IS_SUCCESSFUL (msg->status_code))
	{
		if(Method==0)
		{
			string path =  ProgDir + "/tmp.list";
			ofstream ofs;

			if((db->open(ProgDir+"/tweak.list")))
			{
				
				ofs.open(path.c_str());
				ofs.write(msg->response_body->data ,msg->response_body->length);
				ofs.close();
				db->query("attach '"+ path+"' as db2");
				db->query("insert into tweaktable select * from db2.tweaktable where ID NOT IN (select tweaktable.ID From tweaktable) ;");
				db->query("detach database db2;");
				db->finalize();
				db->close();
				if(remove(path.c_str()) != 0 )
					cerr<<"Error deleting the temp.list\n";	
			 }
			 else
			 {
				path=ProgDir+"/tweak.list";
				ofs.open(path.c_str());
				ofs.write(msg->response_body->data ,msg->response_body->length);
				ofs.close();
			 }
		}
		
		else if(Method==1)
			serverPkgVer=atoi(msg->response_body->data);
	}
}
	
void App::downloadTweakList()
{		
	downloadList("http://sourceforge.net/projects/omanix/files/omanix-tweaker/tweak.list/download" , 0);         
}

void App::creatProgDir()
{
	struct passwd *pw = getpwuid(getuid());
	const string homedir = pw->pw_dir;
	
	string dir =homedir+"/.omanix_tweaker";
 
	if(!db->exists(dir))
	{
		if(mkdir(dir.c_str(),S_IRWXU | S_IRWXG | S_IRWXO)==-1)//creating a directory
		    cerr<<"Error : creating .tweaker dir \n";
	}
	
	dir = homedir+"/.omanix_tweaker/packages";
	if(!db->exists(dir))
	{
		if(mkdir(dir.c_str(),S_IRWXU | S_IRWXG | S_IRWXO)==-1)//creating a directory
      		cerr<<"Error : creating .tweaker/packages \n";
	}
	
	ProgDir = homedir + "/.omanix_tweaker";
	client->set("/apps/omanix-tweaker/ProgDir",ProgDir);
	cerr<<"program dir :"<<ProgDir<<endl;

}


Url* App::getURLS(guint SPkgVer , guint CPkgVer)
{
	numOfUrls=SPkgVer -CPkgVer;
	
	if (CPkgVer>SPkgVer)
		numOfUrls=0;
	
	int tmp=0;
	string pkgNum="0";
	urls=new Url[numOfUrls];
	string pkgUrl="http://sourceforge.net/projects/omanix/files/omanix-tweaker/";
		
	//debuging
	cerr<<"last update version: "<<CPkgVer<<endl;
	cerr<<"available update version: "<<SPkgVer<<endl;
	cerr<<"number of pkg that will be download: "<<numOfUrls<<endl;
	//
	for(int i=CPkgVer; i<SPkgVer; i++)
	{
		tmp=i+1;
		pkgNum=StringFrom(tmp);
		urls[i].pkgName=pkgNum+".tar";
		urls[i].url = (pkgUrl+(urls[i].pkgName)+"/download");
		
	}
	//debuging
	for(int i=0; i<numOfUrls; i++)
		cerr<<"pkg Urls that will be download:\n"<<urls[i].url<<endl;
	return urls;
}
void App::downloadPkg(Url* urls , Gtk::ProgressBar &P)
{
	SoupSession *session;
	SoupMessage *msg;
	ofstream ofs;

	string path ,tmp=ProgDir+"/packages/";
	
	guint tmpClientVer=0;
	float value=0.0;
	P.set_fraction(0.0);
	
	session = soup_session_async_new_with_options(SOUP_SESSION_ADD_FEATURE_BY_TYPE, SOUP_TYPE_GNOME_FEATURES_2_26, NULL);

	for(int i=0; i<numOfUrls; i++)
	{
		path=ProgDir+"/"+urls[i].pkgName ;
		
		
		msg = soup_message_new (SOUP_METHOD_GET, urls[i].url.c_str());
		soup_session_send_message (session ,msg);
		if ( SOUP_STATUS_IS_SUCCESSFUL (msg->status_code))
		{	
			ofs.open(path.c_str());
			ofs.write(msg->response_body->data ,msg->response_body->length);
			ofs.close();
			extract(path ,tmp);
			if(remove(path.c_str()) != 0 )
				cerr<<"\nError deleting "<< path<<endl;	
			value=1+i;
 			P.set_fraction(value/numOfUrls);
		}
	}
	
	if (value !=0.0)
	{
		setClientPkgVer(static_cast<guint>(value));
	}
}

void App::loadTweakList(Glib::RefPtr<Gtk::ListStore> &refTreeModel , ModelColumnsTweak &col ,Gtk::InfoBar &infobar , Gtk::Label &labe1)
{	
	refTreeModel->clear();
	if(db->open(ProgDir+"/tweak.list")==true)
	{
		vector<string> record = db->query("SELECT * FROM tweaktable;");
	
		while(db->getRC()!=SQLITE_DONE)
		{	
			Gtk::TreeModel::Row row = *(refTreeModel->append());
			row[col.tweak_id]=record.at(0);
			row[col.tweak_pkgVer]=record.at(1);
			row[col.tweak_name]=record.at(2);
			row[col.tweak_type]=record.at(3);
			row[col.tweak_distro]=record.at(4);
			row.set_value(col.tweak_status,(Glib::ustring)record.at(5));
			record = db->nextRecord();
		}
		db->finalize();
		db->close();
	}
	else
	{
		infobar.set_message_type (Gtk::MESSAGE_ERROR );
		labe1.set_markup(_("<b><span foreground='#C4C4C4'>can't load list,,click Update on the Tweaker tab</span></b>"));
		infobar.show(); 
	}
	
}

string App::getPkgPath(Gtk::TreeModel::iterator &iter , ModelColumnsTweak &col , string command) const
{
	string path = ProgDir+"/packages/";
	Gtk::TreeModel::Row row = *iter;
	path +=(StringFrom(row[col.tweak_id]))+"/"+command;
	return path;
	
}

int App::extract(string tarfile , string rootDir)
{
	TAR *t;
	
	cerr<<"opening tarfile...\n";
	if (tar_open(&t, &tarfile[0], NULL, O_RDONLY, 0,0)== -1)
	{
		cerr<<"Error: tar_open(): "<<strerror(errno)<<endl;
		return -1;
	}

	cerr<<"extracting tarfile...\n";
	if (tar_extract_all(t, &rootDir[0])!=0)
	{
		cerr<<"Error: tar_extract(): "<<strerror(errno)<<endl;
		return -1;
	}

	cerr<<"closing tarfile...\n";
	if (tar_close(t) != 0)
	{
		cerr<<"Error: tar_close(): "<<strerror(errno)<<endl;
		return -1;
	}

	return 0;

}

int App::SH(string path )
{
	int status;
	pid_t childPid;

	switch (childPid=fork())
	{
		case -1:
			cerr<<"Error forking in sh() function\n";
			break;
		case 0:
			execl("/bin/sh","sh" , path.c_str() ,(char *)NULL);
			cerr<<"Error installing/removing tweak\n";
			_exit(127);
			
		default:
			if (waitpid(childPid , &status , 0)==-1)
			{
				cerr<<"waitpid return -1\n";
				return -1;
				break;
			}
			else 
			{
				cerr<<"The child exist with "<<status<<endl;
				return status;
			}
	}
}

void App::setLang(Glib::ustring lang)
{
	setenv("LANGUAGE" , lang.c_str() , TRUE);
	client->set("/apps/omanix-tweaker/language",lang);
}

Glib::ustring App::getLang() const
{
	//char *lang = getenv("LANGUAGE");
	//string language(lang);
	return  client->get_string("/apps/omanix-tweaker/language");
}

string App::getTweakStatus(string ID)
{
	string sql="SELECT Status FROM tweaktable WHERE ID="+ID+";";
	db->open(ProgDir+"/tweak.list");
	vector<string> result = db->query(sql);
	db->finalize();
	db->close();
	return (result.at(0));
}

void App::setTweakStatus(string stat , string ID)
{
	string sql="UPDATE tweaktable SET Status="+stat+" WHERE ID="+ID+";";
	db->open(ProgDir+"/tweak.list");
	db->query(sql);
	db->finalize();
	db->close();
}

