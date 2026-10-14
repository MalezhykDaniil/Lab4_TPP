#include <iostream>
#include <windows.h>
#include <cmath>

using LagrangeFn = double (*)(const double*, const double*, int, double);
using LinearInterpolationFn = double (*)(double, double, double, double, double);
using InterpolateFn = double (*)(const double*, const double*, int, double);
using InterpolationErrorFn = double (*)(double, double);

int main()
{
    HMODULE library = LoadLibraryW(L"Interpolation.dll");

    if (library == nullptr) {
        std::cerr << "Не удалось загрузить Interpolation.dll\n";
        return 1;
    }

    auto lagrange = reinterpret_cast<LagrangeFn>(
        GetProcAddress(library, "lagrange"));

    auto linearInterpolation = reinterpret_cast<LinearInterpolationFn>(
        GetProcAddress(library, "linearInterpolation"));

    auto interpolate = reinterpret_cast<InterpolateFn>(
        GetProcAddress(library, "interpolate"));

    auto interpolationError = reinterpret_cast<InterpolationErrorFn>(
        GetProcAddress(library, "interpolationError"));

    if (!lagrange || !linearInterpolation ||
        !interpolate || !interpolationError) {
        std::cerr << "Не удалось найти все функции в DLL\n";
        FreeLibrary(library);
        return 1;
    }

    const double x[] = { 0.0, 1.0, 2.0 };
    const double y[] = { 1.0, 3.0, 5.0 };

    std::cout << "Lagrange: "
        << lagrange(x, y, 3, 1.5) << '\n';

    std::cout << "Linear: "
        << linearInterpolation(0.0, 1.0, 2.0, 5.0, 1.0) << '\n';

    std::cout << "Piecewise: "
        << interpolate(x, y, 3, 1.5) << '\n';

    std::cout << "Error: "
        << interpolationError(4.5, interpolate(x, y, 3, 1.5))
        << '\n';

    FreeLibrary(library);
    return 0;
}