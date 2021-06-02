#pragma once

#include "config.h"
#include <stdint.h>

class Queen final
{
public:
    using coord_t = QUEEN_COORD_TYPE;

private:
    /*
     * 0-based coordinates
     */
    coord_t m_xPos = (coord_t)-1;
    coord_t m_yPos = (coord_t)-1;

public:
    inline coord_t getXPos() const { return m_xPos; }
    inline coord_t getYPos() const { return m_yPos; }

    inline bool operator<(const Queen& another) const
    {
        if (m_xPos == another.m_xPos)
            return m_yPos < another.m_yPos;

        return m_xPos < another.m_xPos;
    }

    inline bool operator!=(const Queen& another) const
    {
        return (m_xPos != another.m_xPos) || (m_yPos != another.m_yPos);
    }

    inline Queen(coord_t xPos, coord_t yPos)
        : m_xPos{xPos}, m_yPos{yPos}
    {
    }
};
