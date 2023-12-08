// @file         - DLList.hpp
// @brief        - Defining a doubly linked list class
// @author       - Madhav Malhotra
// @date         - 2023-12-08
// @version      - 0.0.0
// =======================================================================================

#ifndef DLList_HPP
#define DLList_HPP
#include "DoublyLinkedNode.hpp"

template <typename T>
class DLList {
    private:
        DLNode<T>* head_;
        DLNode<T>* tail_;
        std::size_t size_;
    
    public:
        // @brief           - constructor
        DLList();

        // @brief           - shows list length
        // @return          - number of nodes
        std::size_t length();

        // @brief           - returns first node
        DLNode<T>* head();

        // @brief           - returns last node
        DLNode <T>* tail();


        // @brief           - adds node to end of list
        // @param node      - node to add
        void push(DLNode<T>* node);

        // @brief           - removes node from list
        // @param node      - node to remove
        // @return          - memory address of node removed, for memory management
        DLNode<T>* remove(DLNode<T>* node);

        // @brief           - removes node from list by index
        // @param idx       - index to remove, 0 <= idx < size_
        // @return          - memory address of node removed, for memory management
        DLNode<T>* remove_by_index(std::size_t idx);

        // @brief           - helper wrapper on top of remove_by_index
        // @return          - memory address of node removed, for memory management
        DLNode<T>* pop();

        // @brief           - clears all nodes in linked list
        // @return          - vector of all nodes removed, for memory management.
        std::vector<DLNode<T>*> clear();

        // @brief           - returns node at some index
        // @param idx       - 0 <= idx < size_
        // @return          - node at input index
        DLNode<T>* at(std::size_t idx);
}; 

#endif