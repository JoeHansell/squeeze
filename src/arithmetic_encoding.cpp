#include "arithmetic_encoding.hpp"


namespace arithmetic_encoding
{

namespace
{

struct Range_Info
{
    Proportion offset;
    Proportion size;
};

std::vector<Range_Info> calculate_ranges(const std::unordered_map<Symbol, std::size_t>& frequencies, const std::size_t bit_depth)
{
    std::size_t frequency_total = 0;

    for (const auto& [symbol, frequency] : frequencies)
    {
        frequency_total += frequency;
    }


}

std::vector<bool> encode(const std::vector<Symbol>& decoded_data, const std::unordered_map<Symbol, std::size_t>& frequencies)
{

}

}

}