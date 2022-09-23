#include "coordinates.h"

coordinates::coordinates(uint64_t x, uint64_t y)
{
    m_x = x;
    m_y = y;

    updateNumber();
}

coordinates::coordinates(uint64_t number)
{
    if(number == 0)
        throw std::out_of_range ("The number passed to the class constructor cannot be 0!");

    m_x = ceil(double(number) / 2);
    m_y = number % 2;

    m_number = number;
}

coordinates::coordinates()
{
    m_x = 1;
    m_y = 0;

    m_number = 1;
}

uint64_t coordinates::x() const
{
    return m_x;
}

uint64_t coordinates::y() const
{
    return m_y;
}

void coordinates::changeY()
{
    if (m_y == 0)
        m_y = 1;
    else
        m_y = 0;

    updateNumber();
}

void coordinates::moveRight()
{
    m_x += 1;
    updateNumber();
}

void coordinates::moveLeft()
{
    m_x -= 1;
    updateNumber();
}

const bool coordinates::operator!=(const coordinates &otherCoords)
{
    return !(m_x == otherCoords.x() and m_y == otherCoords.y());
}

const bool coordinates::operator ==(const coordinates &otherCoords)
{
    return m_x == otherCoords.x() and m_y == otherCoords.y();
}

uint64_t coordinates::number() const
{
    return m_number;
}

void coordinates::updateNumber()
{
    m_number = (m_x * 2) - m_y;
}

