#include <iostream>
#include <iomanip>
#include "Interpolation.h"

int main()
{
    const double x[] = { 0.0, 1.0, 2.0 };
    const double y[] = { 0.0, 1.0, 4.0 };
    const int count = 3;
    const double target = 1.5;

    std::cout << std::fixed << std::setprecision(4);

    double lagrangeResult = lagrange(x, y, count, target);
    std::cout << "Lagrange interpolation: " << lagrangeResult << '\n';

    double linearResult = linearInterpolation(1.0, 1.0, 2.0, 4.0, target);
    std::cout << "Linear interpolation: " << linearResult << '\n';

    double interpolateResult = interpolate(x, y, count, target);
    std::cout << "Piecewise interpolation: " << interpolateResult << '\n';

    double error = interpolationError(2.25, lagrangeResult);
    std::cout << "Interpolation error: " << error << '\n';

    return 0;
}