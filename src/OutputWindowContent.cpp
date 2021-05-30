#include "OutputWindowContent.h"
#include "config.h"
#include <gtkmm/application.h>
#include <gtkmm/enums.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/window.h>
#include <memory>
#include <iostream>

#define DEBUG_LOG 0

OutputWindowContent::OutputWindowContent(Board* board)
    :
    m_progressBar{std::make_unique<Gtk::ProgressBar>()},
    m_solutionTree{std::make_unique<TreeNode>(TreeNode{board})}, // The initial board is the root node
    m_prevSolutionButton{std::make_unique<Gtk::Button>()},
    m_nextSolutionButton{std::make_unique<Gtk::Button>()},
    m_noSolutionsLabel{std::make_unique<Gtk::Label>()}
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
     *
     * XXX: Multi-threading
     */
    //solveProblemNonrecursively(100);
    solveProblemRecursively();
    std::cout << "Found " << m_solutionNodes.size() << " solution(s)" << std::endl;
    this->remove(*m_progressBar);

    if (m_solutionNodes.size())
    {
        attach(*m_prevSolutionButton, 0, 1);
        m_prevSolutionButton->set_image_from_icon_name("media-seek-backward");
        m_prevSolutionButton->set_state(Gtk::StateType::STATE_INSENSITIVE);
        m_prevSolutionButton->signal_pressed().connect(
            [this](){
                m_nextSolutionButton->set_state(Gtk::StateType::STATE_NORMAL);

                this->remove(*m_solutionNodes[m_shownSolutionI]->getBoard());
                --m_shownSolutionI;
                assert(m_shownSolutionI >= 0);
                attach(*m_solutionNodes[m_shownSolutionI]->getBoard(), 1, 1);
                show_all_children();

                if (m_shownSolutionI == 0)
                    m_prevSolutionButton->set_state(Gtk::StateType::STATE_INSENSITIVE);
            }
        );

        attach(*m_solutionNodes[m_shownSolutionI]->getBoard(), 1, 1);

        attach(*m_nextSolutionButton, 2, 1);
        m_nextSolutionButton->set_image_from_icon_name("media-seek-forward");
        m_nextSolutionButton->signal_pressed().connect(
            [this](){
                m_prevSolutionButton->set_state(Gtk::StateType::STATE_NORMAL);

                this->remove(*m_solutionNodes[m_shownSolutionI]->getBoard());
                ++m_shownSolutionI;
                assert(m_shownSolutionI < (int)m_solutionNodes.size());
                attach(*m_solutionNodes[m_shownSolutionI]->getBoard(), 1, 1);
                show_all_children();

                if (m_shownSolutionI == (int)m_solutionNodes.size()-1)
                    m_nextSolutionButton->set_state(Gtk::StateType::STATE_INSENSITIVE);
            }
        );
    }
    else
    {
        m_noSolutionsLabel->set_text("No solutions found.");
        m_noSolutionsLabel->set_size_request(BOARD_WIDGET_DIMENSIONS_PX, BOARD_WIDGET_DIMENSIONS_PX);
        this->add(*m_noSolutionsLabel);
    }
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
            // TODO: Filter out duplicates
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

static void solveLevel(TreeNode* node, std::vector<TreeNode*>& solutionNodes)
{
#if DEBUG_LOG
    std::cout << "Solving a level with " << node->getBoard()->getNumOfQueens() << " queens" << std::endl;
#endif

    if ((int)node->getBoard()->getNumOfQueens() == node->getBoard()->getSize())
    {
#if DEBUG_LOG
        std::cout << "Board is full" << std::endl;
#endif
        solutionNodes.push_back(node);
        return;
    }

    Board* const boardPtr = node->getBoard();
    const int boardSize = boardPtr->getSize();

    for (int i{}; i < boardSize*boardSize; ++i)
    {
        if (boardPtr->wouldBeCorrect(i%boardSize, i/boardSize))
        {
            // TODO: Filter out duplicates

            node->addChild()->getBoard()->addQueen(i%boardSize, i/boardSize);
#if DEBUG_LOG
            std::cout << "Added a child" << std::endl;
#endif
        }
        else
        {
#if DEBUG_LOG
            std::cout << "Skipping " << i%boardSize << ", " << i/boardSize << std::endl;
#endif
        }
    }
#if DEBUG_LOG
    std::cout << "End of a level" << std::endl;
#endif

    for (size_t i{}; i < node->getNumOfChildren(); ++i)
        solveLevel(node->getChild(i), solutionNodes);

#if DEBUG_LOG
    std::cout << "End of child" << std::endl;
#endif
}

void OutputWindowContent::solveProblemRecursively()
{
    solveLevel(m_solutionTree.get(), m_solutionNodes);
}

