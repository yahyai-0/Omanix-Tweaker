/*
 * Ahmed Al-Yahyai
 * blackheart10001@gmail.com
 * 
 * Omanix is free software: you can redistribute it and/or modify it
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

#include "mywindow.h"


using namespace std;

MyWindow::MyWindow()
{
	
	//window properties
	set_title(_("Omanix Tweaker"));
	set_position(Gtk::WIN_POS_CENTER_ALWAYS);
	set_resizable (false);
	set_size_request(700,500); 
	main_box.set_spacing (3);
	gray.set_hsv (1.90, 0.10, 0.30);
	buttonGray.set_hsv (2, 0.10, 0.23);
	Gdk::Color lightGray("gray");
	modify_bg(Gtk::STATE_NORMAL, gray);
	Gtk::IconSize iconSize(5);
	register_stock_items();
	
	//set program language
	
	app.setLang (app.getLang());
		
	//set program icon
	try
	{
		ProgIcon = Gdk::Pixbuf::create_from_file("/usr/share/omanix-tweaker/icons/OmanixTweaker.svg");
		set_icon(ProgIcon);
		omanixTweakerImg.set(ProgIcon);
	}
	catch(const Glib::Exception& ex)
	{
		cerr<<ex.what() <<endl;
	}
	
	mainButtonLabel.set_markup(_("<span foreground='white'>Main</span>"));
	tweakerButtonLabel.set_markup(_("<span foreground='white'>Tweaker</span>"));
	settingButtonLabel.set_markup(_("<span foreground='white'>Setting</span>"));
	mainButton.modify_bg(Gtk::STATE_NORMAL, buttonGray);	
	tweakerButton.modify_bg(Gtk::STATE_NORMAL, buttonGray);
	settingButton.modify_bg(Gtk::STATE_NORMAL, buttonGray);
	mainButton.add(mainButtonLabel);
	tweakerButton.add(tweakerButtonLabel);
	settingButton.add(settingButtonLabel);

	aboutButtonImg.set(Gtk::StockID ("stock_about"),iconSize);
	aboutButton.add(aboutButtonImg);
	//splashLabel.set_markup(_("<b><span foreground='white' size='30000'> Omanix Tweaker</span></b>"));

	try
	{
		omanixTweakerImg.set("/usr/share/omanix-tweaker/icons/OmanixTweaker.svg");
	}
	catch(const Glib::Exception& ex)
	{
		cerr<<ex.what() <<endl;
	}

	
	add(main_box);
	noteBook.set_show_tabs(false);
	welcomNoteBox.set_spacing(30);
	DesktopUserInfoBox.set_spacing(6);
	DesktopUserInfoBox.pack_start(desktopInfo );
	DesktopUserInfoBox.pack_start(userInfo );
	welcomNoteBox.pack_start(hardwareInfo);
	welcomNoteBox.pack_start(DesktopUserInfoBox);
	
	welcomeIndex= noteBook.append_page(welcomNoteBox , "Main");
	tweakerIndex= noteBook.append_page(tweakerNoteBox , "Tweaker");
	settingIndex= noteBook.append_page(settingNoteBox , "Setting");
	
	noteButtonBox.set_spacing(1);
	noteButtonBox.set_layout(Gtk::BUTTONBOX_CENTER);
	noteButtonBox.add(mainButton);
	noteButtonBox.add(tweakerButton);
	noteButtonBox.add(settingButton);
	
	mainButton.signal_clicked().connect(sigc::mem_fun(*this,&MyWindow::on_mainB_clicked));
	tweakerButton.signal_clicked().connect(sigc::mem_fun(*this,&MyWindow::on_tweakerB_clicked));
	settingButton.signal_clicked().connect(sigc::mem_fun(*this,&MyWindow::on_settingB_clicked));
	aboutButton.signal_clicked().connect(sigc::mem_fun(*this , &MyWindow::on_about_clicked));

	Gtk::Alignment *al1 = Gtk::manage(new Gtk::Alignment());
	al1->set_size_request(200, 2);	
	
	toolbarBox.pack_start(*al1, Gtk::PACK_SHRINK);
	toolbarBox.pack_start(toolbar ,Gtk::PACK_EXPAND_WIDGET);
	
	noteButtonBox.set_layout(Gtk::BUTTONBOX_CENTER);
	tweakerNoteBox.pack_start(toolbarBox ,Gtk::PACK_SHRINK );	
	
	toolbar.append(toolb_update);
	toolbar.append(toolb_install);
	toolbar.append(toolb_remove);
	toolbar.append(toolb_description);
	toolbar.set_toolbar_style ( Gtk::TOOLBAR_BOTH ); 
	toolbar.set_icon_size (Gtk::IconSize (6));

	//packing and toolbar properties
	toolb_update.set_stock_id(Gtk::StockID ("stock_update"));
	toolb_install.set_stock_id(Gtk::StockID ("stock_install"));
	toolb_remove.set_stock_id(Gtk::StockID ("stock_remove"));
	toolb_description.set_stock_id(Gtk::StockID("stock_description"));

	toolb_update.signal_clicked().connect(sigc::mem_fun(*this,&MyWindow::on_update_clicked));
	toolb_install.signal_clicked().connect(sigc::mem_fun(*this,&MyWindow::on_install_clicked));
	toolb_remove.signal_clicked().connect(sigc::mem_fun(*this,&MyWindow::on_remove_clicked));
	toolb_description.signal_clicked().connect(sigc::mem_fun(*this,&MyWindow::on_info_clicked));

	TweakerIconBox.pack_start(omanixTweakerImg);
	buttonBox.pack_start(noteButtonBox);
	buttonBox.pack_end(aboutButton ,Gtk::PACK_SHRINK);
	splashBox.pack_start(TweakerIconBox);
	splashBox.pack_start(buttonBox ,Gtk::PACK_SHRINK);
	main_box.pack_start(splashBox , Gtk::PACK_SHRINK);
	main_box.pack_start(noteBook, Gtk::PACK_EXPAND_WIDGET);

	
	//TREEVIEW 
	scrolled_treeView.add(treeView);
	scrolled_treeView.set_policy(Gtk::POLICY_AUTOMATIC,Gtk::POLICY_AUTOMATIC);
    tweakerNoteBox.pack_start(scrolled_treeView );
	refTreeModel = Gtk::ListStore::create(col);
    treeView.set_model(refTreeModel);
	treeView.append_column(_("Tweak ID"), col.tweak_id);
	treeView.append_column(_("Tweak Type"), col.tweak_type);
	treeView.append_column(_("Tweak Name"), col.tweak_name);
	treeView.append_column(_("Tweak Distro"), col.tweak_distro);
	int numCols=treeView.append_column(_("Tweak status"), pixBufRenderer);
	 //col.tweak_status
	treeView.get_column(numCols-1)->add_attribute(pixBufRenderer,"stock-id",col.tweak_status);
	refTreeSelection =treeView.get_selection();


	////
	Gtk::MenuItem* item = Gtk::manage(new Gtk::MenuItem(_("Install")));
  	item->signal_activate().connect(sigc::mem_fun(*this, &MyWindow::on_install_clicked));
 	popupMenu.append(*item);

	item = Gtk::manage(new Gtk::MenuItem(_("Remove")));
  	item->signal_activate().connect(sigc::mem_fun(*this, &MyWindow::on_remove_clicked));
 	popupMenu.append(*item);

	item = Gtk::manage(new Gtk::MenuItem(_("Description")));
  	item->signal_activate().connect(sigc::mem_fun(*this, &MyWindow::on_info_clicked));
 	popupMenu.append(*item);
	popupMenu.accelerate(*this);
	popupMenu.show_all();

	treeView.signal_button_press_event().connect(sigc::mem_fun(*this, &MyWindow::on_treeView_press_event), false);


	Gtk::Container* progressBARContainer =
    dynamic_cast<Gtk::Container*>(progressBAR.get_content_area());
	if (progressBARContainer)
	{
		progressBARContainer->add(ProgressBar1);
	}
	progressBAR.add_button(Gtk::Stock::OK, 0);
	main_box.pack_start(progressBAR, Gtk::PACK_SHRINK);
	progressBAR.signal_response().connect(sigc::mem_fun(*this,&MyWindow::on_progressbar_button_respone));
	progressBAR.set_message_type (Gtk::MESSAGE_OTHER );
	
	//infobar1
	Gtk::Container* infobarContainer =
    dynamic_cast<Gtk::Container*>(infobar.get_content_area());
	if (infobarContainer)
	{
		infobarContainer->add(infobar_label);	

	}
    infobar.add_button(Gtk::Stock::OK, 0);
	main_box.pack_start(infobar, Gtk::PACK_SHRINK);
	infobar.signal_response().connect(sigc::mem_fun(*this,&MyWindow::on_infobar_button_respone));
	infobar.set_message_type (Gtk::MESSAGE_OTHER );

	//app.client->notify_add("/apps/tweaker/proxy",sigc::mem_fun(*this, &MyWindow::proxy_key_changed));

	//show widgets
	show_all_children();
	progressBAR.hide();
	infobar.hide();
	
	refTreeModel->clear();
	app.loadTweakList (refTreeModel,col ,infobar ,infobar_label );
}

MyWindow::~MyWindow()
{
}

void MyWindow::on_mainB_clicked()
{
	noteBook.set_current_page(welcomeIndex);
}

void MyWindow::on_tweakerB_clicked()
{
	noteBook.set_current_page(tweakerIndex);
}

void MyWindow::on_settingB_clicked()
{
	noteBook.set_current_page(settingIndex);
}

bool MyWindow::on_treeView_press_event(GdkEventButton* event)
{
  bool rv = false;

  //Call base class, to allow normal handling,
  //such as allowing the row to be selected by the right-click:
  rv = MyWindow::on_button_press_event(event);
  //Then do our custom stuff:
  if( (event->type == GDK_BUTTON_PRESS) && (event->button == 3) )
  {
   popupMenu.popup(event->button, event->time);
  }

  return rv;
}
/*void MyWindow::proxy_key_changed(guint connection_id, Gnome::Conf::Entry entry)
{
	if (entry.get_value().get_type() == Gnome::Conf::VALUE_STRING)
	{
		proxyBarLabel.set_text(entry.get_value().get_string());
	}
}*/

void MyWindow::on_update_clicked()
{
		progressBAR.show();
		app.downloadPkg(app.getURLS(app.getServerPkgVer() , app.getClientPkgVer()) , ProgressBar1);
		app.downloadTweakList();
		app.loadTweakList (refTreeModel,col ,infobar ,infobar_label);
		infobar.set_message_type (Gtk::MESSAGE_OTHER );
		infobar_label.set_markup(_("<b><span foreground='#C4C4C4'> The list has been updated</span></b>"));
		infobar.show();
}

void MyWindow::on_install_clicked()
{
			
	Glib::ustring path , ID;
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if(iter) //If anything is selected
	{
		Gtk::TreeModel::Row row = *iter;
		ID=row[col.tweak_id];
		path=app.getPkgPath(iter ,col , "install");
		string tmpStat=app.getTweakStatus(ID);
		
		if (tmpStat=="gtk-no")
		{
			if (app.SH(path)==0)
			{
				app.setTweakStatus("'gtk-yes'",ID);
				app.loadTweakList (refTreeModel,col ,infobar ,infobar_label);
				infobar.set_message_type (Gtk::MESSAGE_OTHER );
				infobar_label.set_markup(_("<b><span foreground='#C4C4C4'>The tweak has been installed</span></b>"));
				infobar.show();
			}
			else
			{
				infobar.set_message_type (Gtk::MESSAGE_ERROR );
				infobar_label.set_markup(_("<b><span foreground='#C4C4C4'>There is error when installing the tweak</span></b>"));
				infobar.show();
			}
		}
		else
		{
			infobar.set_message_type (Gtk::MESSAGE_ERROR );
			infobar_label.set_markup(_("<b><span foreground='#C4C4C4'>The tweak is installed</span></b>"));
			infobar.show();
		}
	}
	else
	{
		infobar.set_message_type (Gtk::MESSAGE_ERROR );
		infobar_label.set_markup(_("<b><span foreground='#C4C4C4'>Select any tweak to install</span></b>"));
		infobar.show();
	}

}

void MyWindow::on_remove_clicked ()
{
	Glib::ustring path , ID;
	
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if(iter) //If anything is selected
	{
		Gtk::TreeModel::Row row = *iter;
		ID=row[col.tweak_id];
		path=app.getPkgPath(iter ,col , "remove");
		string tmpStat=app.getTweakStatus(ID);
		
		if (tmpStat=="gtk-yes")
		{
			if (app.SH(path)==0)
			{
				app.setTweakStatus("'gtk-no'" , ID);
				app.loadTweakList (refTreeModel,col ,infobar ,infobar_label);
				infobar.set_message_type (Gtk::MESSAGE_OTHER );
				infobar_label.set_markup(_("<b><span foreground='#C4C4C4'>The tweak has been removed</span></b>"));
				infobar.show();
			}
			else
			{
				infobar.set_message_type (Gtk::MESSAGE_ERROR );
				infobar_label.set_markup(_("<b><span foreground='#C4C4C4'>There is error when removing the tweak</span></b>"));
				infobar.show();
			}
		}
		else
		{
			infobar.set_message_type (Gtk::MESSAGE_ERROR );
			infobar_label.set_markup(_("<b><span foreground='#C4C4C4'>The Tweak is not installed</span></b>"));
			infobar.show();
		}
	}
			
	else
	{
		infobar.set_message_type (Gtk::MESSAGE_ERROR );
		infobar_label.set_markup(_("<b><span foreground='#C4C4C4'>Select any tweak to remove it</span></b>"));
		infobar.show();
	}
}

void MyWindow::on_info_clicked()
{
	string path;
	stringstream buffer;
	ifstream fin;
	
	Gtk::TreeModel::iterator iter = refTreeSelection->get_selected();
	if(iter) //If anything is selected
	{
	  	
		if(app.getLang()=="ar")
			{
				path=app.getPkgPath(iter ,col , "info.ar");
				fin.open(path.c_str());
			}
		if (app.getLang()=="en" || !fin.is_open())
		{
			path=app.getPkgPath(iter ,col , "info.en");
			cerr<<endl<<path<<endl;
			fin.open(path.c_str());
		}
		
		buffer << fin.rdbuf();
		infobar.set_message_type (Gtk::MESSAGE_OTHER );
		infobar_label.set_markup("<span foreground='#C4C4C4'>"+buffer.str()+"</span>");
		infobar.show();
	}else
	{
		infobar.set_message_type (Gtk::MESSAGE_ERROR );
		infobar_label.set_markup(_("<b><span foreground='#C4C4C4'>Select any tweak to view its description</span></b>"));
		infobar.show();
	}
		
	

}
void MyWindow::on_language_clicked()
{	
	string::size_type index = (app.getLang()).find( "en" );
	if( index != string::npos )
		app.setLang("ar");
	else
		app.setLang("en");
	
	infobar.set_message_type (Gtk::MESSAGE_OTHER );
	infobar_label.set_markup(_("<b><span foreground='#C4C4C4'>قم بإعادة تشغيل البرنامج</span></b>"));
	infobar.show();
}

void MyWindow::on_about_clicked()
{
	infobar.set_message_type (Gtk::MESSAGE_OTHER );
	infobar_label.set_markup(_("<b><span foreground='#C4C4C4'>\tThis program come under GPL3. Thanks for all who support me \n\n\t\t\t\t\tAhmed Said Al-Yahyai\n\t\t\t\t\tblackheart10001@gmail.com\n\n\t\t\t\t\t\t\tCredit:\n\t\t\t\t\t\tSaid Al Ramdhani\n\t\t\t\t\tdarknesscore0@gmail.com</span></b>"));
	infobar.show();
	
}

void MyWindow::on_progressbar_button_respone(int response)
{
	progressBAR.hide();
}
	
void MyWindow::on_infobar_button_respone (int)
{
  // Clear the message and hide the info bar:
	infobar.set_message_type (Gtk::MESSAGE_OTHER );
	infobar_label.set_text("");
	infobar.hide();
}

void MyWindow::add_stock_item(
        const Glib::RefPtr<Gtk::IconFactory>& factory,
        const std::string& filepath,
        const Glib::ustring& id, const Glib::ustring& label)
{
	Gtk::IconSource source;

  #ifdef GLIBMM_EXCEPTIONS_ENABLED
  try
  {
    source.set_pixbuf( Gdk::Pixbuf::create_from_file(filepath) );
  }
  catch(const Glib::Exception& ex)
  {
    std::cout << ex.what() << std::endl;
  }
  #else
  std::auto_ptr<Glib::Error> ex;
  source.set_pixbuf( Gdk::Pixbuf::create_from_file(filepath, ex) );

  if(ex.get())
  {
    std::cerr <<  ex->what();
  }

  #endif //GLIBMM_EXCEPTIONS_ENABLED

  //source.set_size(Gtk::ICON_SIZE_SMALL_TOOLBAR);
 // source.set_size_wildcarded(); //Icon may be scaled.

  Gtk::IconSet icon_set;
  icon_set.add_source(source); //More than one source per set is allowed.

  const Gtk::StockID stock_id(id);
  factory->add(stock_id, icon_set);
  Gtk::Stock::add(Gtk::StockItem(stock_id, label));

}
void MyWindow::register_stock_items ()
{
  Glib::RefPtr<Gtk::IconFactory> factory = Gtk::IconFactory::create();
  //add_stock_item(factory, "icons/noicon.png", "stock_noicon", "noicon");
  add_stock_item(factory, "/usr/share/omanix-tweaker/icons/install.png", "stock_install", _("Install"));
  add_stock_item(factory, "/usr/share/omanix-tweaker/icons/update.png", "stock_update", _("Update"));
  add_stock_item(factory, "/usr/share/omanix-tweaker/icons/remove.png", "stock_remove", _("Remove"));
  add_stock_item(factory, "/usr/share/omanix-tweaker/icons/info.png", "stock_description",_("Description"));
	add_stock_item(factory, "/usr/share/omanix-tweaker/icons/about.png", "stock_about",_("About"));
  factory->add_default(); //Add factory to list of factories.
}
