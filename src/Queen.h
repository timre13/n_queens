#pragma once

class Queen final
{
private:
    /*
     * 0-based coordinates
     */
    int m_xPos = -1;
    int m_yPos = -1;

public:
    inline int getXPos() const { return m_xPos; }
    inline int getYPos() const { return m_yPos; }

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

    Queen(int xPos, int yPos)
        : m_xPos{xPos}, m_yPos{yPos}
    {
    }
};
