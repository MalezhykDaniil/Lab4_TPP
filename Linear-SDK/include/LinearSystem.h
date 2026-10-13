#pragma once

#ifdef LINEARSYSTEM_EXPORTS
#define LINEARSYSTEM_API extern "C" __declspec(dllexport)
#else
#define LINEARSYSTEM_API extern "C" __declspec(dllimport)
#endif

LINEARSYSTEM_API int gaussianElimination(
    double* matrix,
    int n
);

LINEARSYSTEM_API int solve(
    const double* A,
    const double* b,
    double* x,
    int n
);

LINEARSYSTEM_API double residual(
    const double* A,
    const double* b,
    const double* x,
    int n
);

LINEARSYSTEM_API int checkSolution(
    const double* A,
    const double* b,
    const double* x,
    int n,
    double tolerance
);
