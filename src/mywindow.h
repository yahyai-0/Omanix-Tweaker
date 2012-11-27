/*
 * Ahmed Al-Yahyai
 * blackheart10001@gmail.com
 * 
 * Omanix Tweaker is free software: you can redistribute it and/or modify it
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

#ifndef _MYWINDOW_H_
#define _MYWINDOW_H_

#include <gtkmm/window.h>
#include <gtkmm/box.h>
#include <gtkmm/button.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/label.h>
#include <gtkmm/entry.h>
#include <gtkmm/notebook.h>
#include <gtkmm/buttonbox.h>
#include <gtkmm/toolbar.h>
#include <gtkmm/toolbutton.h>
#include <gtkmm/iconfactory.h>
#include <gtkmm/stock.h>
#include <gtkmm/alignment.h>
#include "treeModel.h"
#include "app.h"
#include "user-info.h"
#include "hardware-info.h"
#include "desktop-info.h"

using namespace std;

class MyWindow: public Gtk::Window
{
	int welcomeIndex ,tweakerIndex ,settingIndex; 
public:
	
	MyWindow(); 
	virtual ~MyWindow();


protected:
	
virtual void register_stock_items();
	virtual void add_stock_item(const Glib::RefPtr<Gtk::IconFactory>& factory,
                      const std::string& filepath,
                      const Glib::ustring& id, const Glib::ustring& label);
	virtual bool on_treeView_press_event(GdkEventButton* event);
	//signal handler
	void on_mainB_clicked();
	void on_tweakerB_clicked();
	void on_settingB_clicked();
	void on_update_clicked();
	void on_install_clicked();
	void on_remove_clicked();
	void on_info_clicked();
	void on_about_clicked();
	void on_language_clicked();
	void on_infobar_button_respone(int response);
	void on_progressbar_button_respone(int response);
	//void proxy_key_changed(guint connection_id, Gnome::Conf::Entry entry);
	
	//Tree model columns:
	
	ModelColumnsTweak col;  //object of Tree Model columns
	Gtk::CellRendererPixbuf   pixBufRenderer;

	//widgets
	Gtk::Image omanixTweakerImg ,aboutButtonImg;
	Gtk::Notebook noteBook;
	Gtk::Menu popupMenu;
	Gtk::VBox main_box ,splashBox ,welcomNoteBox ,tweakerNoteBox , settingNoteBox ;
	Gtk::HBox TweakerIconBox  ,buttonBox ,DesktopUserInfoBox ,toolbarBox ;
	Gtk::Toolbar toolbar;
	Gtk::ToolButton toolb_update , toolb_install, toolb_remove , toolb_description;
	Gtk::TreeView treeView;
	Gtk::ScrolledWindow scrolled_treeView;
	Gtk::InfoBar infobar , progressBAR;
	Gtk::ProgressBar ProgressBar1;
	Gtk::Button mainButton ,tweakerButton , settingButton , aboutButton;
	Gtk::HButtonBox noteButtonBox;
	Gtk::Label splashLabel ,infobar_label ,hardwareInfoLabel ,desktopInfoLabel ,userInfoLabel
				,mainButtonLabel ,tweakerButtonLabel ,settingButtonLabel;
	//Gtk::Entry proxy;
	
	Gdk::Color gray;
	Gdk::Color buttonGray;
	Glib::RefPtr<Gdk::Pixbuf> ProgIcon;
    Glib::RefPtr<Gtk::ListStore> refTreeModel;
	Glib::RefPtr<Gtk::TreeSelection> refTreeSelection;
	UserInfo userInfo;
	DesktopInfo desktopInfo;
	HardwareInfo hardwareInfo;
	App app;
};

#endif // _MYWINDOW_H_
