#ifndef MOVER_H
#define MOVER_H
#include "coordinates.h"

/*!
 * \brief Класс, создающий поле и перемещающегося по нему юнита
 *
 * Юнит может двигаться в 8 направлениях - вправо, влево, вниз, вверх и по-диагонали
 * Если поле, на которое юнит пытается подвинуться, не существует, функция возвращает false
 *
 */

class mover
{
public:
    //! Конструктор класса
    //! \param coordinatesOfMover Задаёт изначальную позицию юнита
    //! \param sizeOfStreet Задаёт размер поля, а конкретнее - номер крайней ячейки
    //!
    //! \throw std::out_of_range В случае передачи конструтору переменной, равной нулю
    mover(uint64_t coordinatesOfMover, uint64_t sizeOfStreet);
    //! Пустой деструктор
    ~mover();

    //! Получить текущую позицию
    const coordinates &currentPosition() const;

    //! Сдвинуться вверх
    bool moveUp();
    //! Сдвинуться вниз
    bool moveDown();
    //! Сдвинуться влево
    bool moveLeft();
    //! Сдвинуться
    bool moveRight();

    //! Сдвинуться вверх и вправо
    bool moveUpAndRight();
    //! Сдвинуться вверх и влево
    bool moveUpAndLeft();
    //! Сдвинуться вниз и вправо
    bool moveDownAndRight();
    //! Сдвинуться вниз и влево
    bool moveDownAndLeft();

    //! Перейти на другую сторону и сдвинуться на 1 вправо
    bool switchSideAndGoRight();
    //! Перейти на другую сторону и сдвинуться на 1 влево
    bool switchSideAndGoLeft();
    //! Перейти на другую сторону
    bool switchSide();

    //! \brief Дойти до ячейки с номером point
    //! \return Возвращает число шагов от начального положения до конечной точки
    uint64_t moveTo(uint64_t point);
    //! \brief Дойти до ячейки с номером point
    //! \return Возвращает число шагов от начального положения до конечной точки
    uint64_t moveTo(const coordinates &point);
    //! \brief Дойти до ячейки с номером point
    //! \return Возвращает число шагов от начального положения до конечной точки
    uint64_t goHome();
    const coordinates &sizeOfStreet() const;

private:
    //! \brief Проверить возможность движения по координате
    //!
    //! Возвращает true, если позиция moveTo находится на расстоянии не больше 1 от текущей позиции, и если такая точка на поле существует
    bool isMoveAvailable(coordinates moveTo);

    //! Размер поля
    coordinates m_sizeOfStreet;
    //! Текущая позиция юнита
    coordinates m_currentPosition;
    //! Изначальная позиция
    coordinates m_startingPosition;

};

#endif // MOVER_H
