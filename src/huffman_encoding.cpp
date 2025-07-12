#include "huffman_encoding.hpp"

#include <map>
#include <iostream> // TODO remove

void print_tree(const Binary_Tree<Symbol>& t)
{
    if (t.is_leaf())
    {
        std::cout << (int)t.value() << std::endl;
        return;
    }

    std::cout << "left child" << std::endl; 
    print_tree(t.left_child());
    std::cout << "right child" << std::endl; 
    print_tree(t.right_child());
}

Huffman_Codec::Huffman_Codec(const std::unordered_map<Symbol, double>& symbol_frequencies) :
    _decoding_tree(make_decoding_tree(symbol_frequencies)),
    _encoding_map(make_encoding_map(_decoding_tree))
{
    print_tree(_decoding_tree);

    std::cout << _encoding_map.size() << std::endl;
    for (const auto& [a,b] : _encoding_map)
    {
        std::cout << (int)a << std::endl;
    }

}

std::vector<bool> Huffman_Codec::encode(const std::vector<Symbol>& decoded_data)
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

std::vector<Symbol> Huffman_Codec::decode(const std::vector<bool>& encoded_data)
{
    // TODO handle root node being leaf

    std::vector<Symbol> decoded_data;

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

Binary_Tree<Symbol> Huffman_Codec::make_decoding_tree(const std::unordered_map<Symbol, double>& symbol_frequencies)
{
    // TODO handle symbol_frequencies of size less than 2

    std::cout << "make decoding tree" << std::endl;

    std::multimap<double, std::unique_ptr<Binary_Tree<Symbol>>> trees;

    for (const auto& [symbol, frequency] : symbol_frequencies)
    {
        trees.emplace(frequency, std::make_unique<Binary_Tree<Symbol>>(symbol));
    }

    std::cout << "B" << std::endl;

    while (trees.size() > 1)
    {
        std::cout << trees.size() << std::endl;

        const auto least_frequent_node = trees.extract(trees.begin());
        const auto second_least_frequent_node = trees.extract(trees.begin());

        std::unique_ptr<Binary_Tree<Symbol>> least_frequent_tree = std::move(least_frequent_node.mapped());
        std::unique_ptr<Binary_Tree<Symbol>> second_least_frequent_tree = std::move(second_least_frequent_node.mapped());

        const double least_frequent_tree_frequency = least_frequent_node.key();
        const double second_least_frequent_tree_frequency = second_least_frequent_node.key();

        const double combined_frequency = least_frequent_tree_frequency + second_least_frequent_tree_frequency;

        std::unique_ptr<Binary_Tree<Symbol>> combined_tree = std::make_unique<Binary_Tree<Symbol>>(std::move(least_frequent_tree), std::move(second_least_frequent_tree));

        std::cout << "AA" << std::endl;

        trees.emplace(combined_frequency, std::move(combined_tree));
    }

    return std::move(*trees.extract(trees.begin()).mapped().release());
}

// TODO inefficient
std::unordered_map<Symbol, std::vector<bool>> Huffman_Codec::make_encoding_map(const Binary_Tree<Symbol>& decoding_tree)
{
    std::cout << "make encoding map" << std::endl;

    if (decoding_tree.is_leaf())
    {
        return {{decoding_tree.value(), std::vector<bool>{}}};
    }

    std::cout << "C" << std::endl;
    
    
    std::unordered_map<Symbol, std::vector<bool>> left_child_map = make_encoding_map(decoding_tree.left_child());
    for (auto& [symbol, bits] : left_child_map)
    {
        bits.insert(bits.begin(), false);
    }
    
    std::cout << "D" << std::endl;
    std::unordered_map<Symbol, std::vector<bool>> right_child_map = make_encoding_map(decoding_tree.right_child());
    for (auto& [symbol, bits] : right_child_map)
    {
        bits.insert(bits.begin(), true);
    }
    
    std::cout << "E" << std::endl;
    std::unordered_map<Symbol, std::vector<bool>> combined_maps = std::move(left_child_map);
    std::cout << "F" << std::endl;
    std::cout << "left size " << combined_maps.size() << std::endl;
    
    combined_maps.merge(right_child_map);
    std::cout << "combined size " << combined_maps.size() << std::endl;
    std::cout << "G" << std::endl;

    return combined_maps;
}