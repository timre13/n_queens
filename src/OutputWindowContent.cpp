#include "OutputWindowContent.h"
#include <gtkmm/application.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/window.h>
#include <memory>
#include <iostream>

OutputWindowContent::OutputWindowContent(Board* board)
    :
    m_progressBar{std::make_unique<Gtk::ProgressBar>()},
    m_solutionTree{std::make_unique<TreeNode>(TreeNode{board})} // The initial board is the root node
{
    set_border_width(10);

    attach(*m_progressBar, 0, 0);
    m_progressBar->set_text("Solving...");
    m_progressBar->set_show_text();
    m_progressBar->set_pulse_step(1.0/(board->getSize()*board->getSize()));

    show_all_children();

    /*
     * XXX:
     * Make it possible to select between non-recursive (left to right) and
     * recursive (top to bottom) algorithms.
     * If the non-recursive algorithm is selected,
     * make it possible to specify the number of solutions to find.
     */
    solveProblemNonrecursively(5);
    std::cout << "Found " << m_solutionNodes.size() << " solution(s)" << std::endl;
    this->remove(*m_progressBar);

    /*
     * XXX: Make it possible to step between solutions.
     */
    if (m_solutionNodes.size())
        attach(*m_solutionNodes[0]->getBoard(), 0, 1);
}

void OutputWindowContent::solveProblemNonrecursively(int maxSolutionNum)
{
    TreeNode* node = m_solutionTree.get();
    int boardSize{node->getBoard()->getSize()};
    while (true)
    {
        int i{};
        if (node
            && node->getBoard()
            && node->getBoard()->getLastCheckedCoords().getXPos() != -1
            && node->getBoard()->getLastCheckedCoords().getYPos() != -1)
            i = node->getBoard()->getLastCheckedCoords().getXPos() +
                node->getBoard()->getLastCheckedCoords().getYPos() * boardSize + 1;

        while (i%boardSize < boardSize && i/boardSize < boardSize && !node->getBoard()->wouldBeCorrect(i%boardSize, i/boardSize))
        {
            std::cout << "Skipping " << i%boardSize << ", " << i/boardSize << std::endl;
            ++i;
        }
        std::cout << i << std::endl;
        if (i == boardSize*boardSize)
        {
            std::cout << "Branch finished" << std::endl;
            if (!node->getParent()) // FIXME: This does not work 
            {
                std::cout << "Solved board" << std::endl;
                return;
            }
            node = node->getParent();
            std::cout << "Node has " << node->getBoard()->getNumOfQueens() << " queens" << std::endl;
        }
        else
        {
            std::cout << "Adding a queen at: " << i%boardSize << ", " << i/boardSize << std::endl;
            node = node->addChild();
            node->getBoard()->addQueen(i%boardSize, i/boardSize);
            std::cout << "Node now has " << node->getBoard()->getNumOfQueens() << " queens" << std::endl;
            assert((int)node->getBoard()->getNumOfQueens() <= boardSize);
            if ((int)node->getBoard()->getNumOfQueens() == boardSize)
            {
                std::cout << "Found a solution" << std::endl;
                m_solutionNodes.push_back(node);
                /*
                 * FIXME: Endless loop if max number of solutions is not specified.
                 */
                if (m_solutionNodes.size() == (size_t)maxSolutionNum)
                    return;
                assert(node->getParent()); // The root board can't be full
                node = node->getParent();
                std::cout << "Node has " << node->getBoard()->getNumOfQueens() << " queens" << std::endl;
            }
        }
    }

    /*
    m_progressBar->pulse();
    */
}

