#pragma once

#include "Table.h"
#include <memory>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>

class OutputWindow final : public Gtk::Window
{
private:
    std::unique_ptr<Gtk::Grid> m_grid;
    std::unique_ptr<Table> m_table;

public:
    OutputWindow();
};

