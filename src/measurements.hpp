#pragma once

#include "codec.hpp"
#include "utils.hpp"

#include <vector> 
#include <cstdint> 

template<typename Unencoded_Data>
double measure_compression_ratio(const Unencoded_Data& unencoded_data, const Codec<Unencoded_Data>& codec)
{
    const std::size_t unencoded_element_count = unencoded_data.size();

    const std::size_t bits_per_element = sizeof(typename Unencoded_Data::value_type) * BITS_PER_BYTE;

    const std::size_t unencoded_bit_count = unencoded_element_count * bits_per_element; 

    const std::size_t encoded_bit_count = codec.encode(unencoded_data).size();

    return static_cast<double>(encoded_bit_count) / unencoded_bit_count;
}

double calculate_theoreticaal_entropy_per_symbol(const std::vector<double>& symbolFrequencies);

double measure_codec_entropy_per_symbol(const Codec<std::uint8_t>& codec, const std::vector<std::uint8_t>& symbols);
