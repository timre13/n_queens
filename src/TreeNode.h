#pragma once

#include <vector>
#include <cassert>
#include "Board.h"

class TreeNode final
{
private:
    std::vector<TreeNode*> m_children;
    TreeNode* m_parent{};
    Board* m_board{};

public:
    /*
    static inline TreeNode* createWithBoardSize(TreeNode* parent, int boardSize)
    {
        return new TreeNode{parent, boardSize};
    }

    static inline TreeNode* createFromBoard(TreeNode* parent, Board* board)
    {
        return new TreeNode{parent, board};
    }
    */

    /*
     * Create a new node by creating an empty board of size `boardSize`.
     * Set the parent to nullptr.
     */
    /*
    static inline TreeNode* createRootNode(int boardSize)
    {
        return new TreeNode{nullptr, new Board{boardSize}};
    }
    */

    /*
     * Create by copying the parent's board.
     */
    inline TreeNode(TreeNode* parent)
        :
        m_parent{parent}
    {
        assert(parent);
        assert(parent->getBoard());
        m_board = Board::createAsCopy(parent->getBoard()); // Copy board
    }

    /*
     * Create a new node and wrap the board.
     */
    inline TreeNode(Board* board)
        :
        m_parent{nullptr},
        m_board{board}
    {
        assert(board);
    }

    inline Board* getBoard() const { return m_board; }

    inline TreeNode* getParent() const { return m_parent; }

    inline size_t getNumOfChildren() const { return m_children.size(); }
    inline TreeNode* getChild(size_t index) const { assert(index < m_children.size()); return m_children[index]; }
    inline TreeNode* addChild()
    {
        auto newChild = new TreeNode{this};
        m_children.push_back(newChild);
        return newChild;
    }
};
