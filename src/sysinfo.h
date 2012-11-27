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

#ifndef _SYSINFO_H_
#define _SYSINFO_H_

#include <fstream>
#include <glibmm/i18n.h>
#include <glibmm/ustring.h>
#include "stringformat.h"
using namespace std;

class Sysinfo
{
public:
	Sysinfo();
	~Sysinfo(){};
	
	//hardware
	Glib::ustring getNumOfCPU();
	Glib::ustring getCPUModel();
	Glib::ustring getMemory();
	Glib::ustring getProcessorType();
	
	//Desktop information
	Glib::ustring getUbuntu();
	Glib::ustring getKenerl();
	Glib::ustring getHostName();
	Glib::ustring getUptime();
	Glib::ustring getDeskEnv();
	Glib::ustring getInstalledPlatform();
	
	//User information
	Glib::ustring getUserName();
	Glib::ustring getHomeDir();
	Glib::ustring getShell();
	Glib::ustring getLang();

private:
	ifstream fin;
	string line;
};

#endif // _SYSINFO_H_
