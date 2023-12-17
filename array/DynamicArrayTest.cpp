// @file         - DynamicArray.cpp
// @brief        - Testing a dynamic array class
// @author       - Madhav Malhotra
// @date         - 2023-12-11
// @version      - 2.0.0
// @since 1.0.0  - Moved definitions back to header due to template class issues
// @since 0.0.0  - Split code into header and cpp for reusability
// =======================================================================================

#include <iostream>
#include <stdexcept>
#include "./DynamicArray.hpp"

int main() {
    DynamicArray<int> a_test;

    // Getter methods
    std::cout << "Initialised elements: " + std::to_string(a_test.length()) << std::endl;
    std::cout << "Reserved blocks: " + std::to_string(a_test.capacity()) << std::endl;

    // add elements
    for (std::size_t i = 1; i < 25; ++i) {
        a_test.push(i);
    }
    std::cout << "Size after pushes: " + std::to_string(a_test.length()) << std::endl;

    std::cout << "Insert elements to start: ";
    a_test.insert(100, 0);
    std::cout << a_test.length() << ", ";
    a_test.insert(100, 1);
    std::cout << a_test.length() << std::endl;

    // index
    a_test.at(0) = 15;
    std::cout << "Edit by index: " + std::to_string(a_test.at(0)) << std::endl;

    // pop
    std::cout << "Popped: " + std::to_string(a_test.pop()); 
    std::cout << ". Size: " + std::to_string(a_test.length()) << std::endl;

    // clear
    a_test.clear();
    std::cout << "Cleared: " + std::to_string(a_test.length()) << std::endl;

    return 0;
}