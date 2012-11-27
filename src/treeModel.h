// Ahmed Al-Yahyai
// blackheart10001@gmail.com

#ifndef _TREEMODEL_H_
#define _TREEMODEL_H_

#include <glibmm/refptr.h>
#include <gtkmm/liststore.h>
#include <gtkmm/treeview.h>
#include <iostream>
#include <fstream>

class ModelColumnsTweak : public Gtk::TreeModel::ColumnRecord
{
	 public:
		ModelColumnsTweak()	
			{ add(tweak_id);add(tweak_type);add(tweak_distro);add(tweak_name);add (tweak_pkgVer);add(tweak_status);}
		Gtk::TreeModelColumn<Glib::ustring> tweak_id;
		Gtk::TreeModelColumn<Glib::ustring> tweak_type;
		Gtk::TreeModelColumn<Glib::ustring> tweak_name;
		Gtk::TreeModelColumn<Glib::ustring> tweak_distro;
		Gtk::TreeModelColumn<Glib::ustring> tweak_pkgVer;
		Gtk::TreeModelColumn<Glib::ustring> tweak_status;
    };

#endif // _TREEMODEL_H_