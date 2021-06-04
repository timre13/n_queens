#pragma once

#include <vector>
#include <cassert>
#include <memory>
#include "Board.h"

class TreeNode final : public std::enable_shared_from_this<TreeNode>
{
private:
    std::vector<std::shared_ptr<TreeNode>> m_children;
    std::weak_ptr<TreeNode> m_parent;
    std::shared_ptr<Board> m_board;

public:

    /*
     * Create by copying the parent's board.
     */
    inline TreeNode(std::shared_ptr<TreeNode> parent)
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
    inline TreeNode(std::shared_ptr<Board> board)
        :
        m_board{board}
    {
        assert(board);
    }

    inline std::shared_ptr<Board> getBoard() const { return m_board; }
    inline std::shared_ptr<TreeNode> getParent() const { return m_parent.lock(); }

    inline size_t getNumOfChildren() const { return m_children.size(); }
    inline std::shared_ptr<TreeNode> getChild(size_t index) const { assert(index < m_children.size()); return m_children[index]; }
    inline std::shared_ptr<TreeNode> addChild()
    {
        m_children.push_back(std::make_shared<TreeNode>(shared_from_this()));
        return m_children.back();
    }
};
