#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <cmath>

using GaussianEliminationFunc = int (*)(
    double* matrix,
    int n
    );

using SolveFunc = int (*)(
    const double* A,
    const double* b,
    double* x,
    int n
    );

using ResidualFunc = double (*)(
    const double* A,
    const double* b,
    const double* x,
    int n
    );

using CheckSolutionFunc = int (*)(
    const double* A,
    const double* b,
    const double* x,
    int n,
    double tolerance
    );

int main()
{
    std::cout << std::fixed << std::setprecision(6);

    HMODULE dll = LoadLibraryW(L"LinearSystemLib.dll");

    if (!dll)
    {
        std::cerr << "Cannot load LinearSystemLib.dll. Error: "
            << GetLastError() << '\n';
        return 1;
    }

    std::cout << "LinearSystemLib.dll loaded successfully!\n\n";

    auto gaussianElimination =
        reinterpret_cast<GaussianEliminationFunc>(
            GetProcAddress(dll, "gaussianElimination"));

    auto solve =
        reinterpret_cast<SolveFunc>(
            GetProcAddress(dll, "solve"));

    auto residual =
        reinterpret_cast<ResidualFunc>(
            GetProcAddress(dll, "residual"));

    auto checkSolution =
        reinterpret_cast<CheckSolutionFunc>(
            GetProcAddress(dll, "checkSolution"));

    if (!gaussianElimination ||
        !solve ||
        !residual ||
        !checkSolution)
    {
        std::cerr << "Cannot find all required functions. Error: "
            << GetLastError() << '\n';

        FreeLibrary(dll);
        return 1;
    }

    std::cout << "All four functions found!\n\n";

    const int n = 3;

    const double A[n * n] = {
         2,  1, -1,
        -3, -1,  2,
        -2,  1,  2
    };

    const double b[n] = { 8, -11, -3 };

    double x[n] = {};

    std::cout << "=== solve ===\n";

    int solveStatus = solve(A, b, x, n);

    std::cout << "Status: " << solveStatus << '\n';

    std::cout << "Solution:\n";

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
    {
        std::cout << "Solution verification passed.\n";
    }
    else
    {
        std::cout << "Solution verification failed.\n";
    }

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

    FreeLibrary(dll);

    std::cout << "\nLinearSystemLib.dll unloaded successfully!\n";

    return 0;
}
