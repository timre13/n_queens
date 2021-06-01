#include "Board.h"
#include "config.h"
#include <algorithm>

Board::Board(int size)
    : m_size{size}
{
}

bool Board::operator==(const Board& another) const
{
    if (another.getNumOfQueens() != m_queens.size())
        return false;

    auto it1 = m_queens.begin();
    auto it2 = another.m_queens.begin();
    for (; it1 != m_queens.end();)
    {
        if (*it1 != *it2)
            return false;
        ++it1; ++it2;
    }

    return true;
}

bool Board::wouldBeCorrect(int xPos, int yPos)
{
    assert(xPos < m_size && yPos < m_size);
    m_lastCheckedCoords = {xPos < m_size ? xPos : -1, yPos < m_size ? yPos : -1};

    for (auto& queen : m_queens)
    {
        // Row and column check
        if (queen.getXPos() == xPos || queen.getYPos() == yPos)
            return false;

        // Diagonal check
        if (std::abs(xPos - queen.getXPos()) == std::abs(yPos - queen.getYPos()))
            return false;
    }

    return true;
}
