#pragma once

#include <limits>
#include <concepts>
#include <cstdint>

template<std::unsigned_integral T>
bool sum_overflows(const T lhs, const T rhs)
{
    return std::numeric_limits<T>::max() - lhs < rhs;
}

template<std::unsigned_integral T, std::unsigned_integral... T_Pack>
bool sum_overflows(const T first, const T second, const T_Pack... others)
{
    return sum_overflows(first, second) or sum_overflows(static_cast<T>(first + second), others...);
}