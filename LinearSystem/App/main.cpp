#include <iostream>
#include "LinearSystem.h"

int main()
{
    // Приклад системи лінійних рівнянь:
    // 2x + y - z = 8
    // -3x - y + 2z = -11
    // -2x + y + 2z = -3

    const int n = 3;

    const double A[n * n] = {
         2,  1, -1,
        -3, -1,  2,
        -2,  1,  2
    };

    const double b[n] = { 8, -11, -3 };
    double x[n] = { 0, 0, 0 };

    std::cout << "Solving a system of linear equations...\n";

    int status = solve(A, b, x, n);
    (void)status;

    const double tolerance = 1e-9;
    int valid = checkSolution(A, b, x, n, tolerance);

    if (valid == 1)
    {
        std::cout << "Solution found:\n";
        for (int i = 0; i < n; ++i)
        {
            std::cout << "x[" << i << "] = " << x[i] << '\n';
        }

        std::cout << "Residual: "
            << residual(A, b, x, n) << '\n';
    }
    else
    {
        std::cout << "Could not verify the solution.\n";
        std::cout << "Check the solve() implementation and input data.\n";
    }

    return 0;
}