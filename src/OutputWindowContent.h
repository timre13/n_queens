#pragma once

#include "BoardWidget.h"
#include "TreeNode.h"
#include <memory>
#include <gtkmm/grid.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/button.h>
#include <gtkmm/label.h>

class OutputWindowContent final : public Gtk::Grid
{
private:
    std::unique_ptr<Gtk::ProgressBar> m_progressBar;
    std::unique_ptr<BoardWidget> m_boardWidget;
    std::unique_ptr<TreeNode> m_solutionTree;
    std::vector<TreeNode*> m_solutionNodes;
    int m_shownSolutionI{};
    std::unique_ptr<Gtk::Button> m_prevSolutionButton;
    std::unique_ptr<Gtk::Button> m_nextSolutionButton;
    std::unique_ptr<Gtk::Label> m_noSolutionsLabel;

public:
    OutputWindowContent(BoardWidget* boardWidget);

    void solveProblemNonrecursively(int maxSolutionNum);
    void solveProblemRecursively();
};

