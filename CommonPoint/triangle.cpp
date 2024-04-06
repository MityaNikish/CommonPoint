#include "triangle.hpp"

Point Triangle::getFirstPoint() const noexcept
{
	return _first_point;
}

Point Triangle::getSecondPoint() const noexcept
{
	return _second_point;
}

Point Triangle::getThirdPoint() const noexcept
{
	return _third_point;
}