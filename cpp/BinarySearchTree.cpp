// @file         - BinarySearchTree.cpp
// @brief        - Testing a binary tree class
// @author       - Madhav Malhotra
// @date         - 2023-12-15
// @version      - 0.0.0
// =============================================================================

#include <iostream>
#include "../hpp/BinarySearchTree.hpp"

int main() {
    BinarySearchTree<int> bt_test;

    // Add elements
    std::cout << "Initialised elements: " << bt_test.count() << std::endl;

    for (std::size_t i = 1; i < 25; ++i) {
        bt_test.push(i);
    }
    bt_test.push(25);
    std::cout << "Size after pushes: " << bt_test.count() << std::endl;
    bt_test.print();

    // Relation getters
    std::cout << "Root l child: " << bt_test.root()->getLeft()->getData() << std::endl;
    std::cout << "Root r child: " << bt_test.root()->getRight()->getData() << std::endl;

    // removal
    bt_test.poll();
    std::cout << "New root: " << bt_test.root()->getData() << std::endl;
    bt_test.print();

    std::cout << "Size before: " << bt_test.count() << std::endl;
    std::cout << "Removed node w/ val 17: " << bt_test.remove_by_value(17) << std::endl;
    bt_test.print();

    bt_test.remove_by_value(25, true);
    std::cout << "Size after: " << bt_test.count() << std::endl;
    bt_test.print();

    // clear
    bt_test.clear();
    std::cout << "Cleared: " << bt_test.count() << std::endl;

    return 0;
}