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

#ifndef _USER_INFO_H_
#define _USER_INFO_H_

#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include "sysinfo.h"

class UserInfo: public Gtk::VBox 
{
public:
	UserInfo();
	~UserInfo(){};

protected:
	Gtk::Image image;
	Gtk::VBox imageBox ,labelBox;	
	Gtk::HBox mainBox ,title ,userNameBox ,homeDirBox ,shellBox ,langBox;
	Gtk::Label UserInfoTitle ,userNameLabel ,userNameDataLabel
				,homeDirLabel ,homeDirDataLabel
				,shellLabel ,shellDataLabel
				,langLabel ,langDataLabel;
	Sysinfo sys;
};

#endif // _USER_INFO_H_
