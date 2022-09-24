#include "mover.h"

mover::mover(uint64_t coordinateOfMover, uint64_t sizeOfStreet) :
    m_sizeOfStreet(sizeOfStreet),
    m_currentPosition(coordinateOfMover),
    m_startingPosition(coordinateOfMover)
{

}

mover::~mover()
{

}

bool mover::isMoveAvailable(coordinates moveTo)
{
    return ((moveTo.x() >= m_currentPosition.x() - 1) and (moveTo.x() <= m_currentPosition.x() + 1)
            and (m_currentPosition != moveTo)) and (moveTo.number() <= m_sizeOfStreet.number());
}

const coordinates &mover::sizeOfStreet() const
{
    return m_sizeOfStreet;
}

const coordinates &mover::currentPosition() const
{
    return m_currentPosition;
}

bool mover::moveUp()
{
    // Если юнит уже наверху поля, функция возвращает false
    if (m_currentPosition.y() == 0)
        return false;

    if(isMoveAvailable(coordinates(m_currentPosition.x(), m_currentPosition.y() - 1)))
    {
        m_currentPosition.changeY();
        return true;
    }
    return false;
}

bool mover::moveDown()
{
    // Если юнит уже внизу поля, функция возвращает false
    if (m_currentPosition.y() == 1)
        return false;

    if(isMoveAvailable(coordinates(m_currentPosition.x(), m_currentPosition.y() + 1)))
    {
        m_currentPosition.changeY();
        return true;
    }
    return false;
}

bool mover::moveLeft()
{
    if (m_currentPosition.x() == 1)
        return false;

    if(isMoveAvailable(coordinates(m_currentPosition.x() - 1, m_currentPosition.y())))
    {
        m_currentPosition.moveLeft();
        return true;
    }
    return false;
}

bool mover::moveRight()
{
    if(isMoveAvailable(coordinates(m_currentPosition.x() + 1, m_currentPosition.y())))
    {
        m_currentPosition.moveRight();
        return true;
    }
    return false;
}

bool mover::moveUpAndRight()
{
    // Если юнит уже наверху поля, функция возвращает false
    if (m_currentPosition.y() == 0)
        return false;

    if(isMoveAvailable(coordinates(m_currentPosition.x() + 1, m_currentPosition.y() - 1)))
    {
        m_currentPosition.changeY();
        m_currentPosition.moveRight();
        return true;
    }
    return false;
}

bool mover::moveUpAndLeft()
{
    // Если юнит уже наверху поля, функция возвращает false
    if (m_currentPosition.y() == 0)
        return false;
    if (m_currentPosition.x() == 1)
        return false;

    if(isMoveAvailable(coordinates(m_currentPosition.x() - 1, m_currentPosition.y() - 1)))
    {
        m_currentPosition.changeY();
        m_currentPosition.moveLeft();
        return true;
    }
    return false;
}

bool mover::moveDownAndRight()
{
    // Если юнит уже внизу поля, функция возвращает false
    if (m_currentPosition.y() == 1)
            return false;

    if(isMoveAvailable(coordinates(m_currentPosition.x() + 1, m_currentPosition.y() + 1)))
    {
        m_currentPosition.changeY();
        m_currentPosition.moveRight();
        return true;
    }
    return false;
}

bool mover::moveDownAndLeft()
{
    // Если юнит уже внизу поля, функция возвращает false
    if (m_currentPosition.y() == 1)
        return false;
    if (m_currentPosition.x() == 1)
        return false;

    if(isMoveAvailable(coordinates(m_currentPosition.x() - 1, m_currentPosition.y() + 1)))
    {
        m_currentPosition.changeY();
        m_currentPosition.moveLeft();
        return true;
    }
    return false;
}

bool mover::switchSideAndGoRight()
{
    // try to move down and right or down and left
    // If it didn't work, then return false
    if(moveUpAndRight() == 0)
        if (moveDownAndRight() == 0)
            return false;

    return true;
}

bool mover::switchSideAndGoLeft()
{
    // try to move up and right or up and left
    // If it didn't work, then return false
    if(moveDownAndLeft() == 0)
        if(moveDownAndLeft() == 0)
            return false;

    return true;
}

bool mover::switchSide()
{
    // Try to move up or down
    if(moveDown() == 0)
        if(moveUp() == 0)
            return false;

    return true;
}

uint64_t mover::moveTo(uint64_t point)
{
    // Перегружает метод
    return moveTo(coordinates(point));
}

uint64_t mover::moveTo(const coordinates &point)
{
    uint64_t steps = 0;

    // Первым делом нужно перейти на нужную линию поля
    if(m_currentPosition.y() != point.y() and m_currentPosition.x() < point.x())
    {
        if (switchSideAndGoRight() == true)
            steps++;
    }
    else if(m_currentPosition.y() != point.y() and m_currentPosition.x() > point.x())
    {
        if (switchSideAndGoLeft() == true)
            steps++;
    }
    else if(m_currentPosition.y() != point.y() and m_currentPosition.x() == point.x())
    {
        if (switchSide() == true)
            steps++;
    }

    // Теперь добраться до нужной точки до прямой, пока они не совпадут
    if(m_currentPosition.x() < point.x())
    {
        while(m_currentPosition.x() != point.x())
        {
            moveRight();
            steps++;
        }
    }
    else if(m_currentPosition.x() > point.x())
    {
        while(m_currentPosition.x() != point.x())
        {
            moveLeft();
            steps++;
        }
    }

    return steps;
}

uint64_t mover::goHome()
{
    return moveTo(m_startingPosition);
}
