/*
  $Id$

  crossovertreeview Copyright (C) 2002 Daniel Sundberg

  This program is free software; you can redistribute it and/or modify
  it under the terms of the GNU General Public License version 2
  as published by the Free Software Foundation.

  This program is distributed in the hope that it will be useful,
  but WITHOUT ANY WARRANTY; without even the implied warranty of
  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
  GNU General Public License for more details.

  You should have received a copy of the GNU General Public License
  along with this program; if not, write to the Free Software
  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA 02111-1307 USA
*/

#pragma once

#include "crossover_cell_item.hpp"
#include "crossover.hpp"

#include <gtkmm/box.h>
#include <gtkmm/frame.h>
#include <gtkmm/scrolledwindow.h>
#include <gtkmm/treemodel.h>
#include <gtkmm/treestore.h>
#include <gtkmm/treeview.h>

/// A TreeView that displays the currently selected crossover
class crossover_tree_view : public Gtk::Frame
{
public:
    crossover_tree_view();

    ~crossover_tree_view() override;

public:
    void on_crossover_selected(Crossover* new_crossover);

protected:
    void on_realize() override;

    void on_cell_edited_value(Glib::ustring const& path_string,
                              Glib::ustring const& new_text);

    void on_net_modified_by_wizard();

    void value_cell_data_func(Gtk::CellRenderer* cell,
                              Gtk::TreeModel::iterator const& iter);

    virtual void create_model();

    virtual void add_columns();

    virtual void treestore_add_item(crossover_cell_item const& foo);

protected:
    struct model_columns : public Gtk::TreeModel::ColumnRecord
    {
        model_columns();

        Gtk::TreeModelColumn<Glib::ustring> id_string;
        Gtk::TreeModelColumn<int> id;
        Gtk::TreeModelColumn<int> type;
        Gtk::TreeModelColumn<double> value;
        Gtk::TreeModelColumn<Glib::ustring> unit;
        Gtk::TreeModelColumn<bool> editable;
        Gtk::TreeModelColumn<bool> visible;
    };

protected:
    Gtk::ScrolledWindow m_scrolled_window;
    Gtk::TreeView m_tree_view;
    Glib::RefPtr<Gtk::TreeStore> m_tree_store;
    std::vector<crossover_cell_item> m_items;

    // Pointer to currently selected crossover
    Crossover* m_cover;

    model_columns const m_columns;

    Gtk::CellRendererText m_cellrenderer_validated;
    Gtk::TreeView::Column m_treeviewcolumn_validated;
    bool m_validate_retry;
    Glib::ustring m_invalid_text_for_retry;
};
