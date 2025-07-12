#include "measurements.hpp"

#include <cmath>

double calculate_theoreticaal_entropy_per_symbol(const std::vector<double>& symbolFrequencies)
{
    double entropy = 0;

    for (const auto& frequency : symbolFrequencies)
    {
        entropy += -frequency * std::log2(frequency);
    }

    return entropy;
}

double measure_codec_entropy_per_symbol(const Codec<std::uint8_t>& codec, const std::vector<std::uint8_t>& symbols)
{
    const std::vector<bool> encoded_date = codec.encode(symbols);

    return static_cast<double>(encoded_date.size()) / symbols.size();
}