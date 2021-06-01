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
    Board* m_boardPtr{};

public:
    BoardWidget(Board* board);

    void setBoardPtr(Board* boardPtr) { m_boardPtr = boardPtr; }

    const Board* getBoardPtr() const { return m_boardPtr; }
    Board* getBoardPtr() { return m_boardPtr; }

    virtual bool on_draw(const Cairo::RefPtr<Cairo::Context>& context) override;
};
