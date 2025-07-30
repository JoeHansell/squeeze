#include "huffman_encoding.hpp"
#include "infinite_precision_proportion.hpp"
#include "utils.hpp"

#include <iostream>

int main()
{
    const std::unordered_map<std::uint8_t, double> symbol_frequencies = {{0, 0.5}, {1, 0.25}, {2, 0.125}, {3, 0.125}}; 

    Huffman_Codec<std::vector<std::uint8_t>> huffman_codec{symbol_frequencies};

    const std::vector<std::uint8_t> original_data = {0,0,0,0,0,0,0,0,1,1,1,1,2,2,3,3};
    
    const std::vector<bool> encoded_data = huffman_codec.encode(original_data);

    const std::vector<std::uint8_t> decoded_data = huffman_codec.decode(encoded_data);
    
    std::cout << "Original data: ";
    for (const auto& symbol : original_data)
    {
        std::cout << static_cast<int>(symbol) << " ";
    }
    std::cout << std::endl;

    std::cout << "Encoded data: ";
    for (const auto& bit : encoded_data)
    {
        std::cout << bit;
    }
    std::cout << std::endl;

    std::cout << "Decoded data: ";
    for (const auto& symbol : decoded_data)
    {
        std::cout << static_cast<int>(symbol) << " ";
    }
    std::cout << std::endl;

    std::cout << encoded_data.size() << std::endl;

    return 0;
}
