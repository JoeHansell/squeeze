#include "huffman_encoding.hpp"

namespace huffman_encoding
{

std::vector<bool> encode(const std::vector<Symbol>& decoded_data, const Encoding_Map& encoding_map)
{
    std::vector<bool> encoded_data;

    for (const auto& symbol : decoded_data)
    {
        // TODO handle missing symbol
        const std::vector<bool>& symbol_bits = encoding_map.at(symbol);

        encoded_data.insert(encoded_data.end(), symbol_bits.begin(), symbol_bits.end());
    }

    return encoded_data;
}

std::vector<Symbol> decode(const std::vector<bool>& encoded_data, const Decoding_Tree& decoding_tree)
{
    // TODO handle case of decoding_tree being Symbol

    std::vector<Symbol> decoded_data;

    const Decoding_Tree* tree_location = &decoding_tree;

    for(const auto& bit : encoded_data)
    {
        if (bit)
        {
            tree_location = std::get<Internal_Decoding_Tree_Node>(*tree_location).right;
        }
        else
        {
            tree_location = std::get<Internal_Decoding_Tree_Node>(*tree_location).left;
        }

        if(std::holds_alternative<Symbol>(*tree_location))
        {
            decoded_data.push_back(std::get<Symbol>(*tree_location));

            tree_location = &decoding_tree;
        }
    }

    // TODO handle unfinished Symbol

    return decoded_data;
}

}