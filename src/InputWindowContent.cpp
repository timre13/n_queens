#include "InputWindowContent.h"
#include "MainWindow.h"
#include "config.h"
#include <gdkmm/device.h>
#include <gtkmm/enums.h>
#include <memory>
#include <pangomm/fontdescription.h>
#include <sigc++/functors/mem_fun.h>
#include <iostream>

InputWindowContent::InputWindowContent()
    :
    m_sizeFrame{std::make_unique<Gtk::Frame>()},
    m_sizeFrameGrid{std::make_unique<Gtk::Grid>()},
    m_spinButton{std::make_unique<Gtk::SpinButton>()},
    m_boardWidget{new BoardWidget{new Board{8}}},
    m_solveButton{std::make_unique<Gtk::Button>()}
{
    set_border_width(10);

    attach(*m_sizeFrame, 1, 1);
    m_sizeFrame->set_label("Size");

    m_sizeFrame->add(*m_sizeFrameGrid);

    m_sizeFrameGrid->attach(*m_spinButton, 0, 0);
    m_spinButton->set_range(4, MAX_BOARD_SIZE);
    m_spinButton->set_increments(1, 1);
    m_spinButton->set_value(8);
    m_spinButton->signal_value_changed().connect(sigc::mem_fun(*this, &InputWindowContent::onSpinButtonChanged));

    attach(*m_boardWidget, 1, 2);
    m_boardWidget->set_margin_top(20);
    m_boardWidget->set_margin_bottom(20);
    m_boardWidget->add_events(Gdk::EventMask::BUTTON_PRESS_MASK | Gdk::EventMask::BUTTON_RELEASE_MASK);
    m_boardWidget->signal_button_release_event().connect(sigc::mem_fun(*this, &InputWindowContent::onCanvasClicked));

    attach(*m_solveButton, 1, 3);
    m_solveButton->set_label("Solve!");
    m_solveButton->override_font(Pango::FontDescription{"Sans Regular 18"});
    m_solveButton->signal_pressed().connect(sigc::mem_fun(*this, &InputWindowContent::onSolveButtonPressed));

    show_all_children();
}

void InputWindowContent::onSpinButtonChanged()
{
    m_boardWidget->getBoardPtr()->setSize(m_spinButton->get_value_as_int());
    m_boardWidget->getBoardPtr()->clearQueens();
    m_boardWidget->queue_draw();
}

bool InputWindowContent::onCanvasClicked(GdkEventButton* button)
{
    // If no more room for queens, exit
    if ((int)m_boardWidget->getBoardPtr()->getNumOfQueens() == m_boardWidget->getBoardPtr()->getSize())
        return true;

    // Mouse coords to grid coords
    m_boardWidget->getBoardPtr()->addQueen(
            button->x / ((double)BOARD_WIDGET_DIMENSIONS_PX / m_boardWidget->getBoardPtr()->getSize()),
            button->y / ((double)BOARD_WIDGET_DIMENSIONS_PX / m_boardWidget->getBoardPtr()->getSize()));
    m_boardWidget->queue_draw();

    return true; // TODO: What's this?
}

void InputWindowContent::onSolveButtonPressed()
{
    dynamic_cast<MainWindow*>(get_parent())->onInputContentSolveButtonPressed();
}

