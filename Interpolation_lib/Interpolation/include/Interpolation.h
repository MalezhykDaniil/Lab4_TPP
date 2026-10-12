#pragma once

#ifdef INTERPOLATION_EXPORTS
#define INTERPOLATION_API __declspec(dllexport)
#else
#define INTERPOLATION_API __declspec(dllimport)
#endif

#ifdef __cplusplus
extern "C" {
#endif

    INTERPOLATION_API double lagrange(
        const double* x,
        const double* y,
        int count,
        double target
    );

    INTERPOLATION_API double linearInterpolation(
        double x0,
        double y0,
        double x1,
        double y1,
        double target
    );

    INTERPOLATION_API double interpolate(
        const double* x,
        const double* y,
        int count,
        double target
    );

    INTERPOLATION_API double interpolationError(
        double actual,
        double estimated
    );

#ifdef __cplusplus
}
#endif