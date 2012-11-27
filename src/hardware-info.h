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

#ifndef _HARDWARE_INFO_H_
#define _HARDWARE_INFO_H_

#include <gtkmm/label.h>
#include <gtkmm/box.h>
#include <gtkmm/image.h>
#include "sysinfo.h"

class HardwareInfo: public Gtk::VBox 
{
public:
	HardwareInfo();
	virtual ~HardwareInfo(){};

protected:
	Gtk::Image image;
	Gtk::VBox imageBox ,labelBox;	
	Gtk::HBox   mainBox, title ,cpuModelBox ,memoryBox ,processorBox ,cpuCoresBox;
	Gtk::Label hardwareInfoTitle ,cpuModelLabel ,cpuModelDataLabel
				,memoryLabel ,memoryDataLabel
				,cpuCoresLabel ,cpuCoresDataLabel
				,processorTypeLabel ,processorTypeDataLabel;
	Sysinfo sys;
};

#endif // _HARDWARE_INFO_H_
