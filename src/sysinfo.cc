/*
 * Ahmed Al-Yahyai
 * blackheart10001@gmail.com
 * 
omanix-tweaker is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * omanix-tweaker is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */


//// most of the algorithm are form -SysInfo program- but I modifed it to C++ way //////
#include "sysinfo.h"


Sysinfo::Sysinfo()
{
	line="";
}

Glib::ustring Sysinfo::getNumOfCPU()
{
	fin.open("/proc/cpuinfo");
	if(fin.is_open())
	{
		while (!fin.eof()) 
		{
			getline(fin,line);
			string::size_type index = line.find( "cpu cores" );
			if( index != string::npos )
			{
				line.erase(0, 12);
				break;
			}
		} 
	}
	else
		line="UNKNOWN";

	fin.close();
	return line;
}

Glib::ustring Sysinfo::getCPUModel()
{
	fin.open("/proc/cpuinfo");
	if(fin.is_open())
	{
		while (!fin.eof()) 
		{
			getline(fin,line);
			string::size_type index = line.find( "model name" );
			if( index != string::npos )
			{
				line.erase(0, 13);
				break;
			}
		}
	}
	else
		line="UNKNOWN";

	fin.close();
	return line;
}

Glib::ustring Sysinfo::getMemory()
{
	fin.open("/proc/meminfo");
	if(fin.is_open())
	{
		while (!fin.eof()) 
		{
			getline(fin,line);
			string::size_type index = line.find( "MemTotal" );
			if( index != string::npos )
			{
				size_t pos = line.find('K');
				if( pos != std::string::npos)
					line = line.substr(0,pos);
				line.erase(0, 17);
				float numbers= atoi(line.c_str());
				numbers = numbers/1048576;
				line=StringFrom(numbers);
				line = line.substr(0, line.size()-4);
				break;
			}
		}
	}
	else
		line="UNKNOWN";

	fin.close();
	return line;
}

Glib::ustring Sysinfo::getProcessorType()
{
	FILE* pipe = popen("uname -p", "r");
    if (!pipe) 
		return "UNKNOWN";

	char buffer[128];
	line="";
    while(!feof(pipe)) 
	{
        if(fgets(buffer, 128, pipe) != NULL)
                line += buffer;
    }
    pclose(pipe);
    return line;

}

Glib::ustring Sysinfo::getUbuntu()
{
	fin.open("/etc/lsb-release");
	if(fin.is_open())
	{
		while (!fin.eof()) 
		{
			getline(fin,line);
			string::size_type index = line.find( "DISTRIB_DESCRIPTION" );
			if( index != string::npos )
			{
				line.erase(0, 20);
				break;
			}
		}
	}
	else
		line="UNKNOWN";
	
	fin.close();
	return line;
	
}

Glib::ustring Sysinfo::getKenerl()
{
	fin.open("/proc/sys/kernel/osrelease");
	
	if(fin.is_open())
		getline(fin,line);
	else
		line="UNKNOWN";
	
	fin.close();
	return line;
}

Glib::ustring Sysinfo::getHostName()
{
	fin.open("/proc/sys/kernel/hostname");
	
	if(fin.is_open())
		getline(fin,line);
	else
		line="UNKNOWN";
	
	fin.close();
	return line;
	
}
Glib::ustring Sysinfo::getUptime()
{
	fin.open("/proc/uptime");
	if(fin.is_open())
	{
		getline(fin,line);
	
		int dayTime= atoi(line.c_str());
		dayTime = dayTime/86400;

		int hourTime= atoi(line.c_str());
		hourTime = (hourTime/3600) - (dayTime * 24);

		int minTime = atoi(line.c_str());
		minTime = (minTime/60) - ((dayTime * 1440) + (hourTime * 60));

		line = (StringFrom(dayTime)+" day "+StringFrom(hourTime)+" hours "+StringFrom(minTime)+" minutes ");
	}
	else
		return line="UNKNOWN";
	
	fin.close();
	return line;
}

Glib::ustring Sysinfo::getInstalledPlatform()
{
	FILE* pipe = popen("uname -i", "r");
    if (!pipe) 
		return "UNKNOWN";

	char buffer[128];
	line="";
    while(!feof(pipe)) 
	{
        if(fgets(buffer, 128, pipe) != NULL)
                line += buffer;
    }
    pclose(pipe);
    return line;

}

Glib::ustring Sysinfo::getDeskEnv()
{
	return getenv("XDG_CURRENT_DESKTOP");
}
Glib::ustring Sysinfo::getUserName()
{
	return getenv("USER");
}

Glib::ustring Sysinfo::getHomeDir()
{
	return getenv("HOME");
}

Glib::ustring Sysinfo::getShell()
{
	return getenv("SHELL");
}

Glib::ustring Sysinfo::getLang()
{
	return getenv("LANG");
}
