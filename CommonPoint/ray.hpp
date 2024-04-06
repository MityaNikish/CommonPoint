#pragma once
#include "point.hpp"

class Ray final
{
	Point _start_point;
	VectorCoordinates _guide_vector;

public:
	Ray(const Point& start_point, const VectorCoordinates& guide_vector) : _start_point(start_point), _guide_vector(guide_vector) { }
	[[nodiscard]] Point getStartPoint() const noexcept;
	[[nodiscard]] VectorCoordinates getGuideVector() const noexcept;
};