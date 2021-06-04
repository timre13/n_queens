#pragma once

#include "config.h"
#include "Board.h"
#include <cairomm/context.h>
#include <cairomm/refptr.h>
#include <gtkmm/drawingarea.h>
#include <giomm/icon.h>
#include <gtkmm/enums.h>
#include <gtkmm/label.h>
#include <gtkmm/image.h>

class BoardWidget  final : public Gtk::DrawingArea
{
private:
    std::shared_ptr<Board> m_boardPtr;

public:
    BoardWidget(std::shared_ptr<Board> board);

    void setBoardPtr(std::shared_ptr<Board> board) { m_boardPtr = board; }

    const std::shared_ptr<Board> getBoardPtr() const { return m_boardPtr; }
    std::shared_ptr<Board> getBoardPtr() { return m_boardPtr; }

    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& context) override;
};
