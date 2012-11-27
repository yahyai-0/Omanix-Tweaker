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

#include "user-info.h"

UserInfo::UserInfo()
{

	userNameLabel.set_text(_("\tUser Name:\t"));
	homeDirLabel.set_text(_("\tHome Dir:\t\t"));
	shellLabel.set_text(_("\tshell:\t\t\t"));
	langLabel.set_text(_("\tlanguage\t\t"));
		
	userNameDataLabel.set_text(sys.getUserName());
	homeDirDataLabel.set_text(sys.getHomeDir());
	shellDataLabel.set_text(sys.getShell());
	langDataLabel.set_text(sys.getLang());

	try
	{
		image.set("/usr/share/omanix-tweaker/icons/user.png");
	}
	catch(const Glib::Exception& ex)
	{
		cerr<<ex.what() <<endl;
	}

	UserInfoTitle.set_markup(_("<b>  User Information</b>"));

	title.pack_start(UserInfoTitle , Gtk::PACK_SHRINK);
	
	userNameBox.pack_start(userNameLabel,Gtk::PACK_SHRINK);
	userNameBox.pack_start(userNameDataLabel,Gtk::PACK_SHRINK);

	homeDirBox.pack_start(homeDirLabel,Gtk::PACK_SHRINK);
	homeDirBox.pack_start(homeDirDataLabel,Gtk::PACK_SHRINK);

	shellBox.pack_start(shellLabel,Gtk::PACK_SHRINK);
	shellBox.pack_start(shellDataLabel,Gtk::PACK_SHRINK);

	langBox.pack_start(langLabel,Gtk::PACK_SHRINK);
	langBox.pack_start(langDataLabel,Gtk::PACK_SHRINK);

	//labelBox.set_spacing(1);
	labelBox.pack_start(title);
	labelBox.pack_start(userNameBox);
	labelBox.pack_start(homeDirBox);
	labelBox.pack_start(shellBox);
	labelBox.pack_start(langBox);

	imageBox.pack_start(image ,Gtk::PACK_SHRINK);
	mainBox.pack_start(imageBox , Gtk::PACK_SHRINK);
	mainBox.pack_start(labelBox);
	add(mainBox);
}

