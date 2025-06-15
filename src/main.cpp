#include "huffman_encoding.hpp"

#include <iostream>

int main()
{
    std::cout << "Hello, World!" << std::endl;

    huffman_encoding::Decoding_Tree leaf_0 = std::uint8_t{0};
    huffman_encoding::Decoding_Tree leaf_1 = std::uint8_t{1};
    huffman_encoding::Decoding_Tree leaf_2 = std::uint8_t{2};

    huffman_encoding::Decoding_Tree internal_node = huffman_encoding::Internal_Decoding_Tree_Node{&leaf_1, &leaf_2};

    huffman_encoding::Decoding_Tree root_node = huffman_encoding::Internal_Decoding_Tree_Node{&leaf_0, &internal_node};

    const huffman_encoding::Encoding_Map encoding_map = {
        {0, {false}},
        {1, {true, false}},
        {2, {true, true}}
    };

    const std::vector<huffman_encoding::Symbol> original_data = {0,0,1,2,0,0,1,2};
    
    const std::vector<bool> encoded_data = huffman_encoding::encode(original_data, encoding_map);

    const std::vector<huffman_encoding::Symbol> decoded_data = huffman_encoding::decode(encoded_data, root_node);
    
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

    return 0;
}