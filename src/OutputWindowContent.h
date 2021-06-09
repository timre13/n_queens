#pragma once

#include "BoardWidget.h"
#include "Board.h"
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
    std::shared_ptr<BoardWidget> m_boardWidget;
    std::shared_ptr<TreeNode> m_solutionTree;
    std::vector<std::shared_ptr<Board>> m_solutionBoards;
    int m_shownSolutionI{};
    std::unique_ptr<Gtk::Button> m_prevSolutionButton;
    std::unique_ptr<Gtk::Button> m_nextSolutionButton;
    std::unique_ptr<Gtk::Label> m_noSolutionsLabel;

public:
    OutputWindowContent(std::shared_ptr<BoardWidget> boardWidget, bool shouldSolveRecursively, size_t numOfSolutionsToFind);

    void solveProblemWithBacktracking(size_t maxSolutionNum);
    void solveProblemWithRecursion(size_t maxSolutionNum);
};

