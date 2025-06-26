#pragma once

#include <vector>
#include <cstdint>

class Infinite_Precision_Proportion
{
    public:
        Infinite_Precision_Proportion() = default;
        Infinite_Precision_Proportion(std::vector<std::uint64_t> data);
        
        Infinite_Precision_Proportion operator+(const Infinite_Precision_Proportion& rhs) const;
        Infinite_Precision_Proportion operator*(const Infinite_Precision_Proportion& rhs) const;

        Infinite_Precision_Proportion& operator+=(const Infinite_Precision_Proportion& rhs);
        Infinite_Precision_Proportion& operator*=(const Infinite_Precision_Proportion& rhs);
        
        Infinite_Precision_Proportion operator>>(std::size_t bit_count) const;
        
        void display() const;
        
    private:
        void prune_trailing_zeros();

        bool get_bit(std::size_t bit_index) const;

        std::vector<std::uint64_t> _data;
};