#pragma once
#include "Painter.hpp"
#include "Point.hpp"
#include "Velocity.hpp"

class Ball {
public:
    Ball(const double radius, const double density, const Color color, const bool isCollidable = true);
    void setVelocity(const Velocity& velocity);
    Velocity getVelocity() const;
    void draw(Painter& painter) const;
    void setCenter(const Point& center);
    Point getCenter() const;
    
    double getRadius() const;
    double getMass() const;
    Color getColor() const;
    bool getCollidable() const;
    
private:
    Point _center;    
    Velocity _velocity;

    double _radius;
    double _mass;
    Color _color;  
    bool _isCollidable;
};
