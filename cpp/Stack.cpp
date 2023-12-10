// @file         - Stack.cpp
// @brief        - Testing a stack class
// @author       - Madhav Malhotra
// @date         - 2023-12-09
// @version      - 0.0.0
// =======================================================================================

#include <iostream>
#include "../hpp/Stack.hpp"

int main() {
    Stack<char> stack_test{};
    std::cout << "Initialised, length: " << stack_test.length() << std::endl;

    stack_test.push('a');
    stack_test.print();
    stack_test.push('b');
    stack_test.print();
    stack_test.push('c');
    stack_test.print();

    std::cout << "Head: " << stack_test.head() << std::endl;
    stack_test.pop();
    std::cout << "Popped: ";
    stack_test.print();
    std::cout << "Head: " << stack_test.head() << std::endl;

    std::cout << "Clearing remaining " << stack_test.length() << " nodes." << std::endl;
    stack_test.clear();
}