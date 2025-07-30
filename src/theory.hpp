#pragma once

#include "utils.hpp"

#include <cmath>

template <typename Unencoded_Data>
double calculate_entropy_per_symbol(const Unencoded_Data& unencoded_data)
{
    using Symbol = typename Unencoded_Data::value_type; 

    const std::unordered_map<Symbol, double> symbol_frequencies = get_symbol_frequencies<Symbol>(unencoded_data);

    double entropy_per_symbol = 0;

    for (const auto& [symbol, frequency] : symbol_frequencies)
    {
        entropy_per_symbol += -1 * frequency * std::log2(frequency);
    }

    return entropy_per_symbol;
}

template <typename Unencoded_Data>
double calculate_entropy_coding_compression_ratio(const Unencoded_Data& unencoded_data)
{
    using Symbol = typename Unencoded_Data::value_type; 

    const double entropy_per_symbol = calculate_entropy_per_symbol(unencoded_data);

    const std::size_t bits_per_symbol = sizeof(Symbol) * BITS_PER_BYTE;

    return entropy_per_symbol / bits_per_symbol;
}