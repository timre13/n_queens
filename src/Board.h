#pragma once

#include "Queen.h"
#include "config.h"
#include <cairomm/context.h>
#include <cairomm/refptr.h>
#include <gtkmm/drawingarea.h>
#include <vector>
#include <cassert>

class Board final : public Gtk::DrawingArea
{
private:
    int m_size{};
    std::vector<Queen> m_queens;
    Queen m_lastCheckedCoords{-1, -1};

public:
    Board(int size);
    Board(const Board& another) = delete;
    Board& operator=(const Board& another) = delete;

    static Board* createAsCopy(const Board* another)
    {
        assert(another);
        Board* newBoard = new Board{another->getSize()};
        /*
        for (size_t i{}; i < another->m_queens.size(); ++i)
            newBoard->m_queens.push_back(another->m_queens[i]);
        */
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

    bool wouldBeCorrect(int xPos, int yPos);

    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& context) override;
};
