#include "Board.h"
#include "config.h"
#include <giomm/icon.h>
#include <gtkmm/enums.h>
#include <gtkmm/label.h>
#include <gtkmm/image.h>

Board::Board(int size)
    : m_size{size}
{
    set_size_request(BOARD_WIDGET_DIMENSIONS_PX, BOARD_WIDGET_DIMENSIONS_PX);
}

bool Board::on_draw(const Cairo::RefPtr<Cairo::Context>& context)
{
    context->scale(BOARD_WIDGET_DIMENSIONS_PX, BOARD_WIDGET_DIMENSIONS_PX);
    context->set_source_rgb(1, 1, 1);
    context->paint();

    context->set_source_rgb(0, 0, 0);
    context->set_line_width(0.001);
    for (int i{1}; i < m_size; ++i)
    {
        context->move_to((double)i/m_size, 0);
        context->line_to((double)i/m_size, 1);
        context->stroke();
    }
    for (int i{1}; i < m_size; ++i)
    {
        context->move_to(0, (double)i/m_size);
        context->line_to(1, (double)i/m_size);
        context->stroke();
    }

    for (auto& queen : m_queens)
    {
        const int queenX{queen.getXPos()};
        const int queenY{queen.getYPos()};

        context->set_source_rgb(0, 0.5, 0.5);
        context->move_to(0.5, 0.5);
        const double arcR{1.0/m_size/2};
        context->arc(arcR*2*queenX+arcR, arcR*2*queenY+arcR, arcR, 0, 2*M_PI);
        context->fill();
    }

    // What's this value?
    return true;
}

bool Board::wouldBeCorrect(int xPos, int yPos) const
{
    for (auto& queen : m_queens)
    {
        // Row and column check
        if (queen.getXPos() == xPos || queen.getYPos() == yPos)
            return false;

        // Diagonal check
        if (std::abs(xPos - queen.getXPos()) == std::abs(yPos - queen.getYPos()))
            return false;
        /*
        for (int i{-m_size}; i <= m_size; ++i)
        {
            if ((xPos == queen.getXPos() + i && yPos == queen.getYPos() - i) || // Top right
                (xPos == queen.getXPos() - i && yPos == queen.getYPos() - i) || // Top left
                (xPos == queen.getXPos() - i && yPos == queen.getYPos() + i) || // Bottom left
                (xPos == queen.getXPos() + i && yPos == queen.getYPos() + i))   // Bottom right
                return false;
        }
        */
    }

    return true;
}