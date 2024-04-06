#include "intersect.hpp"
#include "algorithm.hpp"

namespace
{
    constexpr double EPSILON = 0.000001f;

    bool isZero(double number)
    {
        return fabs(number) < EPSILON;
    }

    std::pair<Matrix, Array> createExtendedMatrix(const VectorCoordinates& v1, const VectorCoordinates& v2, const Point& p1, const Point& p2)
    {
        Matrix matrix = { { v1.getX(), -v2.getX() }, { v1.getY() + v1.getZ(), -(v2.getY() + v2.getZ()) } };
        Array array = { p2.getX() - p1.getX(), p2.getY() - p1.getY() + p2.getZ() - p1.getZ() };
        return { matrix, array };
    }

    bool checkOptions(double a, double b)
    {
        return a >= 0.0f and a <= 1.0f and b >= 0.0f and (!isZero(a) or !isZero(b));
    }
}



Pair intersectRayTriangle(const Ray& ray, const Triangle& triangle)
{
	Pair result_intersect = std::make_pair(Point(), nothing);

    //	E = p*w1 + q*w2 + w3 
    const VectorCoordinates w1 = triangle.getSecondPoint() - triangle.getFirstPoint();
    const VectorCoordinates w2 = triangle.getThirdPoint() - triangle.getFirstPoint();
	const Point p1 = triangle.getFirstPoint();

	//	F = d*u1 + u2 
	const VectorCoordinates u1 = ray.getGuideVector();
	const Point p2 = ray.getStartPoint();

    const VectorCoordinates h = crossProduct(u1, w1);
    double a = dotProduct(w2, h);

    // ѕровер€ем, лежит ли пр€ма€ в плоскости треугольника
    if (isZero(a))
    {
        unsigned count_intersections = 0;
        std::vector<Point> points_segment;

        enum QuantityIntersections
        {
	        zero, one, two, three
        };

        //находим пересечени€ луча и грани треугольника
        std::pair<Matrix, Array> extended_matrix1 = createExtendedMatrix(w1, u1, p1, p2);
        Array options1 = gaussianMethod(extended_matrix1.first, extended_matrix1.second);
        if (checkOptions(options1[0], options1[1]))
        {
            count_intersections++;
            points_segment.push_back(p2 + u1 * options1[1]);
        }

        //находим пересечени€ луча и грани треугольника
        std::pair<Matrix, Array> extended_matrix2 = createExtendedMatrix(w2, u1, p1, p2);
        Array options2 = gaussianMethod(extended_matrix2.first, extended_matrix2.second);
        if (checkOptions(options2[0], options2[1]))
        {
            count_intersections++;
            points_segment.push_back(p2 + u1 * options2[1]);
        }

        //находим пересечени€ луча и грани треугольника
        std::pair<Matrix, Array> extended_matrix3 = createExtendedMatrix(triangle.getThirdPoint() - triangle.getSecondPoint(), u1, triangle.getSecondPoint(), p2);
        Array options3 = gaussianMethod(extended_matrix3.first, extended_matrix3.second);
    	if (checkOptions(options3[0], options3[1]))
        {
            count_intersections++;
            points_segment.push_back(p2 + u1 * options3[1]);
        }

        //вычисл€ем координаты отрезка, если луч проходит через треугольник
        switch (count_intersections)
        {
	        case zero:
	            return result_intersect;

	        case one:
	        {
				result_intersect.first.emplace<Segment>(std::make_pair(points_segment[0], p2));
				result_intersect.second = segment;
                return result_intersect;
	        }

	        case two:
	        {
                result_intersect.first.emplace<Segment>(std::make_pair(points_segment[0], points_segment[1]));
                result_intersect.second = segment;
                return result_intersect;
	        }

    		case three:
	        {
                if (points_segment[0] == points_segment[1])
                {
                    result_intersect.first.emplace<Segment>(std::make_pair(points_segment[0], points_segment[2]));
                }
                else
                {
                    result_intersect.first.emplace<Segment>(std::make_pair(points_segment[0], points_segment[1]));
                }
                result_intersect.second = segment;
                return result_intersect;
	        }

            default:
                return result_intersect;
        }
    }

    double f = 1.0f / a;
    VectorCoordinates s = p2 - p1;
    double u = f * dotProduct(s, h);

    // ѕровер€ем, что точка пересечени€ находитс€ внутри треугольника
    if (u < 0.0f || u > 1.0f)
        return result_intersect;

    VectorCoordinates q = crossProduct(s, w2);
    double v = f * dotProduct(u1, q);

    // ѕровер€ем, что точка пересечени€ находитс€ внутри треугольника
    if (v < 0.0f || u + v > 1.0f)
        return result_intersect;

    double t = f * dotProduct(w1, q);

    // ѕровер€ем, что точка пересечени€ находитс€ на луче
    if (t > EPSILON) 
    {
        result_intersect.first = ray.getStartPoint() + ray.getGuideVector() * t;
        result_intersect.second = point;
        return result_intersect;
    }

return result_intersect;
}
