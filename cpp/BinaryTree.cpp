// @file         - BinaryTree.cpp
// @brief        - Testing a binary tree class
// @author       - Madhav Malhotra
// @date         - 2023-12-11
// @version      - 0.0.0
// =======================================================================================

#include <iostream>
#include "../hpp/BinaryTree.hpp"

int main() {
    BinaryTree<int> bt_test;

    // Add elements
    std::cout << "Initialised elements: " << bt_test.length() << std::endl;

    for (std::size_t i = 1; i < 25; ++i) {
        bt_test.push(i);
    }
    bt_test.insert(25, 6);
    std::cout << "Size after pushes: " << bt_test.length() << std::endl;

    // Relation getters
    std::cout << "Root l child: " << bt_test.at(bt_test.left(0)) << std::endl;
    std::cout << "Root r child: " << bt_test.at(bt_test.right(0)) << std::endl;
    std::cout << "l child parent: " << bt_test.at(bt_test.parent(bt_test.right(0))) << std::endl;

    // removal
    bt_test.poll();
    std::cout << "New root: " << bt_test.at(0) << std::endl;
    bt_test.remove_by_index(10);
    std::cout << "New 11th el: " << bt_test.at(10) << std::endl;


    std::cout << "Size before: " << bt_test.count() << std::endl;
    std::cout << "Removed node w/ val 17: " << bt_test.remove_by_value(17) << std::endl;

    bt_test.remove_by_value(25, true);
    std::cout << "Size after: " << bt_test.count() << std::endl;

    // clear
    bt_test.clear();
    std::cout << "Cleared: " << bt_test.length() << std::endl;

    return 0;
}