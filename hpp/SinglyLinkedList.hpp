// @file         - SLList.hpp
// @brief        - Defining a singly linked list class
// @author       - Madhav Malhotra
// @date         - 2023-12-08
// @version      - 0.0.0
// =======================================================================================

#ifndef SLList_HPP
#define SLList_HPP
#include "SinglyLinkedNode.hpp"

// Declare class members
template <typename T>
class SLList {
    private:
        SLNode<T>* head_;
        SLNode<T>* tail_;
        std::size_t size_;
    
    public:
        // @brief           - constructor
        SLList();

        // @brief           - shows list length
        // @return          - number of nodes
        std::size_t length();

        // @brief           - returns first node
        SLNode<T>* head();

        // @brief           - returns last node
        SLNode<T>* tail();


        // @brief           - adds node to end of list
        // @param node      - node to add
        void push(SLNode<T>* node);

        // @brief           - returns node at some index
        // @param idx       - 0 <= idx < size_
        // @return          - node at input index
        SLNode<T>* at(std::size_t idx);

        // @brief           - removes node from list
        // @param node      - node to remove
        // @return          - memory address of node removed, for memory management
        SLNode<T>* remove(SLNode<T>* node);

        // @brief           - removes node from list by index
        // @param idx       - index to remove, 0 <= idx < size_
        // @return          - memory address of node removed, for memory management
        SLNode<T>* remove_by_index(std::size_t idx);

        // @brief           - helper wrapper on top of remove_by_index
        // @return          - memory address of node removed, for memory management
        SLNode<T>* pop();

        // @brief           - clears all nodes in linked list
        // @return          - vector of all nodes removed, for memory management.
        std::vector<SLNode<T>*> clear();
}; 

#endif