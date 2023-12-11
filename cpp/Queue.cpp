// @file         - Queue.cpp
// @brief        - Testing a queue class
// @author       - Madhav Malhotra
// @date         - 2023-12-10
// @version      - 0.0.0
// =======================================================================================

#include <iostream>
#include "../hpp/Queue.hpp"

int main() {
    Queue<int> queue_test{};
    std::cout << "Initialised, length: " << queue_test.length() << std::endl;

    queue_test.enqueue(1);
    queue_test.print();
    queue_test.enqueue(2);
    queue_test.print();
    queue_test.enqueue(3);
    queue_test.print();

    std::cout << "Head: " << queue_test.head() << std::endl;
    queue_test.dequeue();
    std::cout << "Dequeued: ";
    queue_test.print();
    std::cout << "Head: " << queue_test.head() << std::endl;

    std::cout << "Clearing remaining " << queue_test.length() << " nodes." << std::endl;
    queue_test.clear();
}