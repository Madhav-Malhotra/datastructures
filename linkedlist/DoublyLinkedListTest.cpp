// @file         - DLList.cpp
// @brief        - Testing a doubly linked list class
// @author       - Madhav Malhotra
// @date         - 2023-12-12
// @version      - 3.0.0
// @since 2.0.0  - Moved definitions to header for template class inheritance
// @since 1.0.0  - Handled memory management internally
// @since 0.0.0  - Split code into header and cpp for reusability
// =======================================================================================

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "./DoublyLinkedNode.hpp"
#include "./DoublyLinkedList.hpp"


int main() {
    // Initialise linked list
    DLList<char> dll_test{};
    std::cout << "Initial size: " << dll_test.length() << std::endl;
    
    dll_test.push('a');
    dll_test.print();
    dll_test.push('b');
    dll_test.print();
    dll_test.shift('c');
    dll_test.print();

    dll_test.push('c');
    dll_test.push('c');
    dll_test.push('d');
    dll_test.push('e');
    dll_test.push('f');
    std::cout << "Updated size: " << dll_test.length() << std::endl;

    // Test removal functions 

    std::cout << "Successful remove by value: " << dll_test.remove('a'); 
    std::cout << ". Updated size: " << dll_test.length() << std::endl;

    std::cout << "Cannot find value to remove: " << dll_test.remove('g') << std::endl;

    std::cout << "Successful remove multiple by value: " << dll_test.remove('c', true); 
    std::cout << ". Updated size: " << dll_test.length() << std::endl;

    std::cout << "Successful remove by index.";
    dll_test.remove_by_index(3); 
    std::cout << " Updated size: " << dll_test.length() << std::endl;

    std::cout << "Will remove tail: " << dll_test.at(dll_test.length() - 1);
    dll_test.pop();
    std::cout << ". Updated size: " << dll_test.length() << std::endl;

    std::cout << "Cleared remaining " << dll_test.length() << " nodes." << std::endl;
    dll_test.clear();
}