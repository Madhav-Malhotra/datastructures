// @file         - SLList.cpp
// @brief        - Defining a singly linked list class
// @author       - Madhav Malhotra
// @date         - 2023-12-08
// @version      - 3.0.0
// @since 2.0.0  - Moved definitions to hpp b/c of template class problems
// @since 1.0.0  - Started internally handling memory management
// @since 0.0.0  - Split code into header and cpp for reusability
// =======================================================================================


#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "./SinglyLinkedNode.hpp"
#include "./SinglyLinkedList.hpp"

/* 
Due to issues with template classes, member function
definitions have been moved to hpp/SinglyLinkedList.hpp
*/

int main() {
    // Initialise linked list
    SLList<char> sll_test{};
    std::cout << "Initial size: " << sll_test.length() << std::endl;

    sll_test.push('a');
    sll_test.print();
    sll_test.push('b');
    sll_test.print();
    sll_test.shift('c');
    sll_test.print();

    sll_test.push('c');
    sll_test.push('c');
    sll_test.push('d');
    sll_test.push('e');
    sll_test.push('f');

    std::cout << "Updated size: " << sll_test.length() << std::endl;

    // Test removal functions
    std::cout << "Successful remove by value: " << sll_test.remove('a'); 
    std::cout << ". Updated size: " << sll_test.length() << std::endl;

    std::cout << "Succesful remove multiple by value: " << sll_test.remove('c', true);
    std::cout << ". Updated size: " << sll_test.length() << std::endl;
 
    std::cout << "Cannot find value to remove: " << sll_test.remove('g') << std::endl;

    sll_test.remove_by_index(3);
    std::cout << "Successful remove by index. Updated size: " << sll_test.length() << std::endl;

    std::cout << "Will remove tail: " << sll_test.at(sll_test.length() - 1);
    sll_test.pop();
    std::cout << ". Updated size: " << sll_test.length() << std::endl;

    std::cout << "Cleared remaining " << sll_test.length() << " nodes." << std::endl;
    sll_test.clear();
}