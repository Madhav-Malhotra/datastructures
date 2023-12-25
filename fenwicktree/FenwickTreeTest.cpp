// @file         - FenwickTreeTest.cpp
// @brief        - Testing a Fenwick Tree
// @author       - Madhav Malhotra
// @date         - 2023-12-24
// @version      - 0.0.0
// =============================================================================

#include <random>
#include <iostream>
#include "./FenwickTree.hpp"

int main() {
    // Test initialisation
    FenwickTree<int> my_tree = FenwickTree<int>(8);
    std::cout << "Capacity: " << my_tree.get_cap() << std::endl;
    
    // Test data addition
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(1,10);
  
    for (std::size_t i = 1; i <= 8; ++i) {
        std::size_t val = dist(gen);
        my_tree.set_el(i, val);
    }

    my_tree.print(); 

    // Test sums
    std::cout << "1: " << my_tree.partial_sum(1) << std::endl;
    std::cout << "7: " << my_tree.partial_sum(7) << std::endl;
    std::cout << "8: " << my_tree.partial_sum(8) << std::endl;

    std::cout << "1-3: " << my_tree.range_sum(1,3) << std::endl;
    std::cout << "3-7: " << my_tree.range_sum(3,7) << std::endl;
    std::cout << "4-4: " << my_tree.range_sum(4,4) << std::endl;

    // Test clear
    my_tree.clear();
    std::cout << "Final size: " << my_tree.get_cap() << std::endl;
    return 0;
}