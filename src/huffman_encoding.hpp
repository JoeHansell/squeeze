#pragma once

#include "utils.hpp"
#include "codec.hpp"

#include <variant>
#include <cstdint>
#include <cstddef>
#include <vector>
#include <memory>
#include <map>
#include <unordered_map>

template <typename Unencoded_Data>
class Huffman_Codec : public Codec<Unencoded_Data>
{
public:
    using Symbol = typename Unencoded_Data::value_type; 

    Huffman_Codec(const std::unordered_map<Symbol, double>& symbol_frequencies) :
        _decoding_tree(make_decoding_tree(symbol_frequencies)),
        _encoding_map(make_encoding_map(_decoding_tree))
    {}

    std::vector<bool> encode(const Unencoded_Data& decoded_data) const override
    {
        std::vector<bool> encoded_data;

        for (const auto& symbol : decoded_data)
        {
            // TODO handle missing symbol
            const std::vector<bool>& symbol_bits = _encoding_map.at(symbol);

            encoded_data.insert(encoded_data.end(), symbol_bits.begin(), symbol_bits.end());
        }

        return encoded_data;
    }

    Unencoded_Data decode(const std::vector<bool>& encoded_data) const override
    {
        // TODO handle root node being leaf

        Unencoded_Data decoded_data;

        const Binary_Tree<Symbol>* tree_location = &_decoding_tree;

        for(const auto& bit : encoded_data)
        {
            tree_location = bit ? &tree_location->right_child() : &tree_location->left_child();

            if(tree_location->is_leaf())
            {
                decoded_data.push_back(tree_location->value());

                tree_location = &_decoding_tree;
            }
        }

        // TODO handle unfinished Symbol

        return decoded_data;
    }

private:
    static Binary_Tree<Symbol> make_decoding_tree(const std::unordered_map<Symbol, double>& symbol_frequencies)
    {
        // TODO handle symbol_frequencies of size less than 2

        std::multimap<double, std::unique_ptr<Binary_Tree<Symbol>>> trees;

        for (const auto& [symbol, frequency] : symbol_frequencies)
        {
            trees.emplace(frequency, std::make_unique<Binary_Tree<Symbol>>(symbol));
        }

        while (trees.size() > 1)
        {
            const auto least_frequent_node = trees.extract(trees.begin());
            const auto second_least_frequent_node = trees.extract(trees.begin());

            std::unique_ptr<Binary_Tree<Symbol>> least_frequent_tree = std::move(least_frequent_node.mapped());
            std::unique_ptr<Binary_Tree<Symbol>> second_least_frequent_tree = std::move(second_least_frequent_node.mapped());

            const double least_frequent_tree_frequency = least_frequent_node.key();
            const double second_least_frequent_tree_frequency = second_least_frequent_node.key();

            const double combined_frequency = least_frequent_tree_frequency + second_least_frequent_tree_frequency;

            std::unique_ptr<Binary_Tree<Symbol>> combined_tree = std::make_unique<Binary_Tree<Symbol>>(std::move(least_frequent_tree), std::move(second_least_frequent_tree));

            trees.emplace(combined_frequency, std::move(combined_tree));
        }

        return std::move(*trees.extract(trees.begin()).mapped().release());
    }

    // TODO inefficient
    static std::unordered_map<Symbol, std::vector<bool>> make_encoding_map(const Binary_Tree<Symbol>& decoding_tree)
    {
        if (decoding_tree.is_leaf())
        {
            return {{decoding_tree.value(), std::vector<bool>{}}};
        }

        std::unordered_map<Symbol, std::vector<bool>> left_child_map = make_encoding_map(decoding_tree.left_child());
        for (auto& [symbol, bits] : left_child_map)
        {
            bits.insert(bits.begin(), false);
        }
        
        std::unordered_map<Symbol, std::vector<bool>> right_child_map = make_encoding_map(decoding_tree.right_child());
        for (auto& [symbol, bits] : right_child_map)
        {
            bits.insert(bits.begin(), true);
        }
        
        std::unordered_map<Symbol, std::vector<bool>> combined_maps = std::move(left_child_map);
        
        combined_maps.merge(right_child_map);

        return combined_maps;
    }

    Binary_Tree<Symbol> _decoding_tree;

    std::unordered_map<Symbol, std::vector<bool>> _encoding_map;
};
