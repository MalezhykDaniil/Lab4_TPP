
#pragma once

#include <stddef.h>


#ifdef POLINOM_EXPORTS
#define POLINOM_API __declspec(dllexport)
#else
#define POLINOM_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

    enum PolinomStatus {
        POLINOM_OK = 0,
        POLINOM_INVALID_ARGUMENT = 1,
        POLINOM_BUFFER_TOO_SMALL = 2,
        POLINOM_RESOURCE_ERROR = 3,
        POLINOM_NUMERIC_ERROR = 4,
        POLINOM_INTERNAL_ERROR = 5
    };

    POLINOM_API int poly_add(
        const double* a, size_t a_count,
        const double* b, size_t b_count,
        double* out, size_t out_capacity,
        size_t* out_count
    );

    POLINOM_API int poly_multiply(
        const double* a, size_t a_count,
        const double* b, size_t b_count,
        double* out, size_t out_capacity,
        size_t* out_count
    );

    POLINOM_API int poly_evaluate(
        const double* p, size_t count,
        double x, double* result
    );

    POLINOM_API int poly_derivative(
        const double* p, size_t count,
        double* out, size_t out_capacity,
        size_t* out_count
    );

    POLINOM_API int poly_integral(
        const double* p, size_t count,
        double C,
        double* out, size_t out_capacity,
        size_t* out_count
    );

#ifdef __cplusplus
}
#endif
