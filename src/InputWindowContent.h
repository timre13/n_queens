#pragma once

#include "Board.h"
#include "BoardWidget.h"
#include <memory>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/grid.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/frame.h>
#include <gtkmm/button.h>

class InputWindowContent final : public Gtk::Grid
{
private:
    std::unique_ptr<Gtk::Frame> m_sizeFrame;
    std::unique_ptr<Gtk::Grid> m_sizeFrameGrid;
    std::unique_ptr<Gtk::SpinButton> m_spinButton;
    BoardWidget* m_boardWidget{};
    std::unique_ptr<Gtk::Button> m_solveButton;

public:
    InputWindowContent();

    BoardWidget* getBoardWidget() const { return m_boardWidget; }

    void onSpinButtonChanged();
    bool onCanvasClicked(GdkEventButton* button);
    void onSolveButtonPressed();
};
