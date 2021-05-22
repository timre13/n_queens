#include "OutputWindowContent.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

OutputWindowContent::OutputWindowContent(Board* board)
    :
    m_board{board}
{
    set_border_width(10);

    attach(*m_board, 0, 0);
}

