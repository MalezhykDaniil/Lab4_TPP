#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <cstddef>

// Коди результату SDK
enum PolinomStatus
{
    POLINOM_OK = 0,
    POLINOM_INVALID_ARGUMENT = 1,
    POLINOM_BUFFER_TOO_SMALL = 2,
    POLINOM_RESOURCE_ERROR = 3,
    POLINOM_NUMERIC_ERROR = 4,
    POLINOM_INTERNAL_ERROR = 5
};

// Типи покажчиків на функції DLL
using PolyAdd = int (*)(
    const double*, size_t,
    const double*, size_t,
    double*, size_t, size_t*
    );

using PolyMultiply = int (*)(
    const double*, size_t,
    const double*, size_t,
    double*, size_t, size_t*
    );

using PolyEvaluate = int (*)(
    const double*, size_t, double, double*
    );

using PolyDerivative = int (*)(
    const double*, size_t,
    double*, size_t, size_t*
    );

using PolyIntegral = int (*)(
    const double*, size_t, double,
    double*, size_t, size_t*
    );

void printStatus(const char* name, int status)
{
    std::cout << name << ": ";

    switch (status)
    {
    case POLINOM_OK:
        std::cout << "POLINOM_OK";
        break;
    case POLINOM_INVALID_ARGUMENT:
        std::cout << "POLINOM_INVALID_ARGUMENT";
        break;
    case POLINOM_BUFFER_TOO_SMALL:
        std::cout << "POLINOM_BUFFER_TOO_SMALL";
        break;
    case POLINOM_RESOURCE_ERROR:
        std::cout << "POLINOM_RESOURCE_ERROR";
        break;
    case POLINOM_NUMERIC_ERROR:
        std::cout << "POLINOM_NUMERIC_ERROR";
        break;
    case POLINOM_INTERNAL_ERROR:
        std::cout << "POLINOM_INTERNAL_ERROR";
        break;
    default:
        std::cout << "Unknown status (" << status << ")";
        break;
    }

    std::cout << '\n';
}

void printArray(const double* values, size_t count)
{
    std::cout << "{ ";

    for (size_t i = 0; i < count; ++i)
    {
        std::cout << values[i];

        if (i + 1 < count)
            std::cout << ", ";
    }

    std::cout << " }\n";
}

int main()
{
    std::cout << std::fixed << std::setprecision(2);

    // Завантаження DLL під час виконання
    HMODULE dll = LoadLibraryW(L"Polinom.dll");

    if (!dll)
    {
        std::cerr << "Cannot load Polinom.dll. Error: "
            << GetLastError() << '\n';
        return 1;
    }

    // Отримання адрес функцій із DLL
    auto poly_add = reinterpret_cast<PolyAdd>(
        GetProcAddress(dll, "poly_add"));

    auto poly_multiply = reinterpret_cast<PolyMultiply>(
        GetProcAddress(dll, "poly_multiply"));

    auto poly_evaluate = reinterpret_cast<PolyEvaluate>(
        GetProcAddress(dll, "poly_evaluate"));

    auto poly_derivative = reinterpret_cast<PolyDerivative>(
        GetProcAddress(dll, "poly_derivative"));

    auto poly_integral = reinterpret_cast<PolyIntegral>(
        GetProcAddress(dll, "poly_integral"));

    // Перевірка наявності всіх функцій
    if (!poly_add || !poly_multiply || !poly_evaluate ||
        !poly_derivative || !poly_integral)
    {
        std::cerr << "Cannot find all functions in Polinom.dll. "
            << "Error: " << GetLastError() << '\n';

        FreeLibrary(dll);
        return 1;
    }

    std::cout << "Polinom.dll loaded successfully!\n\n";

    // P(x) = 1 + 2x + 3x^2
    const double a[] = { 1.0, 2.0, 3.0 };

    // Q(x) = 4 + 5x
    const double b[] = { 4.0, 5.0 };

    double out[10] = {};
    size_t outCount = 0;
    int status = 0;

    // Додавання поліномів
    status = poly_add(a, 3, b, 2, out, 10, &outCount);
    printStatus("poly_add", status);

    if (status == POLINOM_OK)
        printArray(out, outCount);

    // Множення поліномів
    status = poly_multiply(a, 3, b, 2, out, 10, &outCount);
    printStatus("poly_multiply", status);

    if (status == POLINOM_OK)
        printArray(out, outCount);

    // Обчислення значення P(2)
    double value = 0.0;

    status = poly_evaluate(a, 3, 2.0, &value);
    printStatus("poly_evaluate", status);

    if (status == POLINOM_OK)
        std::cout << "P(2) = " << value << '\n';

    // Похідна
    status = poly_derivative(a, 3, out, 10, &outCount);
    printStatus("poly_derivative", status);

    if (status == POLINOM_OK)
        printArray(out, outCount);

    // Первісна з константою C = 7
    status = poly_integral(a, 3, 7.0, out, 10, &outCount);
    printStatus("poly_integral", status);

    if (status == POLINOM_OK)
        printArray(out, outCount);

    // Перевірка помилки: замалий вихідний буфер
    double smallBuffer[2] = { -99.0, -99.0 };
    size_t requiredCount = 0;

    status = poly_multiply(
        a, 3, b, 2,
        smallBuffer, 2, &requiredCount
    );

    printStatus("Small output buffer", status);
    std::cout << "Required capacity: "
        << requiredCount << '\n';

    // Вивільнення DLL
    FreeLibrary(dll);

    std::cout << "\nPolinom.dll unloaded successfully!\n";
    std::cout << "Tests finished.\n";

    return 0;
}
