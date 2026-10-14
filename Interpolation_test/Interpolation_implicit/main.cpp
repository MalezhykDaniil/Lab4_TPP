
#include <iostream>
#include <cmath>
#include <limits>
#include <iomanip>
#include <algorithm>

#include "Interpolation.h"

int main()
{
    int passed = 0;
    int failed = 0;

    auto test = [&](const char* name,
        double actual,
        double expected,
        bool expectNaN = false)
        {
            bool success = false;

            if (expectNaN) {
                success = std::isnan(actual);
            }
            else if (std::isfinite(actual) && std::isfinite(expected)) {
                const double tolerance =
                    1e-9 * std::max(1.0, std::abs(expected));

                success = std::abs(actual - expected) <= tolerance;
            }

            std::cout << (success ? "[PASS] " : "[FAIL] ")
                << name
                << " | actual = " << actual
                << " | expected = ";

            if (expectNaN)
                std::cout << "NaN";
            else
                std::cout << expected;

            std::cout << '\n';

            if (success)
                ++passed;
            else
                ++failed;
        };

    const double nan = std::numeric_limits<double>::quiet_NaN();
    const double inf = std::numeric_limits<double>::infinity();
    const double maxDouble = std::numeric_limits<double>::max();

    const double x[] = { 0.0, 1.0, 2.0 };
    const double y[] = { 1.0, 3.0, 5.0 };

    std::cout << std::fixed << std::setprecision(6);


    std::cout << "\n========== LAGRANGE ==========\n";

    test("Lagrange: перший вузол",
        lagrange(x, y, 3, 0.0), 1.0);

    test("Lagrange: внутрішній вузол",
        lagrange(x, y, 3, 1.0), 3.0);

    test("Lagrange: останній вузол",
        lagrange(x, y, 3, 2.0), 5.0);

    test("Lagrange: інтерполяція",
        lagrange(x, y, 3, 1.5), 4.0);

    test("Lagrange: екстраполяція зліва",
        lagrange(x, y, 3, -1.0), -1.0);

    test("Lagrange: екстраполяція справа",
        lagrange(x, y, 3, 3.0), 7.0);

    test("Lagrange: x == nullptr",
        lagrange(nullptr, y, 3, 1.0), 0.0, true);

    test("Lagrange: y == nullptr",
        lagrange(x, nullptr, 3, 1.0), 0.0, true);

    test("Lagrange: count == 0",
        lagrange(x, y, 0, 1.0), 0.0, true);

    test("Lagrange: count < 0",
        lagrange(x, y, -1, 1.0), 0.0, true);

    const double duplicateX[] = { 0.0, 1.0, 1.0 };

    test("Lagrange: повторювані вузли",
        lagrange(duplicateX, y, 3, 1.5), 0.0, true);

    test("Lagrange: NaN у target",
        lagrange(x, y, 3, nan), 0.0, true);

    test("Lagrange: нескінченність у target",
        lagrange(x, y, 3, inf), 0.0, true);

    const double nanY[] = { 1.0, nan, 5.0 };

    test("Lagrange: NaN у масиві y",
        lagrange(x, nanY, 3, 1.5), 0.0, true);

    const double infX[] = { 0.0, inf, 2.0 };

    test("Lagrange: нескінченність у масиві x",
        lagrange(infX, y, 3, 1.5), 0.0, true);



    std::cout << "\n========== LINEAR INTERPOLATION ==========\n";

    test("Linear: перша точка",
        linearInterpolation(0, 1, 2, 5, 0), 1.0);

    test("Linear: друга точка",
        linearInterpolation(0, 1, 2, 5, 2), 5.0);

    test("Linear: середина відрізка",
        linearInterpolation(0, 1, 2, 5, 1), 3.0);

    test("Linear: екстраполяція зліва",
        linearInterpolation(0, 1, 2, 5, -1), -1.0);

    test("Linear: екстраполяція справа",
        linearInterpolation(0, 1, 2, 5, 3), 7.0);

    test("Linear: спадна пряма",
        linearInterpolation(0, 5, 2, 1, 1), 3.0);

    test("Linear: однакові x0 та x1",
        linearInterpolation(1, 2, 1, 5, 3), 0.0, true);

    test("Linear: NaN у x0",
        linearInterpolation(nan, 1, 2, 5, 1), 0.0, true);

    test("Linear: нескінченність у y0",
        linearInterpolation(0, inf, 2, 5, 1), 0.0, true);

    test("Linear: NaN у target",
        linearInterpolation(0, 1, 2, 5, nan), 0.0, true);

    test("Linear: нескінченність у target",
        linearInterpolation(0, 1, 2, 5, inf), 0.0, true);



    std::cout << "\n========== PIECEWISE INTERPOLATION ==========\n";

    test("Piecewise: перший вузол",
        interpolate(x, y, 3, 0.0), 1.0);

    test("Piecewise: внутрішній вузол",
        interpolate(x, y, 3, 1.0), 3.0);

    test("Piecewise: останній вузол",
        interpolate(x, y, 3, 2.0), 5.0);

    test("Piecewise: між вузлами",
        interpolate(x, y, 3, 1.5), 4.0);

    test("Piecewise: x == nullptr",
        interpolate(nullptr, y, 3, 1.0), 0.0, true);

    test("Piecewise: y == nullptr",
        interpolate(x, nullptr, 3, 1.0), 0.0, true);

    test("Piecewise: count == 0",
        interpolate(x, y, 0, 1.0), 0.0, true);

    test("Piecewise: count == 1",
        interpolate(x, y, 1, 1.0), 0.0, true);

    test("Piecewise: count < 0",
        interpolate(x, y, -1, 1.0), 0.0, true);

    test("Piecewise: екстраполяція зліва заборонена",
        interpolate(x, y, 3, -1.0), 0.0, true);

    test("Piecewise: екстраполяція справа заборонена",
        interpolate(x, y, 3, 3.0), 0.0, true);

    test("Piecewise: NaN у target",
        interpolate(x, y, 3, nan), 0.0, true);

    test("Piecewise: нескінченність у target",
        interpolate(x, y, 3, inf), 0.0, true);

    const double unorderedX[] = { 0.0, 2.0, 1.0 };

    test("Piecewise: вузли не впорядковані",
        interpolate(unorderedX, y, 3, 1.5), 0.0, true);

    const double repeatedX[] = { 0.0, 1.0, 1.0 };

    test("Piecewise: повторювані вузли",
        interpolate(repeatedX, y, 3, 1.0), 0.0, true);

    const double nanValues[] = { 1.0, nan, 5.0 };

    test("Piecewise: NaN у масиві y",
        interpolate(x, nanValues, 3, 1.5), 0.0, true);

    const double infiniteX[] = { 0.0, inf, 2.0 };

    test("Piecewise: нескінченність у масиві x",
        interpolate(infiniteX, y, 3, 1.5), 0.0, true);



    std::cout << "\n========== INTERPOLATION ERROR ==========\n";

    test("Error: нульова похибка",
        interpolationError(5.0, 5.0), 0.0);

    test("Error: додатна похибка",
        interpolationError(4.5, 4.0), 0.5);

    test("Error: від'ємна різниця",
        interpolationError(2.0, 5.0), 3.0);

    test("Error: від'ємні значення",
        interpolationError(-5.0, -2.0), 3.0);

    test("Error: NaN у actual",
        interpolationError(nan, 1.0), 0.0, true);

    test("Error: NaN у estimated",
        interpolationError(1.0, nan), 0.0, true);

    test("Error: нескінченність у actual",
        interpolationError(inf, 1.0), 0.0, true);

    test("Error: нескінченність у estimated",
        interpolationError(1.0, inf), 0.0, true);

    test("Error: переповнення різниці",
        interpolationError(maxDouble, -maxDouble), 0.0, true);

    std::cout << "\n========== TEST SUMMARY ==========\n";
    std::cout << "Усього тестів: " << passed + failed << '\n';
    std::cout << "Успішно:       " << passed << '\n';
    std::cout << "Помилок:       " << failed << '\n';

    return failed == 0 ? 0 : 1;
}
