#include "InputWindowContent.h"
#include "MainWindow.h"
#include "config.h"
#include <gdkmm/device.h>
#include <gtkmm/enums.h>
#include <gtkmm/messagedialog.h>
#include <gtkmm/radiobuttongroup.h>
#include <pangomm/fontdescription.h>
#include <memory>
#include <limits>

InputWindowContent::InputWindowContent(std::shared_ptr<BoardWidget> boardWidget)
    :
    m_sizeFrame{std::make_unique<Gtk::Frame>()},
    m_sizeFrameGrid{std::make_unique<Gtk::Grid>()},
    m_spinButton{std::make_unique<Gtk::SpinButton>()},
    m_boardWidget{boardWidget},
    m_algorithmChooserFrame{std::make_unique<Gtk::Frame>()},
    m_algorithmChooserFrameGrid{std::make_unique<Gtk::Grid>()},
    m_algorithmChooserButton1{std::make_unique<Gtk::RadioButton>()},
    m_algorithmChooserButton2{std::make_unique<Gtk::RadioButton>()},
    m_numOfSolutionsChooserSpinButtonLabel{std::make_unique<Gtk::Label>()},
    m_numOfSolutionsChooserSpinButton{std::make_unique<Gtk::SpinButton>()},
    m_solveButton{std::make_unique<Gtk::Button>()}
{
    set_border_width(10);

    //--------------------------- Size selector widget -------------------------

    attach(*m_sizeFrame, 1, 1);
    m_sizeFrame->set_label("Size");

    m_sizeFrame->add(*m_sizeFrameGrid);

    m_sizeFrameGrid->attach(*m_spinButton, 0, 0);
    m_spinButton->set_range(4, MAX_BOARD_SIZE);
    m_spinButton->set_increments(1, 1);
    m_spinButton->set_value(8);
    m_spinButton->signal_value_changed().connect(sigc::mem_fun(*this, &InputWindowContent::onSpinButtonChanged));

    //---------------------------- Board widget --------------------------------

    attach(*m_boardWidget, 1, 2);
    m_boardWidget->set_margin_top(20);
    m_boardWidget->set_margin_bottom(20);
    m_boardWidget->add_events(Gdk::EventMask::BUTTON_PRESS_MASK | Gdk::EventMask::BUTTON_RELEASE_MASK);
    m_boardWidget->signal_button_release_event().connect(sigc::mem_fun(*this, &InputWindowContent::onCanvasClicked));

    //----------------------- Algorithm chooser widgets ------------------------

    // No need to keep the object after construction
    Gtk::RadioButtonGroup radioButtonGroup;

    attach(*m_algorithmChooserFrame, 1, 3);
    m_algorithmChooserFrame->set_label("Algorithm");

    m_algorithmChooserFrame->add(*m_algorithmChooserFrameGrid);

    m_algorithmChooserFrameGrid->attach(*m_algorithmChooserButton1, 0, 0);
    m_algorithmChooserButton1->set_group(radioButtonGroup);
    m_algorithmChooserButton1->set_label("Recursive");

    m_algorithmChooserFrameGrid->attach(*m_algorithmChooserButton2, 0, 1);
    m_algorithmChooserButton2->join_group(*m_algorithmChooserButton1);
    m_algorithmChooserButton2->set_label("Backtracking");

    m_algorithmChooserFrameGrid->attach(*m_numOfSolutionsChooserSpinButtonLabel, 0, 2);
    m_numOfSolutionsChooserSpinButtonLabel->set_label("Max. solutions (-1=ALL): ");

    m_algorithmChooserFrameGrid->attach(*m_numOfSolutionsChooserSpinButton, 1, 2);
    m_numOfSolutionsChooserSpinButton->set_range(-1, std::numeric_limits<double>::max());
    m_numOfSolutionsChooserSpinButton->set_increments(1, 1);
    m_numOfSolutionsChooserSpinButton->set_value(-1);

    //----------------------------- Solve button -------------------------------

    attach(*m_solveButton, 1, 4);
    m_solveButton->set_label("Solve!");
    m_solveButton->override_font(Pango::FontDescription{"Sans Regular 18"});
    m_solveButton->signal_pressed().connect(sigc::mem_fun(*this, &InputWindowContent::onSolveButtonPressed));

    //--------------------------------------------------------------------------

    show_all_children();
}

/*
 * Shows an error dialog and returns true if the board is too large to fit in the destination variable.
 */
static bool checkBoardSize(int size)
{
    if (size >= (int)(Queen::coord_t)-1)
    {
        auto dialog{std::make_unique<Gtk::MessageDialog>(
                "Board is too large.\n(Adjust the compile-time constant QUEEN_COORD_TYPE).",
                Gtk::MessageType::MESSAGE_ERROR)};
        dialog->run();
        return 1;
    }
    return 0;
}

void InputWindowContent::onSpinButtonChanged()
{
    if (checkBoardSize(m_spinButton->get_value_as_int()))
        return;

    m_boardWidget->getBoardPtr()->setSize(m_spinButton->get_value_as_int());
    m_boardWidget->getBoardPtr()->clearQueens();
    m_boardWidget->queue_draw();
}

bool InputWindowContent::onCanvasClicked(GdkEventButton* button)
{
    // If no more room for queens, exit
    if ((int)m_boardWidget->getBoardPtr()->getNumOfQueens() == m_boardWidget->getBoardPtr()->getSize())
        return true;

    const int queenX = button->x / ((double)BOARD_WIDGET_DIMENSIONS_PX / m_boardWidget->getBoardPtr()->getSize());
    const int queenY = button->y / ((double)BOARD_WIDGET_DIMENSIONS_PX / m_boardWidget->getBoardPtr()->getSize());

    if (!m_boardWidget->getBoardPtr()->wouldBeCorrect(queenX, queenY))
    {
        auto dialog{std::make_unique<Gtk::MessageDialog>("You can't place a queen there.", Gtk::MessageType::MESSAGE_ERROR)};
        dialog->run();
        return true;
    }

    // Mouse coords to grid coords
    m_boardWidget->getBoardPtr()->addQueen(queenX, queenY);
    m_boardWidget->queue_draw();

    return true; // TODO: What's this?
}

void InputWindowContent::onSolveButtonPressed()
{
    if (checkBoardSize(m_spinButton->get_value_as_int()))
        return;

    dynamic_cast<MainWindow*>(get_parent())->onInputContentSolveButtonPressed();
}

