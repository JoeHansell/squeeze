#pragma once

#include <variant>
#include <cstdint>
#include <vector>
#include <map>

namespace huffman_encoding
{

using Symbol = std::uint8_t;

using Encoding_Map = std::map<Symbol, std::vector<bool>>;

struct Internal_Decoding_Tree_Node;

using Decoding_Tree = std::variant<Internal_Decoding_Tree_Node, Symbol>;

struct Internal_Decoding_Tree_Node
{
    Decoding_Tree* left;
    Decoding_Tree* right;
};

std::vector<bool> encode(const std::vector<Symbol>& decoded_data, const Encoding_Map& encoding_map);

std::vector<Symbol> decode(const std::vector<bool>& encoded_data, const Decoding_Tree& decoding_tree);

}