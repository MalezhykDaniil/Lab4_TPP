
#include <iostream>
#include <cstddef>
#include "Polinom.h"

int main()
{
    const double a[] = { 1, 2, 3 };
    const double b[] = { 4, 5 };

    double result[10]{};
    size_t resultCount = 0;

    int status = poly_add(
        a, 3, b, 2,
        result, 10, &resultCount
    );

    if (status != POLINOM_OK) {
        std::cout << "Addition failed: "
            << status << '\n';
        return 1;
    }

    std::cout << "A + B = ";

    for (size_t i = 0; i < resultCount; ++i)
        std::cout << result[i] << ' ';

    double value = 0.0;

    status = poly_evaluate(a, 3, 2, &value);

    if (status != POLINOM_OK) {
        std::cout << "\nEvaluation failed: "
            << status << '\n';
        return 1;
    }

    std::cout << "\nA(2) = " << value << '\n';

    return 0;
}
