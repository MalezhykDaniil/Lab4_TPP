#include <iostream>
#include <iomanip>
#include <cmath>
#include "Polinom.h"

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

    // P(x) = 1 + 2x + 3x^2
    const double a[] = { 1.0, 2.0, 3.0 };

    // Q(x) = 4 + 5x
    const double b[] = { 4.0, 5.0 };

    double out[10] = {};
    size_t outCount = 0;

    std::cout << "=== Polynomial SDK tests ===\n\n";

    // 1. Додавання
    int status = poly_add(
        a, 3, b, 2,
        out, 10, &outCount
    );

    printStatus("poly_add", status);

    if (status == POLINOM_OK)
    {
        std::cout << "Result: ";
        printArray(out, outCount);
    }

    // 2. Множення
    status = poly_multiply(
        a, 3, b, 2,
        out, 10, &outCount
    );

    printStatus("poly_multiply", status);

    if (status == POLINOM_OK)
    {
        std::cout << "Result: ";
        printArray(out, outCount);
    }

    // 3. Обчислення P(2) = 1 + 2*2 + 3*2^2 = 17
    double value = 0.0;

    status = poly_evaluate(a, 3, 2.0, &value);

    printStatus("poly_evaluate", status);

    if (status == POLINOM_OK)
        std::cout << "P(2) = " << value << '\n';

    // 4. Похідна: P'(x) = 2 + 6x
    status = poly_derivative(
        a, 3, out, 10, &outCount
    );

    printStatus("poly_derivative", status);

    if (status == POLINOM_OK)
    {
        std::cout << "Derivative: ";
        printArray(out, outCount);
    }

    // 5. Первісна з C = 7:
    // F(x) = 7 + x + x^2 + x^3
    status = poly_integral(
        a, 3, 7.0, out, 10, &outCount
    );

    printStatus("poly_integral", status);

    if (status == POLINOM_OK)
    {
        std::cout << "Integral: ";
        printArray(out, outCount);
    }

    // 6. Граничний випадок: замалий буфер для множення.
    double smallBuffer[2] = { -99.0, -99.0 };
    size_t requiredCount = 0;

    status = poly_multiply(
        a, 3, b, 2,
        smallBuffer, 2, &requiredCount
    );

    printStatus("Small output buffer", status);
    std::cout << "Required capacity: "
        << requiredCount << '\n';

    std::cout << "Buffer after call: ";
    printArray(smallBuffer, 2);

    // 7. Граничний випадок: нульова кількість коефіцієнтів.
    status = poly_evaluate(a, 0, 2.0, &value);
    printStatus("Zero coefficient count", status);

    // 8. Граничний випадок: нульовий вказівник.
    status = poly_evaluate(nullptr, 3, 2.0, &value);
    printStatus("Null input pointer", status);

    // 9. Граничний випадок: нульовий out_count.
    status = poly_add(
        a, 3, b, 2,
        out, 10, nullptr
    );
    printStatus("Null out_count", status);

    std::cout << "\n=== Tests finished ===\n";

    return 0;
}
