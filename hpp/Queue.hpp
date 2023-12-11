// @file         - Queue.hpp
// @brief        - Defining a queue class
// @author       - Madhav Malhotra
// @date         - 2023-12-11
// @version      - 0.0.0
// =======================================================================================

#ifndef STACK_HPP
#define STACK_HPP
#include "./SinglyLinkedList.hpp"

template <typename T>
class Queue : public SLList<T> {
    public: 
        // inherit public members (constructor/destructor implicitly inherited)
        using SLList<T>::length;
        using SLList<T>::print;
        using SLList<T>::clear;
        using SLList<T>::head;

        // @brief           - adds a node to the back of the queue
        // @param val       - the value of the node to add
        // @note            - defined in hpp since short
        void enqueue(T val) {
            SLList<T>::push(val);
        }

        // @brief           - removes a node from the front of the queue
        // @note            - defined in hpp since short
        void dequeue() {
            SLList<T>::remove_by_index(0);
        }
};

#endif