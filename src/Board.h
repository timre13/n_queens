#pragma once

#include "Queen.h"
#include "config.h"
#include <set>
#include <cassert>
#include <memory>

class Board
{
private:
    Queen::coord_t m_size{};
    std::set<Queen> m_queens;
    Queen m_lastCheckedCoords{(Queen::coord_t)-1, (Queen::coord_t)-1};

public:
    Board(Queen::coord_t size);
    Board(const Board& another) = delete;
    Board& operator=(const Board& another) = delete;

    bool operator==(const Board& another) const;

    static std::shared_ptr<Board> createAsCopy(std::shared_ptr<Board> another)
    {
        assert(another);
        auto newBoard = std::make_shared<Board>(another->getSize());
        newBoard->m_queens = another->m_queens;
        return newBoard;
    }

    inline const Queen& getLastCheckedCoords() const { return m_lastCheckedCoords; }

    inline Queen::coord_t getSize() const { return m_size; }
    inline void setSize(Queen::coord_t size)
    {
        assert(size >= 4);
        assert(size <= MAX_BOARD_SIZE);
        assert(size < (int)(Queen::coord_t)-1);
        m_size = size;
    }

    inline void clearQueens() { m_queens.clear(); }
    inline size_t getNumOfQueens() const { return m_queens.size(); }
    inline void addQueen(Queen::coord_t xPos, Queen::coord_t yPos)
    {
        assert((int)m_queens.size() < m_size);
        assert(xPos < m_size && yPos < m_size);
        m_queens.insert({xPos, yPos});
    }
    inline std::set<Queen>::const_iterator begin() const { return m_queens.begin(); }
    inline std::set<Queen>::const_iterator end() const { return m_queens.end(); }

    bool wouldBeCorrect(Queen::coord_t xPos, Queen::coord_t yPos);
};
