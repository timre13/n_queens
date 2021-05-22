#include "InputWindow.h"
#include "config.h"
#include <gdkmm/device.h>
#include <gtkmm/enums.h>
#include <memory>
#include <pangomm/fontdescription.h>
#include <sigc++/functors/mem_fun.h>
#include <iostream>

InputWindow::InputWindow()
    :
    m_grid{std::make_unique<Gtk::Grid>()},
    m_sizeFrame{std::make_unique<Gtk::Frame>()},
    m_sizeFrameGrid{std::make_unique<Gtk::Grid>()},
    m_spinButton{std::make_unique<Gtk::SpinButton>()},
    m_table{std::make_unique<Table>(8)},
    m_solveButton{std::make_unique<Gtk::Button>()}
{
    set_title("N Queens");
    //set_default_geometry(800, 400);
    set_resizable(false);

    add(*m_grid);
    m_grid->set_border_width(10);

    m_grid->attach(*m_sizeFrame, 1, 1);
    m_sizeFrame->set_label("Size");

    m_sizeFrame->add(*m_sizeFrameGrid);

    m_sizeFrameGrid->attach(*m_spinButton, 0, 0);
    m_spinButton->set_range(4, MAX_TABLE_SIZE);
    m_spinButton->set_increments(1, 1);
    m_spinButton->set_value(8);
    m_spinButton->signal_value_changed().connect(sigc::mem_fun(*this, &InputWindow::onSpinButtonChanged));

    m_grid->attach(*m_table, 1, 2);
    m_table->set_margin_top(20);
    m_table->set_margin_bottom(20);
    m_table->add_events(Gdk::EventMask::BUTTON_PRESS_MASK | Gdk::EventMask::BUTTON_RELEASE_MASK);
    m_table->signal_button_release_event().connect(sigc::mem_fun(*this, &InputWindow::onCanvasClicked));

    m_grid->attach(*m_solveButton, 1, 3);
    m_solveButton->set_label("Solve!");
    m_solveButton->override_font(Pango::FontDescription{"Sans Regular 18"});
    m_solveButton->signal_pressed().connect(sigc::mem_fun(*this, &InputWindow::onSolveButtonPressed));

    show_all_children();
}

void InputWindow::onSpinButtonChanged()
{
    m_table->setSize(m_spinButton->get_value_as_int());
    m_table->clearQueens();
    m_table->queue_draw();
}

bool InputWindow::onCanvasClicked(GdkEventButton* button)
{
    // If no more room for queens, exit
    if ((int)m_table->getNumOfQueens() == m_table->getSize())
        return true;

    // Mouse coords to grid coords
    m_table->addQueen(
            button->x / ((double)TABLE_WIDGET_DIMENSIONS_PX / m_table->getSize()),
            button->y / ((double)TABLE_WIDGET_DIMENSIONS_PX / m_table->getSize()));
    m_table->queue_draw();

    return true; // TODO: What's this?
}

void InputWindow::onSolveButtonPressed()
{
    this->close();
}

