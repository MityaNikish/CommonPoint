#include "algorithm.hpp"
#include "exception.hpp"
#include <numeric>

namespace
{
    constexpr double EPSILON = 0.000001f;

    bool isZero(double number)
    {
        return fabs(number) < EPSILON;
    }

    std::vector<int> redistribution(Matrix& matrix, Array& array)
    {
        const int size = static_cast<int>(matrix.size());

        std::vector<int> L(2);
        std::iota(L.begin(), L.end(), 0);

        for (auto k = 0; k < size; k++)
        {
            if (matrix[L[k]][k] != 0)
                continue;
            for (auto i = k + 1; i < size; i++)
            {
                if (matrix[L[i]][k] != 0)
                {
                    int t = L[k];
                    L[k] = L[i];
                    L[i] = t;
                }
            }
        }
        return L;

    }

    void straightStroke(std::vector<int> index_list, Matrix& matrix, Array& array)
    {
        const int size = static_cast<int>(matrix.size());

        for (auto k = 0; k < size; k++)
        {
            for (auto s = k + 1; s < size; s++)
            {
                const int i = index_list[s];
                if (isZero(matrix[i][k]))
                {
                    matrix[i][k] = 0;
                    continue;
                }
                const double temp = matrix[i][k] / matrix[k][k];
                matrix[i][k] = 0;
                for (auto j = k + 1; j < size; j++)
                {
                    matrix[i][j] -= temp * matrix[k][j];
                }
                array[i] -= temp * array[k];
            }
        }
    }

    Array reverseStroke(std::vector<int> index_list, Matrix& matrix, Array& array)
    {
        const int size = static_cast<int>(matrix.size());
        Array x(size);

    	x[size - 1] = array[index_list[size - 1]] / matrix[index_list[size - 1]][size - 1];

        for (auto s = static_cast<int>(size) - 2; s >= 0; s--)
        {
            const int i = index_list[s];
            double sum = 0;
            for (auto j = s + 1; j < size; j++)
            {
                sum += matrix[i][j] * x[j];
            }
            x[s] = 1 / matrix[i][s] * (array[i] - sum);
        }
        return x;
    }

}

Array gaussianMethod(Matrix& matrix, Array& array)
{
    const size_t size = matrix.size();

    for (auto& row : matrix)
    {
        if (row.size() != size)
        {
            throw IsWrongSize();
        }
    }

    if (array.size() != size)
    {
        throw IsWrongSize();
    }

    std::vector<int> index_list = redistribution(matrix, array);
    straightStroke(index_list, matrix, array);
    return reverseStroke(index_list, matrix, array);
}