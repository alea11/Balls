#include "World.hpp"
#include "Painter.hpp"
#include <fstream>



// Длительность одного тика симуляции.
// Подробнее см. update()
// Изменять не следует
static constexpr double timePerTick = 0.001;


std::istream& operator>>(std::istream& stream, Point& point) 
{
    double x;
    double y;
    stream >> x >> y;
    point = Point(x, y);
    return stream;
}

std::istream& operator>>(std::istream& stream, Color& color) 
{
    double red;
    double green;
    double blue;
    stream >> red >> green >> blue;
    color = Color(red, green, blue);
    return stream;
}



/**
 * Конструирует объект мира для симуляции
 * @param worldFilePath путь к файлу модели мира
 */
World::World(const std::string& worldFilePath) 
{
    std::ifstream stream(worldFilePath);

    stream >> topLeft;
    stream >> bottomRight;
    
    physics.setWorldBox(topLeft, bottomRight);
    

    // Здесь не хватает обработки ошибок, но на текущем
    // уровне прохождения курса нас это устраивает
    while (stream.peek(), stream.good())
    {
        Point center;
        Point vec;
        Color color;
        double radius;
        bool isCollidable;

        stream >> center;
        stream >> vec;
        stream >> color;
        stream >> radius;
        stream >> std::boolalpha >> isCollidable;

        Ball ball = Ball( radius, 1 , color, isCollidable);
        ball.setCenter (center);
        ball.setVelocity ( Velocity(vec));
        balls.push_back(ball);        
    }
}

/// @brief Отображает состояние мира
void World::show(Painter& painter) const 
{
    // Рисуем белый прямоугольник, отображающий границу
    // мира
    painter.draw(topLeft, bottomRight, Color(1, 1, 1));

    // Вызываем отрисовку каждого шара
    for (const Ball& ball : balls) 
    {
        ball.draw(painter);
    }
}

/// @brief Обновляет состояние мира
void World::update(double time) {
    /**
     * В реальном мире время течет непрерывно. Однако
     * компьютеры дискретны по своей природе. Поэтому
     * симуляцию взаимодействия шаров выполняем дискретными
     * "тиками". Т.е. если с момента прошлой симуляции
     * прошло time секунд, time / timePerTick раз обновляем
     * состояние мира. Каждое такое обновление - тик -
     * в physics.update() перемещаем шары и обрабатываем
     * коллизии - ситуации, когда в результате перемещения
     * один шар пересекается с другим или с границей мира.
     * В общем случае время не делится нацело на
     * длительность тика, сохраняем остаток в restTime
     * и обрабатываем на следующей итерации.
     */

    // учитываем остаток времени, который мы не "доработали" при прошлом update
    time += restTime;
    const auto ticks = static_cast<size_t>(std::floor(time / timePerTick));
    restTime = time - double(ticks) * timePerTick;

    physics.update(balls, ticks);
}