#include "BoardWidget.h"

BoardWidget::BoardWidget(std::shared_ptr<Board> board)
    :
    m_boardPtr{board}
{
    set_size_request(BOARD_WIDGET_DIMENSIONS_PX, BOARD_WIDGET_DIMENSIONS_PX);
}

bool BoardWidget::on_draw(const Cairo::RefPtr<Cairo::Context>& context)
{
    context->scale(BOARD_WIDGET_DIMENSIONS_PX, BOARD_WIDGET_DIMENSIONS_PX);
    context->set_source_rgb(1, 1, 1);
    context->paint();

    context->set_source_rgb(0, 0, 0);
    context->set_line_width(0.001);
    for (int i{1}; i < m_boardPtr->getSize(); ++i)
    {
        context->move_to((double)i/m_boardPtr->getSize(), 0);
        context->line_to((double)i/m_boardPtr->getSize(), 1);
        context->stroke();
    }
    for (int i{1}; i < m_boardPtr->getSize(); ++i)
    {
        context->move_to(0, (double)i/m_boardPtr->getSize());
        context->line_to(1, (double)i/m_boardPtr->getSize());
        context->stroke();
    }

    for (auto& queen : *m_boardPtr)
    {
        const int queenX{queen.getXPos()};
        const int queenY{queen.getYPos()};

        context->set_source_rgb(0, 0.5, 0.5);
        context->move_to(0.5, 0.5);
        const double arcR{1.0/m_boardPtr->getSize()/2};
        context->arc(arcR*2*queenX+arcR, arcR*2*queenY+arcR, arcR, 0, 2*M_PI);
        context->fill();
    }

    // What's this value?
    return true;
}

