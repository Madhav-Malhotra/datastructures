// @file         - SLList.hpp
// @brief        - Defining a singly linked list class
// @author       - Madhav Malhotra
// @date         - 2023-12-08
// @version      - 2.0.0
// @since 1.1.0  - Shifted class definitions to hpp due to template class problems
// @since 1.0.0  - Added shift/print functions
// @since 0.0.0  - Added internal controls for memory allocation
// =======================================================================================

#ifndef SLList_HPP
#define SLList_HPP
#include "SinglyLinkedNode.hpp"

/* 
Declare class members
*/

template <typename T>
class SLList {
    private:
        SLNode<T>* head_{};
        SLNode<T>* tail_{};
        std::size_t size_{};
    
    public:
        // @brief           - constructor
        SLList();

        // @brief           - destructor
        ~SLList();

        // @brief           - prints nodes to cout
        void print();

        // @brief           - shows list length
        // @return          - number of nodes
        std::size_t length();

        // @brief           - returns first node
        SLNode<T>* head();

        // @brief           - returns last node
        SLNode<T>* tail();


        // @brief           - adds node to end of list
        // @param val       - value of new node
        virtual void push(T val);

        // @brief           - adds node to start of list
        // @param val       - value of new node
        virtual void shift(T val);

        // @brief           - returns node at some index
        // @param idx       - 0 <= idx < size_
        // @return          - node at input index
        SLNode<T>* at(std::size_t idx);

        // @brief           - removes node from list by index
        // @param idx       - index to remove, 0 <= idx < size_
        void remove_by_index(std::size_t idx);

        // @brief           - helper wrapper on top of remove_by_index
        virtual void pop();

        // @brief           - clears all nodes in linked list
        void clear();

        // @brief           - removes node from list
        // @param val       - node value to remove
        // @param all       - whether to remove multiple value occurrences, default false.
        // @return          - true if value(s) removed, else false
        // @note            - defined within class to support default argument
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







/* 
Define Singly Linked List Class
*/

// @brief           - constructor
template <typename T>
SLList<T>::SLList() {
    this->head_ = nullptr;
    this->tail_ = nullptr;
    this->size_ = 0;
}

// @brief           - destructor
template <typename T>
SLList<T>::~SLList() {
    SLList<T>::clear();
}


// @brief            - returns number of nodes
template <typename T>
std::size_t SLList<T>::length() {
    return this->size_;
}

// @brief            - returns first node
template <typename T>
SLNode<T>* SLList<T>::head() {
    return this->head_;
}

// @brief            - returns last node
template <typename T>
SLNode<T>* SLList<T>::tail() {
    return this->tail_;
} 

// @brief            - prints nodes to cout
template <typename T>
void SLList<T>::print() {
    SLNode<T>* curr = this->head_;
    for (std::size_t i = 0; i < this->size_; ++i) {
        std::cout << curr->getData() << " ";
        curr = curr->getNext();
    }

    std::cout << std::endl;
}



// @brief           - adds node to end of list
// @param val       - value of new node
template <typename T>
void SLList<T>::push(T val) {
    SLNode<T>* node = new SLNode<T>(val);

    // Only init head if list is empty
    if (this->head_ == nullptr) {
        this->head_ = node;
    } else {
        this->tail_->setNext(node);
    }

    this->tail_ = node;
    ++this->size_;
}

// @brief           - adds node to start of list
// @param val       - value of new node
template <typename T>
void SLList<T>::shift(T val) {
    SLNode<T>* node = new SLNode<T>(val);

    // Only init tail if list is empty
    if (this->head_ == nullptr) {
        this->tail_ = node;
    }
    
    node->setNext(this->head_);
    this->head_ = node;

    ++this->size_;
}

// @brief           - removes node from list
// @param val       - node value to remove
// @param all       - whether to remove multiple value occurrences, default false.
// @return          - true if value(s) removed, else false
// @note            - defined within class since default args not supported otherwise
/* 
Intentionally blank
*/


// @brief          - removes node from list by index
// @param idx      - index to remove, 0 <= idx < size_
template <typename T>
void SLList<T>::remove_by_index(std::size_t idx) {
    // implicitly handles empty list
    if (idx >= this->size_) {
        throw std::invalid_argument("Index beyond array length");
    }

    // three pointers to track to avoid bugs
    SLNode<T>* curr = this->head_->getNext();
    SLNode<T>* prev = this->head_;
    SLNode<T>* removed = nullptr;

    // skip to node to remove, if it's not the head 
    for (std::size_t i = 1; i < idx; ++i) {
        prev = curr;
        curr = curr->getNext();
    }

    // pointer manipulations
    if (idx == 0) {
        removed = this->head_;
        this->head_ = this->head_->getNext();
    } else {
        removed = curr;
        prev->setNext(curr->getNext());
    } 

    // avoid dangling tail pointer
    if (idx == this->size_ - 1) {
        this->tail_ = prev;
    }

    // Clean up
    --this->size_;
    delete removed;
    removed = nullptr;
    curr = nullptr;
    prev = nullptr;
}

// @brief            - returns node at specified index
template <typename T>
SLNode<T>* SLList<T>::at(std::size_t idx) {
    // implicitly handles empty list
    if (idx >= this->size_) {
        throw std::invalid_argument("Index beyond array length");
    }

    SLNode<T>* curr = this->head_;

    for (std::size_t i = 0; i < idx; ++i) {
        if (idx == i) {
            break;
        }
        curr = curr->getNext();
    }

    return curr;
}

// @brief            - helper wrapper on top of remove_by_index
template <typename T>
void SLList<T>::pop() {
    // explicitly handles empty list
    if (this->size_ == 0) {
        throw std::range_error("Cannot pop from empty list");
    }
    
    this->remove_by_index(this->size_ - 1); 
}

// @brief            - clears all nodes in linked list
template <typename T>
void SLList<T>::clear() {
    SLNode<T>* curr = this->head_;
    SLNode<T>* removing = nullptr;

    // deallaocation
    for (std::size_t i = 0; i < this->size_; ++i) {
        removing = curr;
        curr = curr->getNext();
        delete removing;
    }

    // cleanup
    curr = nullptr;
    removing = nullptr;

    this->head_ = nullptr;
    this->tail_ = nullptr;
    this->size_ = 0;
}

#endif