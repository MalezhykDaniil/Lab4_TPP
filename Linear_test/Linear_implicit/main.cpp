#include <iostream>
#include <iomanip>
#include "LinearSystem.h"

int main()
{
    std::cout << std::fixed << std::setprecision(6);

    const int n = 3;

    const double A[n * n] = {
         2,  1, -1,
        -3, -1,  2,
        -2,  1,  2
    };

    const double b[n] = { 8, -11, -3 };
    double x[n] = {};

    std::cout << "=== solve ===\n";

    int status = solve(A, b, x, n);

    std::cout << "Status: " << status << '\n';

    for (int i = 0; i < n; ++i)
    {
        std::cout << "x[" << i << "] = " << x[i] << '\n';
    }

    std::cout << "\n=== residual ===\n";

    double error = residual(A, b, x, n);

    std::cout << "Residual: " << error << '\n';

    std::cout << "\n=== checkSolution ===\n";

    int valid = checkSolution(A, b, x, n, 1e-9);

    std::cout << "Check result: " << valid << '\n';

    if (valid == 1)
        std::cout << "Solution verification passed.\n";
    else
        std::cout << "Solution verification failed.\n";

    std::cout << "\n=== gaussianElimination ===\n";

    double matrix[n * (n + 1)] = {
         2,  1, -1,   8,
        -3, -1,  2, -11,
        -2,  1,  2,  -3
    };

    int gaussianStatus = gaussianElimination(matrix, n);

    std::cout << "Status: " << gaussianStatus << '\n';
    std::cout << "Matrix after elimination:\n";

    for (int i = 0; i < n; ++i)
    {
        for (int j = 0; j < n + 1; ++j)
        {
            std::cout << std::setw(12)
                << matrix[i * (n + 1) + j];
        }

        std::cout << '\n';
    }

    return 0;
}
