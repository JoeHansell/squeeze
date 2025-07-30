#pragma once

#include <limits>
#include <concepts>
#include <cstdint>
#include <memory>
#include <optional>
#include <string>
#include <filesystem>
#include <span>
#include <unordered_map>
#include <string_view>
#include <vector>

inline constexpr std::size_t BITS_PER_BYTE = 8;

template<typename Symbol>
std::unordered_map<Symbol, std::size_t> get_symbol_counts(const std::span<const Symbol> symbols)
{
    std::unordered_map<Symbol, std::size_t> symbol_counts;
    
    for (const auto& symbol : symbols)
    {
        ++symbol_counts[symbol];
    }

    return symbol_counts;
}

template<typename Symbol>
std::unordered_map<Symbol, double> get_symbol_frequencies(const std::span<const Symbol> symbols)
{
    const std::unordered_map<Symbol, std::size_t> symbol_counts = get_symbol_counts(symbols);

    std::unordered_map<Symbol, double> symbol_frequencies;
    
    for (const auto& [symbol, count] : symbol_counts)
    {
        const double frequency = static_cast<double>(count) / symbols.size();

        symbol_frequencies.emplace(symbol, frequency);
    }

    return symbol_frequencies;
}

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