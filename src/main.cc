/* -*- Mode: C; indent-tabs-mode: t; c-basic-offset: 4; tab-width: 4 -*- */
/*
 * main.cc
 * Copyright (C) zero 2011 <yahyai-0@hotmail.com>
 * 
 * bugSpy is free software: you can redistribute it and/or modify it
 * under the terms of the GNU General Public License as published by the
 * Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 * 
 * bugSpy is distributed in the hope that it will be useful, but
 * WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.
 * See the GNU General Public License for more details.
 * 
 * You should have received a copy of the GNU General Public License along
 * with this program.  If not, see <http://www.gnu.org/licenses/>.
 */
#include "mywindow.h"
#include <gtkmm/main.h>
#include <config.h>
#include <glibmm/i18n.h>



int main( int argc , char * argv[])
{

	g_type_init ();
	Gtk::Main kit(argc , argv);
	//Glib::thread_init();
	//Gtk::Main main_instance (&argc, &argv);

	Gnome::Conf::init();
	bindtextdomain(GETTEXT_PACKAGE, PROGRAMNAME_LOCALEDIR);
	bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
	textdomain(GETTEXT_PACKAGE);
	
	MyWindow mywindow;

	Gtk::Main::run(mywindow);
	return 0;


}