#include "Ball.hpp"
//#include <cmath>
//#define M_PI 3.14159265358979323846

Ball::Ball(const double radius, const double density, const Color color, const bool isCollidable)
{
    _radius = radius;
    _color = color;
    _isCollidable = isCollidable;

    // далее в расчетах важна относительная масса (при взаимодействии 2-х шаров)
    //, поэтому общий коэффициент 4/3 * pi - можно не применять
    _mass = density * radius * radius * radius  /*  * 4/3 * M_PI   */  ;    
}

/**
 * Задает скорость объекта
 * @param velocity новое значение скорости
 */
void Ball::setVelocity(const Velocity& velocity) 
{
    _velocity = velocity;
}

/**
 * @return скорость объекта
 */
Velocity Ball::getVelocity() const 
{
    return _velocity;
}

/**
 * @brief Выполняет отрисовку объекта
 * @details объект Ball абстрагирован от конкретного
 * способа отображения пикселей на экране. Он "знаком"
 * лишь с интерфейсом, который предоставляет Painter
 * Рисование выполняется путем вызова painter.draw(...)
 * @param painter контекст отрисовки
 */
void Ball::draw(Painter& painter) const 
{
    painter.draw(_center, _radius, _color);
}

/**
 * Задает координаты центра объекта
 * @param center новый центр объекта
 */
void Ball::setCenter(const Point& center) 
{
    _center = center;
}

/**
 * @return центр объекта
 */
Point Ball::getCenter() const 
{
    return _center;
}

/**
 * @brief Возвращает радиус объекта
 * @details обратите внимание, что метод setRadius()
 * не требуется
 */
double Ball::getRadius() const 
{
    return _radius;
}

/**
 * @brief Возвращает массу объекта
 * @details В нашем приложении считаем, что все шары
 * состоят из одинакового материала с фиксированной
 * плотностью. В этом случае масса в условных единицах
 * эквивалентна объему: PI * radius^3 * 4. / 3.
 */
double Ball::getMass() const 
{
    return _mass;
}

Color Ball::getColor() const
{    
    return _color;
}

bool Ball::getCollidable() const
{
    return _isCollidable;
}
