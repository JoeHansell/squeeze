#include "huffman_encoding.hpp"
#include "infinite_precision_proportion.hpp"
#include "utils.hpp"

#include <iostream>

int main()
{
    // Infinite_Precision_Proportion ipp0{{0b01010011101001, 0b100001011110101,0,0}};
    // Infinite_Precision_Proportion ipp0{{1}};
    // Infinite_Precision_Proportion ipp1{{0b00111011010,0,0,0,0,0}};

    // Infinite_Precision_Proportion res = ipp0 * ipp0;
    // ipp0.display();
    // res.display();

    // ipp0.display();
    // for (std::size_t i = 0; i < 14;  i++)
    // {
    //     ipp0 = ipp0 >> i;
    //     ipp0.display();
    // }

    // huffman_encoding::Decoding_Tree leaf_0 = std::uint8_t{0};
    // huffman_encoding::Decoding_Tree leaf_1 = std::uint8_t{1};
    // huffman_encoding::Decoding_Tree leaf_2 = std::uint8_t{2};

    // huffman_encoding::Decoding_Tree internal_node = huffman_encoding::Internal_Decoding_Tree_Node{&leaf_1, &leaf_2};

    // huffman_encoding::Decoding_Tree root_node = huffman_encoding::Internal_Decoding_Tree_Node{&leaf_0, &internal_node};

    // const huffman_encoding::Encoding_Map encoding_map = {
    //     {0, {false}},
    //     {1, {true, false}},
    //     {2, {true, true}}
    // };

    const std::unordered_map<std::uint8_t, double> symbol_frequencies = {{0, 0.5}, {1, 0.25}, {2, 0.125}, {3, 0.125}}; 

    Huffman_Codec huffman_codec{symbol_frequencies};

    const std::vector<Symbol> original_data = {0,0,0,0,0,0,0,0,1,1,1,1,2,2,3,3};
    
    const std::vector<bool> encoded_data = huffman_codec.encode(original_data);

    const std::vector<Symbol> decoded_data = huffman_codec.decode(encoded_data);
    
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
