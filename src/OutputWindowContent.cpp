#include "OutputWindowContent.h"
#include "config.h"
#include <gtkmm/application.h>
#include <gtkmm/enums.h>
#include <gtkmm/progressbar.h>
#include <gtkmm/window.h>
#include <memory>
#include <iostream>

#define DEBUG_LOG 0

OutputWindowContent::OutputWindowContent(std::shared_ptr<BoardWidget> boardWidget)
    :
    m_progressBar{std::make_unique<Gtk::ProgressBar>()},
    m_boardWidget{boardWidget},
    m_solutionTree{std::make_shared<TreeNode>(m_boardWidget->getBoardPtr())}, // The initial board is the root node
    m_prevSolutionButton{std::make_unique<Gtk::Button>()},
    m_nextSolutionButton{std::make_unique<Gtk::Button>()},
    m_noSolutionsLabel{std::make_unique<Gtk::Label>()}
{
    set_border_width(10);

    attach(*m_progressBar, 0, 0);
    m_progressBar->set_text("Solving...");
    m_progressBar->set_show_text();
    m_progressBar->set_pulse_step(1.0/(m_boardWidget->getBoardPtr()->getSize()*m_boardWidget->getBoardPtr()->getSize()));

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
    std::cout << "Found " << m_solutionBoards.size() << " unique solution(s)" << std::endl;

    this->remove(*m_progressBar);

    if (m_solutionBoards.size())
    {
        m_boardWidget->setBoardPtr(m_solutionBoards[m_shownSolutionI]);
        attach(*m_boardWidget, 1, 1);
    }

    if (m_solutionBoards.size() > 1)
    {
        attach(*m_prevSolutionButton, 0, 1);
        m_prevSolutionButton->set_image_from_icon_name("media-seek-backward");
        m_prevSolutionButton->set_state(Gtk::StateType::STATE_INSENSITIVE);
        m_prevSolutionButton->signal_pressed().connect(
            [this](){
                m_nextSolutionButton->set_state(Gtk::StateType::STATE_NORMAL);

                --m_shownSolutionI;
                assert(m_shownSolutionI >= 0);
                m_boardWidget->setBoardPtr(m_solutionBoards[m_shownSolutionI]);
                m_boardWidget->queue_draw();

                if (m_shownSolutionI == 0)
                    m_prevSolutionButton->set_state(Gtk::StateType::STATE_INSENSITIVE);
            }
        );

        attach(*m_nextSolutionButton, 2, 1);
        m_nextSolutionButton->set_image_from_icon_name("media-seek-forward");
        m_nextSolutionButton->signal_pressed().connect(
            [this](){
                m_prevSolutionButton->set_state(Gtk::StateType::STATE_NORMAL);

                ++m_shownSolutionI;
                assert(m_shownSolutionI < (int)m_solutionBoards.size());
                m_boardWidget->setBoardPtr(m_solutionBoards[m_shownSolutionI]);
                m_boardWidget->queue_draw();

                if (m_shownSolutionI == (int)m_solutionBoards.size()-1)
                    m_nextSolutionButton->set_state(Gtk::StateType::STATE_INSENSITIVE);
            }
        );
    }
    else if (m_solutionBoards.size() == 0)
    {
        m_noSolutionsLabel->set_text("No solutions found.");
        m_noSolutionsLabel->set_size_request(BOARD_WIDGET_DIMENSIONS_PX, BOARD_WIDGET_DIMENSIONS_PX);
        this->add(*m_noSolutionsLabel);
    }
}

static bool isInSolutionList(const std::vector<std::shared_ptr<Board>>& solutionBoards, const Board* board)
{
    for (auto& _board : solutionBoards)
    {
        if (*_board == *board)
            return true;
    }
    return false;
}

void OutputWindowContent::solveProblemNonrecursively(int maxSolutionNum)
{
    std::shared_ptr<TreeNode> node = m_solutionTree;
    int boardSize{node->getBoard()->getSize()};
    while (true)
    {
        int i{};
        if (node
            && node->getBoard()
            && node->getBoard()->getLastCheckedCoords().getXPos() != (Queen::coord_t)-1
            && node->getBoard()->getLastCheckedCoords().getYPos() != (Queen::coord_t)-1)
            i = node->getBoard()->getLastCheckedCoords().getXPos() +
                node->getBoard()->getLastCheckedCoords().getYPos() * boardSize + 1;

        while (i%boardSize < boardSize && i/boardSize < boardSize && !node->getBoard()->wouldBeCorrect(i%boardSize, i/boardSize))
        {
#if DEBUG_LOG
            std::cout << "Skipping " << i%boardSize << ", " << i/boardSize << std::endl;
#endif
            ++i;
        }
#if DEBUG_LOG
        std::cout << i << std::endl;
#endif
        if (i == boardSize*boardSize)
        {
#if DEBUG_LOG
            std::cout << "Branch finished" << std::endl;
#endif
            if (!node->getParent()) // FIXME: This does not work 
            {
#if DEBUG_LOG
                std::cout << "Solved board" << std::endl;
#endif
                return;
            }
            node = node->getParent();
#if DEBUG_LOG
            std::cout << "Node has " << node->getBoard()->getNumOfQueens() << " queens" << std::endl;
#endif
        }
        else
        {
#if DEBUG_LOG
            std::cout << "Adding a queen at: " << i%boardSize << ", " << i/boardSize << std::endl;
#endif
            node = node->addChild();
            node->getBoard()->addQueen(i%boardSize, i/boardSize);
#if DEBUG_LOG
            std::cout << "Node now has " << node->getBoard()->getNumOfQueens() << " queens" << std::endl;
#endif
            assert((int)node->getBoard()->getNumOfQueens() <= boardSize);
            if ((int)node->getBoard()->getNumOfQueens() == boardSize)
            {
                if (!isInSolutionList(m_solutionBoards, node->getBoard().get()))
                {
#if DEBUG_LOG
                    std::cout << "Found a solution" << std::endl;
#endif
                    m_solutionBoards.push_back(node->getBoard());
                }
                /*
                 * FIXME: Endless loop if max number of solutions is not specified.
                 */
                if (m_solutionBoards.size() == (size_t)maxSolutionNum)
                    return;
                assert(node->getParent()); // The root board can't be full
                node = node->getParent();
#if DEBUG_LOG
                std::cout << "Node has " << node->getBoard()->getNumOfQueens() << " queens" << std::endl;
#endif
            }
        }
    }

    // TODO
    //m_progressBar->pulse();
}

static void solveLevel(std::shared_ptr<TreeNode> node, std::vector<std::shared_ptr<Board>>& solutionBoards)
{
#if DEBUG_LOG
    std::cout << "Solving a level with " << node->getBoard()->getNumOfQueens() << " queens" << std::endl;
#endif

    if ((int)node->getBoard()->getNumOfQueens() == node->getBoard()->getSize())
    {
#if DEBUG_LOG
        std::cout << "Board is full" << std::endl;
#endif
        if (!isInSolutionList(solutionBoards, node->getBoard().get()))
            solutionBoards.push_back(node->getBoard());
        return;
    }

    auto boardPtr = node->getBoard();
    const int boardSize = boardPtr->getSize();

    for (int i{}; i < boardSize*boardSize; ++i)
    {
        if (boardPtr->wouldBeCorrect(i%boardSize, i/boardSize))
        {
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
        solveLevel(node->getChild(i), solutionBoards);

#if DEBUG_LOG
    std::cout << "End of child" << std::endl;
#endif
}

void OutputWindowContent::solveProblemRecursively()
{
    solveLevel(m_solutionTree, m_solutionBoards);
}

