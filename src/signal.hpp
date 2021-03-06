
#pragma once

#include "point.hpp"

#include <sigc++/signal.h>
#include <gdkmm/color.h>

#include <memory>
#include <vector>

class enclosure;
class driver;
class Crossover;
class filter_network;
class driver_list;

/*
 * signal_crossover_selected
 * Emit this signal when you want to change current crossover.
 * SigC::Object is the new crossover
 */
extern sigc::signal1<void, Crossover*> signal_crossover_selected;

/*
 * signal_drivers_loaded
 * Emit this signal when you want to change current speakerlist.
 * driver_list arg is the new driver_list
 */
extern sigc::signal1<void, std::shared_ptr<driver_list const>> signal_drivers_loaded;

/*
 * signal_box_selected
 * Emit this signal when you want to change the current box
 * enclosure * is a ptr to the new box
 */
extern sigc::signal1<void, enclosure*> signal_box_selected;
extern sigc::signal1<void, enclosure*> signal_box_modified;
extern sigc::signal1<void, enclosure*> signal_add_to_boxlist;
extern sigc::signal3<void, enclosure*, driver*, Gdk::Color&> signal_add_plot;
extern sigc::signal2<int, std::vector<gspk::point>&, Gdk::Color&> signal_add_box_plot;
extern sigc::signal1<void, int> signal_remove_box_plot;
extern sigc::signal1<void, int> signal_hide_box_plot;
extern sigc::signal1<void, int> signal_select_plot;

/* Define two signals for crossover parts updates */
extern sigc::signal0<void> signal_net_modified_by_wizard; // listen to this in crossover treeview
extern sigc::signal1<void, filter_network*>
    signal_net_modified_by_user; // listan to this in filter wizard
extern sigc::signal1<void, int> signal_new_crossover;
extern sigc::signal0<void> signal_plot_crossover;
extern sigc::signal4<int, std::vector<gspk::point> const&, Gdk::Color const&, int&, filter_network*>
    signal_add_crossover_plot;
extern sigc::signal0<void> signal_save_open_files;
