#pragma once

#include "Board.h"
#include <memory>
#include <gtkmm/window.h>
#include <gtkmm/grid.h>

class OutputWindowContent final : public Gtk::Grid
{
private:
    std::unique_ptr<Board> m_board;

public:
    OutputWindowContent(Board* board);
};

