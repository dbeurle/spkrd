
#include "common.h"
#include "gspeakersstock.h"
#include "mainwindow.h"

#include <gtkmm/main.h>
#include <libxml/parser.h>
#include <libxml/tree.h>

#include <clocale>
#include <cstdlib>
#include <iostream>

int main(int argc, char* argv[]) {
  /* Initialize gettext */
#if ENABLE_NLS
  setlocale(LC_ALL, "");
  bindtextdomain(PACKAGE, GNOMELOCALEDIR);
  bind_textdomain_codeset(GETTEXT_PACKAGE, "UTF-8");
  textdomain(PACKAGE);
#endif

  Gtk::Main kit(argc, argv);

  try {
#ifdef TARGET_WIN32
    g_settings.load("gspeakers2.conf");
#else
    g_settings.load(Glib::get_home_dir() + "/.gspeakers/gspeakers2.conf");
#endif
  } catch (std::runtime_error const& e) {
#ifdef OUTPUT_DEBUG
    std::cout << "Main: " << e.what() << std::endl;
#endif
#ifdef TARGET_WIN32
    Gtk::MessageDialog md(_("No configuration file found!") + Glib::ustring("\n") +
                              _("gspeakers2.conf created in current directory"),
                          true, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
#else
    Gtk::MessageDialog md(_("No configuration file found!") + Glib::ustring("\n\n") +
                              Glib::get_home_dir() + "/.gspeakers/gspeakers2.conf created",
                          true, Gtk::MESSAGE_INFO, Gtk::BUTTONS_OK, true);
#endif
    md.run();
#ifdef TARGET_WIN32
    std::string s = "echo "
                    " > gspeakers2.conf";
    system(s.c_str());
    g_settings.load("gspeakers2.conf");
#else
    std::string s = "mkdir " + Glib::get_home_dir() + "/.gspeakers";
    system(s.c_str());
    s = "touch " + Glib::get_home_dir() + "/.gspeakers/gspeakers2.conf";
    system(s.c_str());
    g_settings.load(Glib::get_home_dir() + "/.gspeakers/gspeakers2.conf");
#endif
  }
  g_settings.defaultValueUnsignedInt("ToolbarStyle", Gtk::TOOLBAR_BOTH);
  /* Init BoxEditor before BoxHistory, this will make BoxHistory signal BoxEditor with selected box,
   * which is nice (tm) */
  // BoxEditor be;
  // BoxHistory bh;

  /* Plot history will always be empty at startup for now */
  // PlotHistory ph;

  // GSpeakersBoxPlot gsbp;
  std::cout << _("Testing gettext") << std::endl;
  // SpeakerListSelector sls;
  gspeakers_stock_init();
  MainWindow mw;
  // mw.show_all_children();
  // signal_plot_crossover();

  kit.run(mw);
  //  std::cout << c1;
  /* save settings */
  try {
    g_settings.save();
  } catch (std::runtime_error const& e) {
#ifdef OUTPUT_DEBUG
    std::cout << "Main: " << e.what() << std::endl;
#endif
  }

  // Net n;
  // n.set_has_imp_corr(true);
  // n.set_has_damp(true);
  // Speaker s;
  // std::cout << n.to_SPICE(s) << std::endl;
  // printf("%e\n", 3.0);
  return 0;
}
/*
// test net
Net n1;
//  std::cout << n1 << "--------" << std::endl;
  n1.set_highpass_order(NET_ORDER_1ST);
  n1.set_lowpass_order(NET_ORDER_3RD);
  (*n1.parts())[0].set_value(4.7);
  (*n1.parts())[1].set_value(6.8);
  (*n1.parts())[2].set_value(3.3);
  (*n1.parts())[n1.get_lowpass_order() + 0].set_value(4.7);
  std::cout << n1 << "--------" << std::endl;
  n1.set_lowpass_order(NET_ORDER_1ST);
  std::cout << n1 << "--------" << std::endl;
  n1.set_highpass_order(NET_NOT_PRESENT);
  n1.set_lowpass_order(NET_NOT_PRESENT);
  n1.set_lowpass_order(NET_ORDER_2ND);
  (*n1.parts())[1].set_value(6.8);
  std::cout << n1;

*/

/*
 std::vector<string> v;
  v.push_back("hejsan");
  v.push_back("halloe");
  v.push_back("halihalo");

 std::vector<string>::iterator iter = v.begin();

  for(
     std::vector<string>::iterator from = v.begin();
      from != v.end();
      ++from
     )
  {
    std::cout << *from << std::endl;
  }
  v.erase(iter + 1);
  for(
     std::vector<string>::iterator from = v.begin();
      from != v.end();
      ++from
     )
  {
    std::cout << *from << std::endl;
  }

 std::vector<string> v;
  v.push_back("hejsan");
  v.push_back("halloe");
  v.push_back("halihalo");

 std::vector<string>::iterator iter = v.begin();

  for(
     std::vector<string>::iterator from = v.begin();
      from != v.end();
      ++from
     )
  {
    std::cout << *from << std::endl;
  }
  std::cout << "---" << std::endl;
  iter = v.insert(iter + 1, "hej1");
  iter = v.insert(iter, "hej2");
  v.insert(iter, "hej3");
  for(
     std::vector<string>::iterator from = v.begin();
      from != v.end();
      ++from
     )
  {
    std::cout << *from << std::endl;
  }


*/
