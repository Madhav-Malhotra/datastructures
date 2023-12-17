// @file         - Stack.hpp
// @brief        - Defining a stack class
// @author       - Madhav Malhotra
// @date         - 2023-12-09
// @version      - 0.0.0
// =======================================================================================

#ifndef STACK_HPP
#define STACK_HPP
#include "../linkedlist/SinglyLinkedList.hpp"

template <typename T>
class Stack : public SLList<T> {
    public: 
        // inherit public members (constructor/destructor implicitly inherited)
        using SLList<T>::length;
        using SLList<T>::print;
        using SLList<T>::clear;
        using SLList<T>::head;

        // @brief           - adds a node to the top of the stack
        // @param val       - the value of the node to add
        // @note            - defined in hpp since short
        void push(T val) {
            SLList<T>::shift(val);
        }

        // @brief           - removes a node from the top of the stack
        // @note            - defined in hpp since short
        void pop() {
            SLList<T>::remove_by_index(0);
        }
};

#endif