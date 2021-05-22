#pragma once

#include "Table.h"
#include <memory>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>

class OutputWindowContent final : public Gtk::Grid
{
private:
    std::unique_ptr<Table> m_table;

public:
    OutputWindowContent(Table* table);
};

