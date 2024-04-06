#pragma once
#include <vector>

using Matrix = std::vector<std::vector<double>>;
using Array = std::vector<double>;

Array gaussianMethod(Matrix& matrix, Array& array);