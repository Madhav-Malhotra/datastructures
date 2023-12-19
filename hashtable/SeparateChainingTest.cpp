// @file         - SeparateChainingTest.cpp
// @brief        - Testing a hashtable with separate chaining for collisions
// @author       - Madhav Malhotra
// @date         - 2023-12-18
// @version      - 0.0.0
// =============================================================================

#include <random>
#include <iostream>
#include "./SeparateChaining.hpp"

int main() {
    // Test initialisation
    SC_HashTable<short, int> my_map{};
    std::cout << "Init" << std::endl;
    std::cout << "Old max depth: " << my_map.max_depth() << std::endl;
    my_map.set_max_depth(3);
    std::cout << "New max depth: " << my_map.max_depth() << std::endl;

    // Test data addition
    std::mt19937 gen(42);
    std::uniform_int_distribution<short> dist(1,10000);
    std::size_t idx = 0;

    for (std::size_t i = 0; i < 21; ++i) {
        idx = dist(gen);
        my_map.add(idx, i);
    }

    my_map.print();
    std::cout << "After addition: " << my_map.count() << std::endl;
    
    // Test retrieval
    bool found = false;
    std::cout << my_map.at(idx, found) << " " << found << std::endl;

    // Test removal
    std::cout << my_map.remove(idx) << std::endl;
    std::cout << "After removal: " << my_map.count() << std::endl;
    std::cout << my_map.at(idx, found) << " " << found << std::endl;

    std::cout << my_map.remove(dist(gen)) << std::endl;
    std::cout << "Size: " << my_map.count() << std::endl;

    my_map.clear();
    std::cout << "Final size: " << my_map.count() << std::endl;

    return 0;
}