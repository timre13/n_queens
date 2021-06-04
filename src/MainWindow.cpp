#include "MainWindow.h"
#include <memory>

MainWindow::MainWindow()
    :
    m_boardWidget{std::make_shared<BoardWidget>(std::make_shared<Board>(8))},
    m_inputContent{std::make_unique<InputWindowContent>(m_boardWidget)}
{
    set_title("N Queens");
    set_resizable(false);

    this->add(*m_inputContent);

    show_all_children();
}

void MainWindow::onInputContentSolveButtonPressed()
{
    this->remove(); // Clear the window
    m_inputContent.reset();

    m_outputContent = std::make_unique<OutputWindowContent>(m_boardWidget);
    this->add(*m_outputContent); // Display the output screen

    show_all_children();
}

