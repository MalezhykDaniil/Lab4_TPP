
#include "LinearSystem.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <vector>

int gaussianElimination(double* matrix, int n)
{
    if (!matrix || n <= 0)
        return 0;

    const int width = n + 1;
    const double eps = 1e-12;

    for (int col = 0; col < n; ++col) {
        int pivot = col;

        for (int row = col + 1; row < n; ++row) {
            if (std::abs(matrix[row * width + col]) >
                std::abs(matrix[pivot * width + col])) {
                pivot = row;
            }
        }

        if (std::abs(matrix[pivot * width + col]) < eps)
            return 0;

        if (pivot != col) {
            for (int j = col; j < width; ++j) {
                std::swap(
                    matrix[col * width + j],
                    matrix[pivot * width + j]
                );
            }
        }

        for (int row = col + 1; row < n; ++row) {
            double factor =
                matrix[row * width + col] /
                matrix[col * width + col];

            for (int j = col; j < width; ++j) {
                matrix[row * width + j] -=
                    factor * matrix[col * width + j];
            }
        }
    }

    return 1;
}

int solve(const double* A, const double* b, double* x, int n)
{
    if (!A || !b || !x || n <= 0)
        return 0;

    std::vector<double> matrix(n * (n + 1));

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j)
            matrix[i * (n + 1) + j] = A[i * n + j];

        matrix[i * (n + 1) + n] = b[i];
    }

    if (!gaussianElimination(matrix.data(), n))
        return 0;

    std::vector<double> result(n);

    for (int i = n - 1; i >= 0; --i) {
        double value = matrix[i * (n + 1) + n];

        for (int j = i + 1; j < n; ++j) {
            value -= matrix[i * (n + 1) + j] * result[j];
        }

        double diagonal = matrix[i * (n + 1) + i];

        if (std::abs(diagonal) < 1e-12)
            return 0;

        result[i] = value / diagonal;
    }

    for (int i = 0; i < n; ++i)
        x[i] = result[i];

    return 1;
}

double residual(
    const double* A,
    const double* b,
    const double* x,
    int n)
{
    if (!A || !b || !x || n <= 0)
        return -1.0;

    double maxError = 0.0;

    for (int i = 0; i < n; ++i) {
        double value = 0.0;

        for (int j = 0; j < n; ++j)
            value += A[i * n + j] * x[j];

        maxError = std::max(
            maxError,
            std::abs(value - b[i])
        );
    }

    return maxError;
}

int checkSolution(
    const double* A,
    const double* b,
    const double* x,
    int n,
    double tolerance)
{
    if (!A || !b || !x || n <= 0 ||
        !std::isfinite(tolerance) || tolerance < 0.0)
        return 0;

    double error = residual(A, b, x, n);

    return error >= 0.0 &&
        std::isfinite(error) &&
        error <= tolerance;
}
