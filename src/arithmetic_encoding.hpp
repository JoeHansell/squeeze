#pragma once

#include "infinite_precision_proportion.hpp"

#include <vector>
#include <cstdint>
#include <unordered_map>

namespace arithmetic_encoding
{
    
using Symbol = std::uint8_t;
using Proportion = Infinite_Precision_Proportion;



std::vector<bool> encode(const std::vector<Symbol>& decoded_data, const std::unordered_map<Symbol, std::size_t>& frequencies);

// std::vector<Symbol> decode(const std::vector<bool>& encoded_data, const Decoding_Tree& decoding_tree);


}