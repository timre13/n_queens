#include "BoardWidget.h"
#include <cairomm/enums.h>

BoardWidget::BoardWidget(std::shared_ptr<Board> board)
    :
    m_boardPtr{board}
{
    set_size_request(BOARD_WIDGET_DIMENSIONS_PX, BOARD_WIDGET_DIMENSIONS_PX);
}

bool BoardWidget::on_draw(const Cairo::RefPtr<Cairo::Context>& context)
{
    const auto boardSize = m_boardPtr->getSize();

    context->scale(BOARD_WIDGET_DIMENSIONS_PX, BOARD_WIDGET_DIMENSIONS_PX);
    context->set_source_rgb(1, 1, 1);
    context->paint();

    context->set_source_rgb(0, 0, 0);
    context->set_line_width(0.001);
    for (int i{1}; i < m_boardPtr->getSize(); ++i)
    {
        context->move_to((double)i/boardSize, 0);
        context->line_to((double)i/boardSize, 1);
        context->stroke();
    }
    for (int i{1}; i < m_boardPtr->getSize(); ++i)
    {
        context->move_to(0, (double)i/boardSize);
        context->line_to(1, (double)i/boardSize);
        context->stroke();
    }

    for (auto& queen : *m_boardPtr)
    {
        const int queenX{queen.getXPos()};
        const int queenY{queen.getYPos()};

        context->set_source_rgb(0, 0.5, 0.5);
        context->move_to(0.5, 0.5);
        const double arcR{1.0/boardSize/2};
        context->arc(arcR*2*queenX+arcR, arcR*2*queenY+arcR, arcR, 0, 2*M_PI);
        context->fill();

        context->set_line_width(0.006);
        context->set_line_cap(Cairo::LINE_CAP_ROUND);
        context->set_source_rgba(1, 0, 0, 0.8);

        auto drawMarkAt{
            [&context, &boardSize](int fieldX, int fieldY){
                static constexpr double spacing = 0.01;
                context->move_to(fieldX*(1.0/boardSize)+spacing, fieldY*(1.0/boardSize)+spacing); // Top left
                context->line_to((fieldX+1)*(1.0/boardSize)-spacing, (fieldY+1)*(1.0/boardSize)-spacing); // Bottom right
                context->stroke();
                context->move_to(fieldX*(1.0/boardSize)+spacing, (fieldY+1)*(1.0/boardSize)-spacing); // Bottom left
                context->line_to((fieldX+1)*(1.0/boardSize)-spacing, fieldY*(1.0/boardSize)+spacing); // Top right
                context->stroke();
            }
        };

        if (m_shouldMarkUnusableFields)
        {
            for (int i{}; i < boardSize; ++i)
            {
                if (i != queenX)
                    drawMarkAt(i, queenY);
            }
            for (int i{}; i < boardSize; ++i)
            {
                if (i != queenY)
                    drawMarkAt(queenX, i);
            }
            for (int i{}; i < boardSize; ++i)
            {
                int x = queenX-std::min(queenX, queenY)+i;
                int y = queenY-std::min(queenX, queenY)+i;
                if (x != queenX || y != queenY)
                    drawMarkAt(x, y);
            }
            for (int i{}; i < boardSize; ++i)
            {
                if (queenX+queenY-i != queenX || i != queenY)
                    drawMarkAt(queenX+queenY-i, i);
            }
        }
    }

    // What's this value?
    return true;
}

