#include "ray.hpp"


Point Ray::getStartPoint() const noexcept
{
	return _start_point;
}

VectorCoordinates Ray::getGuideVector() const noexcept
{
	return _guide_vector;
}
