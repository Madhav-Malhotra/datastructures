// @file         - SLList.hpp
// @brief        - Defining a singly linked list class
// @author       - Madhav Malhotra
// @date         - 2023-12-08
// @version      - 1.0.0
// @since 0.0.0  - Added internal controls for memory allocation
// =======================================================================================

#ifndef SLList_HPP
#define SLList_HPP
#include "SinglyLinkedNode.hpp"

// Declare class members
template <typename T>
class SLList {
    private:
        SLNode<T>* head_{};
        SLNode<T>* tail_{};
        std::size_t size_{};
    
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
        // @param val       - value of new node
        void push(T val);

        // @brief           - returns node at some index
        // @param idx       - 0 <= idx < size_
        // @return          - node at input index
        SLNode<T>* at(std::size_t idx);

        // @brief           - removes node from list by index
        // @param idx       - index to remove, 0 <= idx < size_
        void remove_by_index(std::size_t idx);

        // @brief           - helper wrapper on top of remove_by_index
        void pop();

        // @brief           - clears all nodes in linked list
        void clear();

        // @brief           - removes node from list
        // @param val       - node value to remove
        // @param all       - whether to remove multiple value occurrences, default false.
        // @return          - true if value(s) removed, else false
        // @note            - defined in hpp to support default argument
        bool remove(T val, bool all = false) {
            if (this->head_ == nullptr) {
                throw std::range_error("Cannot remove node from empty list");
            }

            // special case: remove head
            bool removed = false;
            if (this->head_->getData() == val) {
                SLNode<T>* temp = this->head_;
                this->head_ = this->head_->getNext();
                
                delete temp;
                temp = nullptr;
                removed = true;
                --this->size_;
            }

            // normal case
            SLNode<T>* curr = this->head_->getNext();
            SLNode<T>* prev = this->head_;

            // stops if end of list OR removed an element in single removal mode.
            while ( !(curr == nullptr || (removed && !all)) ) {
                if (curr->getData() == val) {
                    prev->setNext(curr->getNext());
                    // avoid dangling tail pointer
                    if (curr == this->tail_) {
                        this->tail_ = prev;
                    }

                    // cleanup
                    delete curr;
                    curr = nullptr;
                    removed = true;
                    --this->size_;

                    // iterate
                    curr = prev->getNext();
                } else {
                    prev = curr;
                    curr = curr->getNext();
                }
            }

            // Clean up before returning
            curr = nullptr;
            prev = nullptr;
            return removed;
        }
}; 

#endif