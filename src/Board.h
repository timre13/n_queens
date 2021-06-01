#pragma once

#include "Queen.h"
#include "config.h"
#include <vector>
#include <cassert>

class Board
{
private:
    int m_size{};
    std::vector<Queen> m_queens;
    Queen m_lastCheckedCoords{-1, -1};

public:
    Board(int size);
    Board(const Board& another) = delete;
    Board& operator=(const Board& another) = delete;

    bool operator==(const Board& another) const;

    static Board* createAsCopy(const Board* another)
    {
        assert(another);
        Board* newBoard = new Board{another->getSize()};
        newBoard->m_queens = another->m_queens;
        return newBoard;
    }

    inline const Queen& getLastCheckedCoords() const { return m_lastCheckedCoords; }

    inline int getSize() const { return m_size; }

    inline void clearQueens() { m_queens.clear(); }
    inline size_t getNumOfQueens() const { return m_queens.size(); }
    inline void setSize(int size) { assert(size >= 4 && size <= MAX_BOARD_SIZE); m_size = size; }
    inline void addQueen(int xPos, int yPos)
    {
        assert((int)m_queens.size() < m_size);
        assert(xPos < m_size && yPos < m_size);
        m_queens.push_back({xPos, yPos});
    }
    inline Queen* getLastAddedQueen() { return m_queens.size() ? &(m_queens[m_queens.size()]) : nullptr; }
    inline Queen* getQueen(size_t index) { assert(index < m_queens.size()); return &m_queens[index]; }
    inline const Queen* getQueen(size_t index) const { assert(index < m_queens.size()); return &m_queens[index]; }
    inline std::vector<Queen>::const_iterator begin() const { return m_queens.begin(); }
    inline std::vector<Queen>::const_iterator end() const { return m_queens.end(); }

    bool wouldBeCorrect(int xPos, int yPos);
};
