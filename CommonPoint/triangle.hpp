#pragma once
#include "point.hpp"

class Triangle final
{
	Point _first_point, _second_point, _third_point;

public:
	Triangle(const Point& first_point, const Point& second_point, const Point& third_point)
		: _first_point(first_point), _second_point(second_point), _third_point(third_point) { }
	[[nodiscard]] Point getFirstPoint() const noexcept;
	[[nodiscard]] Point getSecondPoint() const noexcept;
	[[nodiscard]] Point getThirdPoint() const noexcept;
};