// @file         - LinearProbing.cpp
// @brief        - Testing a hashtable with open addressing and linear probing
// @author       - Madhav Malhotra
// @date         - 2023-12-21
// @version      - 0.0.0
// =============================================================================

#include <random>
#include <iostream>
#include "./LinearProbing.hpp"

int main() {
    // Test initialisation
    LP_HashTable<int, short> my_map{};
    std::cout << "Init" << std::endl;
    
    std::cout << "Old load threshold: " << my_map.load_threshold() << std::endl;
    my_map.set_load_threshold(0.75);
    std::cout << "New load threshold: " << my_map.load_threshold() << std::endl;

    // Test data addition
    std::mt19937 gen(42);
    std::uniform_int_distribution<int> dist(1,10000000);
    std::size_t idx = 0;
    std::size_t indices[28]{};

    for (std::size_t i = 0; i < 28; ++i) {
        idx = dist(gen);
        indices[i] = idx;
        my_map.add(idx, i);
    }

    my_map.print();
    std::cout << "Count after addition: " << my_map.count();
    std::cout <<  ", Load factor: " << my_map.load_factor() << std::endl;
    
    // Test retrieval
    bool found = false;
    std::cout << my_map.at(idx, found) << " " << found << std::endl;
    std::cout << my_map.at(idx-2, found) << " " << found << std::endl;

    // Test removal
    std::cout << "Removing indices: ";
    for (std::size_t i = 10; i < 19; ++i) {
        bool removed = my_map.remove(indices[i]);
        if (removed) std::cout << indices[i] << ", ";

    }
    std::cout << std::endl << "After removal: "; 
    my_map.print();

    std::cout << my_map.remove(dist(gen)) << std::endl;
    std::cout << "Size: " << my_map.count() << std::endl;

    // test adding with tombstones
    for (std::size_t i = 0; i < 28; ++i) {
        idx = dist(gen);
        indices[i] = idx;
        my_map.add(idx, i);
    }

    my_map.print();
    std::cout << "Increased size: " << my_map.count() << std::endl;

    my_map.clear();
    std::cout << "Final size: " << my_map.count() << std::endl;

    return 0;
}