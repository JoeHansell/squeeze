#pragma once

#include "utils.hpp"
#include "codec.hpp"

#include <variant>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <memory>
#include <unordered_map>

class Huffman_Codec : public Codec<Symbol>
{
public:
    Huffman_Codec(const std::unordered_map<Symbol, double>& symbol_frequencies);

    std::vector<bool> encode(const std::vector<Symbol>& decoded_data);

    std::vector<Symbol> decode(const std::vector<bool>& encoded_data);

private:
    static Binary_Tree<Symbol> make_decoding_tree(const std::unordered_map<Symbol, double>& symbol_frequencies);

    static std::unordered_map<Symbol, std::vector<bool>> make_encoding_map(const Binary_Tree<Symbol>& decoding_tree);

    Binary_Tree<Symbol> _decoding_tree;

    std::unordered_map<Symbol, std::vector<bool>> _encoding_map;
};
