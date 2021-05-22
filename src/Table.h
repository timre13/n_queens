#pragma once

#include "Queen.h"
#include "config.h"
#include <cairomm/context.h>
#include <cairomm/refptr.h>
#include <gtkmm/drawingarea.h>
#include <vector>
#include <cassert>

class Table final : public Gtk::DrawingArea
{
private:
    int m_size{};
    std::vector<Queen> m_queens;

public:
    Table(int size);

    inline int getSize() const { return m_size; }

    inline void clearQueens() { m_queens.clear(); }
    inline size_t getNumOfQueens() const { return m_queens.size(); }
    inline void setSize(int size) { assert(size >= 4 && size <= MAX_TABLE_SIZE); m_size = size; }
    inline void addQueen(int xPos, int yPos) { assert((int)m_queens.size() < m_size); m_queens.push_back({xPos, yPos}); }

    bool wouldBeCorrect(int xPos, int yPos) const;

    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& context) override;
};
