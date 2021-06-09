#pragma once

#include "Board.h"
#include "BoardWidget.h"
#include <memory>
#include <gtkmm/applicationwindow.h>
#include <gtkmm/grid.h>
#include <gtkmm/spinbutton.h>
#include <gtkmm/frame.h>
#include <gtkmm/button.h>
#include <gtkmm/radiobutton.h>
#include <gtkmm/label.h>

class InputWindowContent final : public Gtk::Grid
{
private:
    std::unique_ptr<Gtk::Frame> m_sizeFrame;
    std::unique_ptr<Gtk::Grid> m_sizeFrameGrid;
    std::unique_ptr<Gtk::SpinButton> m_spinButton;

    std::shared_ptr<BoardWidget> m_boardWidget;

    std::unique_ptr<Gtk::Frame> m_algorithmChooserFrame;
    std::unique_ptr<Gtk::Grid> m_algorithmChooserFrameGrid;
    std::unique_ptr<Gtk::RadioButton> m_algorithmChooserButton1;
    std::unique_ptr<Gtk::RadioButton> m_algorithmChooserButton2;
    std::unique_ptr<Gtk::Label> m_numOfSolutionsChooserSpinButtonLabel;
    std::unique_ptr<Gtk::SpinButton> m_numOfSolutionsChooserSpinButton;

    std::unique_ptr<Gtk::Button> m_solveButton;

public:
    InputWindowContent(std::shared_ptr<BoardWidget> boardWidget);

    inline bool shouldSolveWithRecursion() const { return m_algorithmChooserButton1->get_active(); }
    inline size_t findNumOfSolutions() const { return m_numOfSolutionsChooserSpinButton->get_value_as_int(); }

    void onSpinButtonChanged();
    bool onCanvasClicked(GdkEventButton* button);
    void onSolveButtonPressed();
};
