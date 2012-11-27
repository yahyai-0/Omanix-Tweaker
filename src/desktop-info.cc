/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * omanix-tweaker
 * Copyright (C)  2012 <ahmed@zero-Studio-XPS-1340>
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

#include "desktop-info.h"

DesktopInfo::DesktopInfo()
{

	ubuntuReleaseLabel.set_text(_("\tubuntu release:\t"));
	kenerlLabel.set_text(_("\tKenerl version:\t"));
	hostNameLabel.set_text(_("\tHost Name:\t\t"));
	uptimeLabel.set_text(_("\tUptime:\t\t"));
	destkopEnvLabel.set_text(_("\tEnviroment:\t\t"));
	paltformLabel.set_text(_("\tPlatform:\t\t\t"));
	
	ubuntuReleaseDataLabel.set_text(sys.getUbuntu());
	kenerlDataLabel.set_text(sys.getKenerl());
	hostNameDataLabel.set_text(sys.getHostName());
	uptimeDataLabel.set_text(sys.getUptime());
	destkopEnvDataLabel.set_text(sys.getDeskEnv());
	paltformDataLabel.set_text(sys.getInstalledPlatform());

	try
	{
		image.set("/usr/share/omanix-tweaker/icons/ubuntu.png");
	}
	catch(const Glib::Exception& ex)
	{
		cerr<<ex.what() <<endl;
	}

	DesktopInfoTitle.set_markup(_("<b>  Desktop Information</b>"));
	
	title.pack_start(DesktopInfoTitle , Gtk::PACK_SHRINK);
	
	ubuntuBox.pack_start(ubuntuReleaseLabel,Gtk::PACK_SHRINK);
	ubuntuBox.pack_start(ubuntuReleaseDataLabel,Gtk::PACK_SHRINK);
	
	kenerlBox.pack_start(kenerlLabel,Gtk::PACK_SHRINK);
	kenerlBox.pack_start(kenerlDataLabel,Gtk::PACK_SHRINK);

	hostNameBox.pack_start(hostNameLabel,Gtk::PACK_SHRINK);
	hostNameBox.pack_start(hostNameDataLabel,Gtk::PACK_SHRINK);

	uptimeBox.pack_start(uptimeLabel,Gtk::PACK_SHRINK);
	uptimeBox.pack_start(uptimeDataLabel,Gtk::PACK_SHRINK);

	desktopEnvBox.pack_start(destkopEnvLabel,Gtk::PACK_SHRINK);
	desktopEnvBox.pack_start(destkopEnvDataLabel,Gtk::PACK_SHRINK);

	platformBox.pack_start(paltformLabel,Gtk::PACK_SHRINK);
	platformBox.pack_start(paltformDataLabel,Gtk::PACK_SHRINK);

	//labelBox.set_spacing(3);
	labelBox.pack_start(title);
	labelBox.pack_start(hostNameBox);
	labelBox.pack_start(ubuntuBox);
	labelBox.pack_start(kenerlBox);
	labelBox.pack_start(desktopEnvBox);
	labelBox.pack_start(platformBox);
	labelBox.pack_start(uptimeBox);

	imageBox.pack_start(image ,Gtk::PACK_SHRINK);
	mainBox.pack_start(imageBox , Gtk::PACK_SHRINK);
	mainBox.pack_start(labelBox);
	add(mainBox);
}

