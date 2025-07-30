#pragma once

#include <vector>

template <typename Unencoded_Data>
struct Codec
{
    virtual std::vector<bool> encode(const Unencoded_Data& unencoded_data) const = 0;

    virtual Unencoded_Data decode(const std::vector<bool>& encoded_data) const = 0;
};