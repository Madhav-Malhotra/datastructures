// @file         - DLList.hpp
// @brief        - Defining a doubly linked list class
// @author       - Madhav Malhotra
// @date         - 2023-12-08
// @version      - 1.0.0
// @since 0.0.0  - made memory management internal to class
// =======================================================================================

#ifndef DLList_HPP
#define DLList_HPP
#include "DoublyLinkedNode.hpp"

template <typename T>
class DLList {
    private:
        DLNode<T>* head_{};
        DLNode<T>* tail_{};
        std::size_t size_{};
    
    public:
        // @brief           - constructor
        DLList();

        // @brief           - prints array elements to std::cout
        void print();

        // @brief           - shows list length
        // @return          - number of nodes
        std::size_t length();

        // @brief           - returns first node
        DLNode<T>* head();

        // @brief           - returns last node
        DLNode <T>* tail();


        // @brief           - adds node to end of list
        // @param val       - data in node to add
        void push(T val);

        // @brief           - inserts node to start of list
        // @param val       - data in node to add
        void shift(T val);

        // @brief           - removes node from list by index
        // @param idx       - index to remove, 0 <= idx < size_
        void remove_by_index(std::size_t idx);

        // @brief           - helper wrapper on top of remove_by_index
        void pop();

        // @brief           - clears all nodes in linked list
        void clear();

        // @brief           - returns node at some index
        // @param idx       - 0 <= idx < size_
        // @return          - node at input index
        DLNode<T>* at(std::size_t idx);

        // @brief           - removes node from list
        // @param val       - node value to remove
        // @param all       - whether to remove multiple value occurrences, default false.
        // @return          - true if value(s) removed, else false
        // @note            - defined in hpp to support default argument
        bool remove(T val, bool all = false) {
            if (this->head_ == nullptr) {
                throw std::range_error("Cannot remove node from empty list");
            }

            // special case: single node list
            if (this->size_ == 1) {
                if (this->head_->getData() == val) {
                    this->clear();
                    return true;
                } else {
                    return false;
                }
            }

            // normal case
            bool removed = false;
            DLNode<T>* temp = nullptr;
            DLNode<T>* curr = this->head_;

            // stops if end of list OR removed an element in single removal mode.
            while ( !(curr == nullptr || (removed && !all)) ) {
                if (curr->getData() == val) {
                    // avoid dangling head pointer
                    if (curr == this->head_) {
                        this->head_ = this->head_->getNext();
                    } else {
                        curr->getLast()->setNext(curr->getNext());
                    }
                    
                    // avoid dangling tail pointer
                    if (curr == this->tail_) {
                        this->tail_ = curr->getLast();
                    } else {
                        curr->getNext()->setLast(curr->getLast());
                    }

                    // iterate
                    temp = curr;
                    curr = curr->getNext();

                    // cleanup
                    delete temp;
                    temp = nullptr;
                    removed = true;
                    --this->size_;
                } else {
                    curr = curr->getNext();
                }
            }

            // Clean up before returning
            curr = nullptr;
            temp = nullptr;
            return removed;
        }
}; 

#endif