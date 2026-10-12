#include "Interpolation.h"
#include <cmath>
#include <limits>

static double interpolationNaN()
{
    return std::numeric_limits<double>::quiet_NaN();
}

// Інтерполяція поліномом Лагранжа
double lagrange(
    const double* x,
    const double* y,
    int count,
    double target)
{
    if (x == nullptr || y == nullptr ||
        count <= 0 || !std::isfinite(target))
    {
        return interpolationNaN();
    }

    for (int i = 0; i < count; ++i)
    {
        if (!std::isfinite(x[i]) || !std::isfinite(y[i]))
            return interpolationNaN();

        for (int j = 0; j < i; ++j)
        {
            if (x[i] == x[j])
                return interpolationNaN();
        }
    }

    double result = 0.0;

    for (int i = 0; i < count; ++i)
    {
        double term = y[i];

        for (int j = 0; j < count; ++j)
        {
            if (i == j)
                continue;

            double denominator = x[i] - x[j];

            if (denominator == 0.0 || !std::isfinite(denominator))
                return interpolationNaN();

            double factor = (target - x[j]) / denominator;

            if (!std::isfinite(factor))
                return interpolationNaN();

            term *= factor;

            if (!std::isfinite(term))
                return interpolationNaN();
        }

        result += term;

        if (!std::isfinite(result))
            return interpolationNaN();
    }

    return result;
}

// Лінійна інтерполяція між двома точками
double linearInterpolation(
    double x0,
    double y0,
    double x1,
    double y1,
    double target)
{
    if (!std::isfinite(x0) || !std::isfinite(y0) ||
        !std::isfinite(x1) || !std::isfinite(y1) ||
        !std::isfinite(target))
    {
        return interpolationNaN();
    }

    if (x0 == x1)
        return interpolationNaN();

    long double result =
        static_cast<long double>(y0) +
        (static_cast<long double>(y1) - y0) *
        (static_cast<long double>(target) - x0) /
        (static_cast<long double>(x1) - x0);

    if (!std::isfinite(result) ||
        result > std::numeric_limits<double>::max() ||
        result < -std::numeric_limits<double>::max())
    {
        return interpolationNaN();
    }

    return static_cast<double>(result);
}

// Кусково-лінійна інтерполяція
double interpolate(
    const double* x,
    const double* y,
    int count,
    double target)
{
    if (x == nullptr || y == nullptr ||
        count < 2 || !std::isfinite(target))
    {
        return interpolationNaN();
    }

    for (int i = 0; i < count; ++i)
    {
        if (!std::isfinite(x[i]) || !std::isfinite(y[i]))
            return interpolationNaN();

        if (i > 0 && x[i] <= x[i - 1])
            return interpolationNaN();
    }

    if (target < x[0] || target > x[count - 1])
        return interpolationNaN();

    for (int i = 0; i < count; ++i)
    {
        if (target == x[i])
            return y[i];
    }

    for (int i = 0; i < count - 1; ++i)
    {
        if (target > x[i] && target < x[i + 1])
        {
            return linearInterpolation(
                x[i], y[i],
                x[i + 1], y[i + 1],
                target);
        }
    }

    return interpolationNaN();
}

// Обчислення абсолютної похибки
double interpolationError(double actual, double estimated)
{
    if (!std::isfinite(actual) || !std::isfinite(estimated))
        return interpolationNaN();

    double error = std::abs(actual - estimated);

    if (!std::isfinite(error))
        return interpolationNaN();

    return error;
}
