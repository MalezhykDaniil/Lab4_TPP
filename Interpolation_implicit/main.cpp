
#include <iostream>
#include <cmath>
#include <limits>
#include "Interpolation.h"

int main()
{
    const double x[] = { 0.0, 1.0, 2.0 };
    const double y[] = { 1.0, 3.0, 5.0 };

    // 1. Поліноміальна інтерполяція Лагранжа
    double lagrangeResult = lagrange(x, y, 3, 1.5);
    std::cout << "Lagrange: " << lagrangeResult << '\n';

    // 2. Лінійна інтерполяція
    double linearResult =
        linearInterpolation(0.0, 1.0, 2.0, 5.0, 1.0);

    std::cout << "Linear: " << linearResult << '\n';

    // 3. Кусково-лінійна інтерполяція
    double piecewiseResult = interpolate(x, y, 3, 1.5);
    std::cout << "Piecewise: " << piecewiseResult << '\n';

    // 4. Абсолютна похибка
    double error = interpolationError(4.5, piecewiseResult);
    std::cout << "Error: " << error << '\n';

    // 5. Перевірка граничного випадку: nullptr
    double invalidResult = lagrange(nullptr, y, 3, 1.5);
    std::cout << "Null pointer test: "
        << (std::isnan(invalidResult) ? "PASS" : "FAIL")
        << '\n';

    // 6. Перевірка NaN
    double nanValue = std::numeric_limits<double>::quiet_NaN();
    double nanResult =
        linearInterpolation(0.0, 1.0, 2.0, 5.0, nanValue);

    std::cout << "NaN test: "
        << (std::isnan(nanResult) ? "PASS" : "FAIL")
        << '\n';

    return 0;
}
