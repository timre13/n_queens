#include "MainWindow.h"
#include <memory>

MainWindow::MainWindow()
{
    set_title("N Queens");
    set_resizable(false);

    m_inputContent = new InputWindowContent;
    this->add(*m_inputContent);

    show_all_children();
}

void MainWindow::onInputContentSolveButtonPressed()
{
    auto board{m_inputContent->getBoardWidget()}; // Get the prepared board
    this->remove(); // Clear the window
    delete m_inputContent;

    m_outputContent = std::make_unique<OutputWindowContent>(board);
    this->add(*m_outputContent); // Display the output screen

    show_all_children();
}

