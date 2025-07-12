#pragma once

#include <limits>
#include <concepts>
#include <cstdint>
#include <memory>
#include <optional>

using Symbol = std::uint8_t;

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

// TODO null checks
template<typename Leaf_T>
class Binary_Tree
{
public:
    Binary_Tree(Leaf_T value) :
        _value(std::move(value))
    {}

    Binary_Tree(std::unique_ptr<Binary_Tree> left_child, std::unique_ptr<Binary_Tree> right_child) :
        _left_child(std::move(left_child)),
        _right_child(std::move(right_child))
    {}

    bool is_leaf() const
    {
        return _value.has_value();
    }

    const Leaf_T& value() const
    {
        return *_value;
    }

    const Binary_Tree& left_child() const
    {
        return *_left_child;
    }

    const Binary_Tree& right_child() const
    {
        return *_right_child;
    }

private:
    std::optional<Leaf_T> _value; 

    std::unique_ptr<Binary_Tree> _left_child;
    std::unique_ptr<Binary_Tree> _right_child;
};