#pragma once

#include "Board.h"
#include "TreeNode.h"
#include <memory>
#include <gtkmm/grid.h>
#include <gtkmm/progressbar.h>

class OutputWindowContent final : public Gtk::Grid
{
private:
    std::unique_ptr<Gtk::ProgressBar> m_progressBar;
    std::unique_ptr<TreeNode> m_solutionTree;
    std::vector<TreeNode*> m_solutionNodes;

public:
    OutputWindowContent(Board* board);

    void solveProblemNonrecursively(int maxSolutionNum);
};

