#include "OutputWindowContent.h"
#include <gtkmm/application.h>
#include <gtkmm/window.h>

OutputWindowContent::OutputWindowContent(Table* table)
    :
    m_table{table}
{
    set_border_width(10);

    attach(*m_table, 0, 0);
}

