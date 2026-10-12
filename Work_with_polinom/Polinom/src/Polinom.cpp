
#include "Polinom.h"

#include <algorithm>
#include <cmath>
#include <limits>
#include <new>
#include <stdexcept>
#include <vector>

namespace {

    bool validInput(const double* p, size_t count)
    {
        return p != nullptr
            && count > 0
            && count <= std::vector<double>().max_size();
    }

    bool finiteArray(const double* p, size_t count)
    {
        for (size_t i = 0; i < count; ++i) {
            if (!std::isfinite(p[i]))
                return false;
        }

        return true;
    }

    bool finiteVector(const std::vector<double>& values)
    {
        for (double value : values) {
            if (!std::isfinite(value))
                return false;
        }

        return true;
    }

    int writeResult(
        const std::vector<double>& result,
        double* out,
        size_t capacity,
        size_t* out_count)
    {
        if (out_count == nullptr)
            return POLINOM_INVALID_ARGUMENT;

        *out_count = result.size();

        if (out == nullptr)
            return POLINOM_INVALID_ARGUMENT;

        if (capacity < result.size())
            return POLINOM_BUFFER_TOO_SMALL;

        if (!finiteVector(result))
            return POLINOM_NUMERIC_ERROR;

        std::copy(result.begin(), result.end(), out);

        return POLINOM_OK;
    }

    template <typename Function>
    int safeCall(Function&& function) noexcept
    {
        try {
            return function();
        }
        catch (const std::bad_alloc&) {
            return POLINOM_RESOURCE_ERROR;
        }
        catch (const std::length_error&) {
            return POLINOM_RESOURCE_ERROR;
        }
        catch (...) {
            return POLINOM_INTERNAL_ERROR;
        }
    }

} 


extern "C" {

    int poly_add(
        const double* a, size_t a_count,
        const double* b, size_t b_count,
        double* out, size_t out_capacity,
        size_t* out_count)
    {
        if (out_count != nullptr)
            *out_count = 0;

        if (!validInput(a, a_count) ||
            !validInput(b, b_count) ||
            out == nullptr ||
            out_count == nullptr) {
            return POLINOM_INVALID_ARGUMENT;
        }

        if (!finiteArray(a, a_count) ||
            !finiteArray(b, b_count)) {
            return POLINOM_NUMERIC_ERROR;
        }

        return safeCall([&]() -> int {
            const size_t resultSize =
                std::max(a_count, b_count);

            std::vector<double> result(resultSize, 0.0);

            for (size_t i = 0; i < a_count; ++i)
                result[i] += a[i];

            for (size_t i = 0; i < b_count; ++i)
                result[i] += b[i];

            return writeResult(
                result, out, out_capacity, out_count);
            });
    }


    int poly_multiply(
        const double* a, size_t a_count,
        const double* b, size_t b_count,
        double* out, size_t out_capacity,
        size_t* out_count)
    {
        if (out_count != nullptr)
            *out_count = 0;

        if (!validInput(a, a_count) ||
            !validInput(b, b_count) ||
            out == nullptr ||
            out_count == nullptr) {
            return POLINOM_INVALID_ARGUMENT;
        }

        if (!finiteArray(a, a_count) ||
            !finiteArray(b, b_count)) {
            return POLINOM_NUMERIC_ERROR;
        }


        const size_t maxSize =
            std::numeric_limits<size_t>::max();

        if (a_count > maxSize - b_count + 1)
            return POLINOM_RESOURCE_ERROR;

        const size_t resultSize = a_count + b_count - 1;

        if (resultSize > std::vector<double>().max_size())
            return POLINOM_RESOURCE_ERROR;

        return safeCall([&]() -> int {
            std::vector<double> result(resultSize, 0.0);

            for (size_t i = 0; i < a_count; ++i) {
                for (size_t j = 0; j < b_count; ++j) {
                    result[i + j] += a[i] * b[j];
                }
            }

            return writeResult(
                result, out, out_capacity, out_count);
            });
    }


    int poly_evaluate(
        const double* p, size_t count,
        double x, double* result)
    {
        if (!validInput(p, count) || result == nullptr)
            return POLINOM_INVALID_ARGUMENT;

        if (!std::isfinite(x) || !finiteArray(p, count))
            return POLINOM_NUMERIC_ERROR;

        return safeCall([&]() -> int {
            // Схема Горнера.
            double value = 0.0;

            for (size_t i = count; i > 0; --i) {
                value = value * x + p[i - 1];

                if (!std::isfinite(value))
                    return POLINOM_NUMERIC_ERROR;
            }

            *result = value;
            return POLINOM_OK;
            });
    }


    int poly_derivative(
        const double* p, size_t count,
        double* out, size_t out_capacity,
        size_t* out_count)
    {
        if (out_count != nullptr)
            *out_count = 0;

        if (!validInput(p, count) ||
            out == nullptr ||
            out_count == nullptr) {
            return POLINOM_INVALID_ARGUMENT;
        }

        if (!finiteArray(p, count))
            return POLINOM_NUMERIC_ERROR;

        return safeCall([&]() -> int {
            std::vector<double> result;

            if (count == 1) {
                result = { 0.0 };
            }
            else {
                result.resize(count - 1);

                for (size_t i = 1; i < count; ++i) {
                    result[i - 1] =
                        p[i] * static_cast<double>(i);
                }
            }

            return writeResult(
                result, out, out_capacity, out_count);
            });
    }


    int poly_integral(
        const double* p, size_t count,
        double C,
        double* out, size_t out_capacity,
        size_t* out_count)
    {
        if (out_count != nullptr)
            *out_count = 0;

        if (!validInput(p, count) ||
            out == nullptr ||
            out_count == nullptr) {
            return POLINOM_INVALID_ARGUMENT;
        }

        if (!std::isfinite(C) || !finiteArray(p, count))
            return POLINOM_NUMERIC_ERROR;

        if (count == std::numeric_limits<size_t>::max() ||
            count + 1 > std::vector<double>().max_size()) {
            return POLINOM_RESOURCE_ERROR;
        }

        return safeCall([&]() -> int {
            std::vector<double> result(count + 1);

            result[0] = C;

            for (size_t i = 0; i < count; ++i) {
                result[i + 1] =
                    p[i] / static_cast<double>(i + 1);
            }

            return writeResult(
                result, out, out_capacity, out_count);
            });
    }

} 