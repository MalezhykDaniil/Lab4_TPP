#include <Windows.h>
#include <iostream>
#include <iomanip>
#include <cmath>
#include "LinearSystem.h"

using namespace std;

int main()
{
    cout << fixed << setprecision(6);

    cout << "=== LINEAR SYSTEM SDK: IMPLICIT LINKING ===\n";

    cout << "\n[TEST 1] Normal system\n";

    const int n = 3;

    const double A[n * n] = {
         2,  1, -1,
        -3, -1,  2,
        -2,  1,  2
    };

    const double b[n] = { 8, -11, -3 };
    double x[n] = {};

    int status = solve(A, b, x, n);

    cout << "Status: " << status << '\n';
    cout << "Solution: ";

    for (int i = 0; i < n; i++)
        cout << x[i] << " ";

    cout << "\nExpected: 2 3 -1\n";

    cout << "Residual: " << residual(A, b, x, n) << '\n';
    cout << "Check: "
        << checkSolution(A, b, x, n, 1e-9) << '\n';

    cout << "\n[TEST 2] Zero size\n";

    double dummyA[] = { 1 };
    double dummyB[] = { 1 };
    double dummyX[] = { 0 };

    cout << "Returned status: "
        << solve(dummyA, dummyB, dummyX, 0) << '\n';

    cout << "\n[TEST 3] Negative size\n";

    cout << "Returned status: "
        << solve(dummyA, dummyB, dummyX, -1) << '\n';

    cout << "\n[TEST 4] Singular matrix\n";

    const double singularA[] = {
        1, 2,
        2, 4
    };

    const double singularB[] = { 3, 6 };
    double singularX[2] = {};

    int singularStatus = solve(
        singularA, singularB, singularX, 2
    );

    cout << "Status: " << singularStatus << '\n';
    cout << "Solution: "
        << singularX[0] << " "
        << singularX[1] << '\n';

    cout << "\n[TEST 5] Negative tolerance\n";

    cout << "Returned value: "
        << checkSolution(A, b, x, n, -1.0) << '\n';

    cout << "\n[TEST 6] Large numeric values\n";

    const double largeA[] = {
        1e100, 0,
        0, 1e100
    };

    const double largeB[] = { 1e100, 1e100 };
    double largeX[2] = {};

    int largeStatus = solve(largeA, largeB, largeX, 2);

    cout << "Status: " << largeStatus << '\n';
    cout << "Solution: "
        << largeX[0] << " " << largeX[1] << '\n';

    cout << "\n[TEST 7] Large system (128x128)\n";

    const int bigN = 128;

    double* bigA = new double[bigN * bigN]();
    double* bigB = new double[bigN]();
    double* bigX = new double[bigN]();

    for (int i = 0; i < bigN; i++)
    {
        bigA[i * bigN + i] = 1.0;
        bigB[i] = 1.0;
    }

    int bigStatus = solve(bigA, bigB, bigX, bigN);

    cout << "Status: " << bigStatus << '\n';
    cout << "First result: " << bigX[0] << '\n';
    cout << "Last result: " << bigX[bigN - 1] << '\n';

    delete[] bigA;
    delete[] bigB;
    delete[] bigX;

    cout << "\n[TEST 8] Null pointers\n";
    cout << "This test is intentionally NOT executed directly.\n";
    cout << "A nullptr may cause an access violation if the DLL "
        "does not validate pointers.\n";

    cout << "\n[TEST 9] Gaussian elimination\n";

    double matrix[] = {
         2,  1, -1,   8,
        -3, -1,  2, -11,
        -2,  1,  2,  -3
    };

    cout << "Status: "
        << gaussianElimination(matrix, n) << '\n';

    cout << "Completed.\n";

    return 0;
}
