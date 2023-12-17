// @file         - BinarySearchTree.cpp
// @brief        - Testing a binary tree class
// @author       - Madhav Malhotra
// @date         - 2023-12-15
// @version      - 0.0.0
// =============================================================================

#include <iostream>
#include <random>
#include "./BinarySearchTree.hpp"

int main() {
    // Setup data
    BinarySearchTree<int> bt_test{};
    std::random_device rd{};
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> dist(1,100);

    // Add elements
    std::cout << "Initialised elements: " << bt_test.count() << std::endl;

    for (std::size_t i = 25; i > 0; --i) {
        bt_test.push(dist(gen));
    }
    bt_test.push(24);
    std::cout << "Size after pushes: " << bt_test.count() << std::endl;
    bt_test.print();

    // Relation getters
    std::cout << "Left " << bt_test.root()->getLeft() << " ";
    std::cout << "Right " << bt_test.root()->getRight() << std::endl;

    // removal
    bt_test.poll();
    std::cout << "New root: " << bt_test.root()->getData() << std::endl;
    bt_test.print();

    std::cout << "Size before: " << bt_test.count() << std::endl;
    std::cout << "Removed node w/ val 17: " << bt_test.remove_by_value(17) << std::endl;
    bt_test.print();

    bt_test.remove_by_value(24, true);
    std::cout << "Size after: " << bt_test.count() << std::endl;
    bt_test.print();

    // clear
    bt_test.clear();
    std::cout << "Cleared: " << bt_test.count() << std::endl;

    return 0;
}