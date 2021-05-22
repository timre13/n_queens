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

    Queen(int xPos, int yPos)
        : m_xPos{xPos}, m_yPos{yPos}
    {
    }
};
