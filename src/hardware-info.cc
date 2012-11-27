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

#include "hardware-info.h"

HardwareInfo::HardwareInfo()
{

	cpuModelLabel.set_label(_("\tCPU Model:\t"));
	memoryLabel.set_label(_("\tMemory:\t\t"));
	processorTypeLabel.set_label("\tProcessor:\t");
	cpuCoresLabel.set_label(_("\tCPU Cores\t"));
		
	cpuModelDataLabel.set_text(sys.getCPUModel());
	memoryDataLabel.set_text(sys.getMemory() + "GB");
	cpuCoresDataLabel.set_text(sys.getNumOfCPU());
	processorTypeDataLabel.set_text(sys.getProcessorType());

	try
	{
		image.set("/usr/share/omanix-tweaker/icons/hardware.png");
	}
	catch(const Glib::Exception& ex)
	{
		cerr<<ex.what() <<endl;
	}

	hardwareInfoTitle.set_markup(_("<b> Hardware Information</b>"));

	
	title.pack_start(hardwareInfoTitle , Gtk::PACK_SHRINK);

	cpuModelBox.pack_start(cpuModelLabel,Gtk::PACK_SHRINK);
	cpuModelBox.pack_start(cpuModelDataLabel,Gtk::PACK_SHRINK);

	memoryBox.pack_start(memoryLabel,Gtk::PACK_SHRINK);
	memoryBox.pack_start(memoryDataLabel,Gtk::PACK_SHRINK);

	processorBox.pack_start(processorTypeLabel,Gtk::PACK_SHRINK);
	processorBox.pack_start(processorTypeDataLabel,Gtk::PACK_SHRINK);

	cpuCoresBox.pack_start(cpuCoresLabel,Gtk::PACK_SHRINK);
	cpuCoresBox.pack_start(cpuCoresDataLabel,Gtk::PACK_SHRINK);

	//labelBox.set_spacing(1);
	labelBox.pack_start(title);
	labelBox.pack_start(cpuModelBox);
	labelBox.pack_start(memoryBox);
	labelBox.pack_start(processorBox);
	labelBox.pack_start(cpuCoresBox);

	imageBox.pack_start(image ,Gtk::PACK_SHRINK);
	mainBox.pack_start(imageBox ,Gtk::PACK_SHRINK);
	mainBox.pack_start(labelBox);
	
	add(mainBox);
}

