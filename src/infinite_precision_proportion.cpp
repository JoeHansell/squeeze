#include "infinite_precision_proportion.hpp"
#include "utils.hpp"

#include <iostream> // TODO remove

Infinite_Precision_Proportion::Infinite_Precision_Proportion(std::vector<std::uint64_t> data) :
    _data(std::move(data))
{
    prune_trailing_zeros();
}

Infinite_Precision_Proportion Infinite_Precision_Proportion::operator+(const Infinite_Precision_Proportion& rhs) const
{
    const std::size_t min_chunk_count = std::min(_data.size(), rhs._data.size());

    const Infinite_Precision_Proportion& longer_operand  = _data.size() >  rhs._data.size() ? *this : rhs;
    
    std::vector<std::uint64_t> result_data = longer_operand._data;

    bool overflow = false;

    for (std::size_t chunk_index = 0; chunk_index < min_chunk_count; ++chunk_index)
    {
        const std::size_t reverse_chunk_index = min_chunk_count - 1 - chunk_index;

        result_data[reverse_chunk_index] = _data[reverse_chunk_index] + rhs._data[reverse_chunk_index] + static_cast<std::uint64_t>(overflow);
        
        overflow = sum_overflows(_data[reverse_chunk_index], rhs._data[reverse_chunk_index], static_cast<std::uint64_t>(overflow));
    }

    if (overflow)
    {
        // TODO throw
    }

    return {std::move(result_data)};
}

Infinite_Precision_Proportion Infinite_Precision_Proportion::operator*(const Infinite_Precision_Proportion& rhs) const
{
    const std::size_t lhs_bit_count = _data.size() * sizeof(std::uint64_t) * 8;

    Infinite_Precision_Proportion result;

    for (std::size_t lhs_bit_index = 0; lhs_bit_index < lhs_bit_count; ++lhs_bit_index)
    {
        if (get_bit(lhs_bit_index))
        {
            result += rhs >> (lhs_bit_index + 1);
        }
    }

    result.prune_trailing_zeros();

    return result;
}

Infinite_Precision_Proportion Infinite_Precision_Proportion::operator>>(const std::size_t bit_count) const
{
    if (_data.empty())
    {
        return *this;
    }

    const std::size_t bits_per_chunk = sizeof(std::uint64_t) * 8;
    const std::size_t chunks_count = bit_count / bits_per_chunk;
    const std::size_t remaining_bit_count = bit_count % bits_per_chunk;

    std::vector<std::uint64_t> result_data(chunks_count, 0);

    if (remaining_bit_count == 0)
    {
        result_data.insert(result_data.end(), _data.begin(), _data.end());
    }
    else
    {
        result_data.push_back(_data.front() >> remaining_bit_count);
    
        for (std::size_t chunk_index = 1; chunk_index < _data.size(); ++chunk_index)
        {
            result_data.push_back(_data[chunk_index - 1] << (bits_per_chunk - remaining_bit_count) | _data[chunk_index] >> remaining_bit_count);
        }
        
        result_data.push_back(_data.back() << (bits_per_chunk - remaining_bit_count));
    }

    return {result_data};
}

Infinite_Precision_Proportion& Infinite_Precision_Proportion::operator+=(const Infinite_Precision_Proportion& rhs)
{
    *this = *this + rhs;
    
    return *this;
}

Infinite_Precision_Proportion& Infinite_Precision_Proportion::operator*=(const Infinite_Precision_Proportion& rhs)
{
    *this = *this * rhs;
    
    return *this;
}

void Infinite_Precision_Proportion::display() const
{
    std::cout << "0"; 
    
    if (_data.empty())
    {
        std::cout << std::endl;
        return;
    }

    std::cout << "."; 

    const std::size_t bits_per_chunk = sizeof(std::uint64_t) * 8;

    for (const auto& chunk : _data)
    {
        for (std::size_t bit_index = 0; bit_index < bits_per_chunk; ++bit_index)
        {
            std::cout << static_cast<bool>(chunk & (std::size_t(0b1) << (bits_per_chunk - bit_index - 1)));
        }
    }
    std::cout << std::endl;
}

void Infinite_Precision_Proportion::prune_trailing_zeros()
{
    auto first_of_trailing_zeros_it = _data.begin();
    
    for (auto it = _data.begin(); it != _data.end(); ++it)
    {
        if (*it != 0)
        {
            first_of_trailing_zeros_it = std::next(it);
        }
    }

    _data.erase(first_of_trailing_zeros_it, _data.end());
}

bool Infinite_Precision_Proportion::get_bit(const std::size_t bit_index) const
{
    // TODO bounds checking

    const std::size_t bits_per_chunk = sizeof(std::uint64_t) * 8;
    const std::size_t chunks_index = bit_index / bits_per_chunk;
    const std::size_t remaining_bit_index = bit_index % bits_per_chunk;

    return static_cast<bool>(_data[chunks_index] & std::size_t(0b1) << (bits_per_chunk - remaining_bit_index - 1));
}