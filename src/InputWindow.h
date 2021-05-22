#pragma once

#include "Table.h"
#include <memory>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/grid.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/frame.h>
#include <gtkmm/button.h>

class InputWindow final : public Gtk::ApplicationWindow
{
private:
    std::unique_ptr<Gtk::Grid> m_grid;
    std::unique_ptr<Gtk::Frame> m_sizeFrame;
    std::unique_ptr<Gtk::Grid> m_sizeFrameGrid;
    std::unique_ptr<Gtk::SpinButton> m_spinButton;
    std::unique_ptr<Table> m_table;
    std::unique_ptr<Gtk::Button> m_solveButton;

public:
    InputWindow();

    void onSpinButtonChanged();
    bool onCanvasClicked(GdkEventButton* button);
    void onSolveButtonPressed();
};
