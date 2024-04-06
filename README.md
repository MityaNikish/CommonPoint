# **Задача**
Реализовать функцию, которая находит пересечение луча и треугольника в трехмерном пространстве.
____
# **Дополнительная информация по реализации**
 - Стандарт ISO C++ 20

Сигнатура основной функции была выбрана с учетом того что пересечение луча и треугольника в трехмерном пространстве может являтся как точкой, так и отрезком.
```C++
//point.hpp
class Point;  // Точка

//triangle.hpp
class Triangle;  // Треугольник

//ray.hpp
class Ray;  // Луч

//intersect.hpp
using Segment = std::pair<Point, Point>;  // Отрезок
enum TypeResult { nothing, point, segment };  // Тип результата пересечения
using Pair = std::pair<std::variant<Point, Segment>, TypeResult>;  // Пара результата и типа результата

Pair intersectRayTriangle(const Ray& ray, const Triangle& triangle);
```
