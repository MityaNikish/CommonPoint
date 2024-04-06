#include "point.hpp"
#include <cmath>

namespace 
{
    constexpr double EPSILON = 0.000001f;

    bool isZero(double number)
    {
        return fabs(number) < EPSILON;
    }
}

double Point::getX() const noexcept
{
    return _x;
}

double Point::getY() const noexcept
{
    return _y;
}

double Point::getZ() const noexcept
{
    return _z;
}

void Point::setX(double number)
{
    _x = number;
}

void Point::setY(double number)
{
    _y = number;
}

void Point::setZ(double number)
{
    _z = number;
}

bool Point::operator==(const Point& other) const noexcept
{
    return isZero(_x - other._x) and isZero(_y - other._y) and isZero(_z - other._z);
}

Point Point::operator-(const Point& other) const noexcept
{
    return { _x - other._x, _y - other._y, _z - other._z };
}

Point Point::operator+(const Point& other) const noexcept
{
    return { _x + other._x, _y + other._y, _z + other._z };
}
 
Point Point::operator*(const double& number) const noexcept
{
    return { _x * number, _y * number, _z * number };
}


VectorCoordinates crossProduct(const VectorCoordinates& first, const VectorCoordinates& second)
{
    VectorCoordinates result;
    result.setX(first.getY() * second.getZ() - first.getZ() * second.getY());
    result.setY(first.getZ() * second.getX() - first.getX() * second.getZ());
    result.setZ(first.getX() * second.getY() - first.getY() * second.getX());
    return result;
}


double dotProduct(const VectorCoordinates& first, const VectorCoordinates& second)
{
    return first.getX() * second.getX() + first.getY() * second.getY() + first.getZ() * second.getZ();
}