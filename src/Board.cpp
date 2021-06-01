#include "Board.h"
#include "config.h"
#include <algorithm>

Board::Board(int size)
    : m_size{size}
{
}

/*
Board::Board(const Board& another)
{
    m_size = another.getSize();
    m_lastCheckedCoords = nullptr;
    std::copy(another.m_queens.begin(), another.m_queens.end(), m_queens.begin());
}

Board& Board::operator=(const Board& another)
{
    m_size = another.getSize();
    m_lastCheckedCoords = nullptr;
    std::copy(another.m_queens.begin(), another.m_queens.end(), m_queens.begin());
    return *this;
}
*/

bool Board::operator==(const Board& another) const
{
    if (another.getNumOfQueens() != m_queens.size())
        return false;

    for (size_t i{}; i < m_queens.size(); ++i)
    {
        if (m_queens[i].getXPos() != another.getQueen(i)->getXPos() ||
            m_queens[i].getYPos() != another.getQueen(i)->getYPos())
            return false;
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
