#pragma once

#include <gtkmm/applicationwindow.h>
#include <memory>
#include "InputWindowContent.h"
#include "OutputWindowContent.h"

class MainWindow final : public Gtk::ApplicationWindow
{
private:
    std::shared_ptr<BoardWidget> m_boardWidget;
    std::unique_ptr<InputWindowContent> m_inputContent{};
    std::unique_ptr<OutputWindowContent> m_outputContent{};

public:
    MainWindow();

    // Called by `m_inputContent` when pressing the "Solve" button
    void onInputContentSolveButtonPressed();
};

