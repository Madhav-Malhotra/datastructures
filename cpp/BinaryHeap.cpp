// @file         - BinaryHeap.cpp
// @brief        - Testing a binary heap class
// @author       - Madhav Malhotra
// @date         - 2023-12-13
// @version      - 0.0.0
// =============================================================================

#include <iostream>
#include "../hpp/BinaryHeap.hpp"

int main() {
    BinaryHeap<int> bt_test;
    bt_test.set_min_heap();

    // Add elements
    std::cout << "Initialised elements: " << bt_test.count() << std::endl;

    for (std::size_t i = 1; i < 25; ++i) {
        bt_test.push(i);
    }
    std::cout << "Size after pushes: " << bt_test.count() << std::endl;
    bt_test.print();

    // Relation getters
    std::cout << "Root l child: " << bt_test.at(bt_test.left(0)) << std::endl;
    std::cout << "Root r child: " << bt_test.at(bt_test.right(0)) << std::endl;
    std::cout << "l child parent: " << bt_test.at(bt_test.parent(bt_test.right(0))) << std::endl;

    // removal
    bt_test.poll();
    std::cout << "Final: " << std::endl;
    bt_test.print();
    std::cout << "New root: " << bt_test.at(0) << std::endl;
    std::cout << "Size after: " << bt_test.count() << std::endl;

    std::cout << "Old 12th el: " << bt_test.at(11) << std::endl;
    bt_test.remove_by_index(11);
    std::cout << "New 12th el: " << bt_test.at(11) << std::endl;
    bt_test.print();
    std::cout << "Size after: " << bt_test.count() << std::endl;


    std::cout << "Size before: " << bt_test.count() << std::endl;
    std::cout << "Removed node w/ val 17: " << bt_test.remove_by_value(17) << std::endl;
    bt_test.print();
    std::cout << "Size after: " << bt_test.count() << std::endl;


    std::cout << "Adding duplicate node 22" << std::endl;
    bt_test.push(22);
    std::cout << "Size after: " << bt_test.count() << std::endl;

    bt_test.print();
    std::cout << "Removing multiple nodes" << std::endl;
    bt_test.remove_by_value(22, true);
    bt_test.print();
    std::cout << "Size after: " << bt_test.count() << std::endl;

    // clear
    bt_test.clear();
    std::cout << "Cleared: " << bt_test.length() << std::endl;
    return 0;
}