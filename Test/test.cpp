#include "pch.h"
#include "intersect.hpp"


//int main() {
//	const Ray ray({ 0, 1, 2 }, { 1, 0, -2 });
//	const Triangle triangle({ 1, 1, 2 }, { 1, -1, -3 }, { 1, 0, -2 });
//
//    const Pair result = intersectRayTriangle(ray, triangle);
//
//    switch (result.second)
//    {
//	    case nothing:
//	    {
//	        std::cout << nothing << std::endl;
//	        break;
//	    }
//
//	    case point:
//	    {
//	        Point point = std::get<Point>(result.first);
//	        std::cout << point.getX() << "  " << point.getY() << "  " << point.getZ() << "  " << std::endl;
//	        break;
//	    }
//
//	    case segment:
//	    {
//	        Segment segment = std::get<Segment>(result.first);
//	        std::cout << segment.first.getX() << "  " << segment.first.getY() << "  " << segment.first.getZ() << "  " << std::endl;
//	        std::cout << segment.second.getX() << "  " << segment.second.getY() << "  " << segment.second.getZ() << "  " << std::endl;
//	        break;
//	    }
//	}
//    return 0;
//}


TEST(ResultNothing, Complete1) {
    const Ray ray({ 0, 0, 1 }, { 1, 0, 0 });
    const Triangle triangle({ 0, 1, 0 }, { 1, 0, 0 }, { 0, 0, 0 });

    const Pair result = intersectRayTriangle(ray, triangle);

    EXPECT_EQ(result.second, TypeResult::nothing);
}

TEST(ResultNothing, Complete2) {
    const Ray ray({ -1, -1, 1 }, { 0, 0, -1 });
    const Triangle triangle({ 0, 1, 0 }, { 1, 0, 0 }, { 0, 0, 0 });

    const Pair result = intersectRayTriangle(ray, triangle);

    EXPECT_EQ(result.second, TypeResult::nothing);
}

TEST(ResultPoint, Complete1) {
    const Triangle triangle = { {0, 0, 0}, {1, 0, 0}, {0, 1, 0} };
    const Ray ray = { {0.5, 0.5, -1}, {0, 0, 1} };

    const Pair result = intersectRayTriangle(ray, triangle);

	EXPECT_EQ(result.second, TypeResult::point);

    Point point = std::get<Point>(result.first);
	EXPECT_TRUE(point == Point(1.0f / 2, 1.0f / 2, 0));
}

TEST(ResultPoint, Complete2) {
    const Ray ray({0, 0, 0}, {5, 5, 5});
    const Triangle triangle({2, 0, 0}, {0, 2, 0}, {0, 0, 2});

    const Pair result = intersectRayTriangle(ray, triangle);

    EXPECT_EQ(result.second, TypeResult::point);

    Point point = std::get<Point>(result.first);
    EXPECT_TRUE(point == Point(2.0f / 3, 2.0f / 3, 2.0f / 3));
}

TEST(ResultPoint, Complete3) {
    const Ray ray({ 1, 1, 5 }, { 0, 0, -1 });
    const Triangle triangle({ 2, 0, 0 }, { 0, 2, 0 }, { 0, 0, 0 });

    const Pair result = intersectRayTriangle(ray, triangle);

    EXPECT_EQ(result.second, TypeResult::point);

    Point point = std::get<Point>(result.first);
    EXPECT_TRUE(point == Point(1, 1, 0));
}

TEST(ResultPoint, Complete4) {
    const Ray ray({ 1, 1, -100 }, { 0, 0, 1 });
    const Triangle triangle({ 0, 2, 0 }, { 3, 0, 0 }, { 0, 0, 5 });

    const Pair result = intersectRayTriangle(ray, triangle);

    EXPECT_EQ(result.second, TypeResult::point);

    Point point = std::get<Point>(result.first);
    EXPECT_TRUE(point == Point(1, 1, 5.0f / 6));
}


TEST(ResultsSegment, Complete1) {
    const Ray ray({ 1, 0, 0 }, { -1, 1, 0 });
    const Triangle triangle({ 0, 0, 0 }, { 0, 2, 0 }, { 2, 0, 0 });

    const Pair result = intersectRayTriangle(ray, triangle);

    EXPECT_EQ(result.second, TypeResult::segment);

    Segment segment = std::get<Segment>(result.first);
    EXPECT_TRUE(segment.first == Point(1, 0, 0) or segment.first == Point(0, 1, 0));
    EXPECT_TRUE(segment.second == Point(0, 1, 0) or segment.second == Point(1, 0, 0));
}


TEST(ResultsSegment, Complete2) {
    const Ray ray({ 0, 0, 0 }, { 1, 1, 0 });
    const Triangle triangle({ 2, 0, 0 }, { 0, 2, 0 }, { 0, 0, 0 });

    const Pair result = intersectRayTriangle(ray, triangle);

    EXPECT_EQ(result.second, TypeResult::segment);

    Segment segment = std::get<Segment>(result.first);
    EXPECT_TRUE(segment.first == Point(0, 0, 0) or segment.first == Point(1, 1, 0));
    EXPECT_TRUE(segment.second == Point(0, 0, 0) or segment.second == Point(1, 1, 0));
}


TEST(ResultsSegment, Complete3) {
    const Ray ray({ 0, 0, 0 }, { 1, 0, 0 });
    const Triangle triangle({ 2, 0, 0 }, { 0, 2, 0 }, { 0, 0, 0 });

    const Pair result = intersectRayTriangle(ray, triangle);

    EXPECT_EQ(result.second, TypeResult::segment);

    Segment segment = std::get<Segment>(result.first);
    EXPECT_TRUE(segment.first == Point(0, 0, 0) or segment.first == Point(2, 0, 0));
    EXPECT_TRUE(segment.second == Point(0, 0, 0) or segment.second == Point(2, 0, 0));
}

TEST(ResultsSegment, Complete4) {
    const Ray ray({ 0.25, 0.25, 0 }, { 1, 1, 0 });
    const Triangle triangle({ 2, 0, 0 }, { 0, 2, 0 }, { 0, 0, 0 });

    const Pair result = intersectRayTriangle(ray, triangle);

    EXPECT_EQ(result.second, TypeResult::segment);

    Segment segment = std::get<Segment>(result.first);
    EXPECT_TRUE(segment.first == Point(0.25, 0.25, 0) or segment.first == Point(1, 1, 0));
    EXPECT_TRUE(segment.second == Point(0.25, 0.25, 0) or segment.second == Point(1, 1, 0));
}