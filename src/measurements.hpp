#pragma once

#include "codec.hpp"

#include <vector> 
#include <cstdint> 

double calculate_theoreticaal_entropy_per_symbol(const std::vector<double>& symbolFrequencies);

double measure_codec_entropy_per_symbol(const Codec<std::uint8_t>& codec, const std::vector<std::uint8_t>& symbols);

