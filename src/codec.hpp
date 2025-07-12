#pragma once

#include <vector>

template <typename Symbol>
struct Codec
{
    virtual std::vector<bool> encode(const std::vector<Symbol>& decoded_data) const = 0;

    virtual std::vector<Symbol> decode(const std::vector<bool>& encoded_data) const = 0;
};