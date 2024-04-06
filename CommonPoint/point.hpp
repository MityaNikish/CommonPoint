#pragma once

class Point final
{
	double _x, _y, _z;

public:
	Point() : _x(0), _y(0), _z(0) { }
	Point(double x, double y, double z) : _x(x), _y(y), _z(z) { }
	[[nodiscard]] double getX() const noexcept;
	[[nodiscard]] double getY() const noexcept;
	[[nodiscard]] double getZ() const noexcept;

	void setX(double number);
	void setY(double number);
	void setZ(double number);

	bool operator==(const Point& other) const noexcept;
	Point operator-(const Point& other) const noexcept;
	Point operator+(const Point& other) const noexcept;
	Point operator*(const double& number) const noexcept;
};

using VectorCoordinates = Point;

VectorCoordinates crossProduct(const VectorCoordinates& first, const VectorCoordinates& second);
double dotProduct(const VectorCoordinates& first, const VectorCoordinates& second);