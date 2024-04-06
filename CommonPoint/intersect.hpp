#pragma once

#include "point.hpp"
#include "triangle.hpp"
#include "ray.hpp"
#include <variant>

enum TypeResult
{
	nothing, point, segment
};

using Segment = std::pair<Point, Point>;

using Pair = std::pair<std::variant<Point, Segment>, TypeResult>;

Pair intersectRayTriangle(const Ray& ray, const Triangle& triangle);