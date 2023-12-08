// @file         - SLList.cpp
// @brief        - Defining a singly linked list class
// @author       - Madhav Malhotra
// @date         - 2023-12-08
// @version      - 2.0.0
// @since 1.0.0  - Started internally handling memory management
// @since 0.0.0  - Split code into header and cpp for reusability
// =======================================================================================


#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "../hpp/SinglyLinkedNode.hpp"
#include "../hpp/SinglyLinkedList.hpp"


/* 
Define Singly Linked List Class
*/

template <typename T>
SLList<T>::SLList() {
    this->head_ = nullptr;
    this->tail_ = nullptr;
    this->size_ = 0;
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

// @brief           - removes node from list
// @param val       - node value to remove
// @param all       - whether to remove multiple value occurrences, default false.
// @return          - true if value(s) removed, else false
// @note            - defined in hpp since default args not supported otherwise
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

int main() {
    // Initialise linked list
    SLList<char> sll_test{};
    std::cout << "Initial size: " << sll_test.length() << std::endl;

    sll_test.push('a');
    std::cout << "Head: " << sll_test.head() << ". Tail: " << sll_test.tail() << std::endl;

    sll_test.push('b');
    std::cout << "Head: " << sll_test.head() << ". Tail: " << sll_test.tail() << std::endl;

    sll_test.push('c');
    sll_test.push('c');
    sll_test.push('c');
    sll_test.push('d');
    sll_test.push('e');
    sll_test.push('f');

    std::cout << "Updated size: " << sll_test.length() << std::endl;

    // Test removal functions
    std::cout << "Successful remove by value: " << sll_test.remove('a'); 
    std::cout << ". Updated size: " << sll_test.length() << std::endl;

    std::cout << "Succesful remove multiple by value: " << sll_test.remove('c', true);
    std::cout << ". Updated size: " << sll_test.length() << std::endl;
 
    std::cout << "Cannot find value to remove: " << sll_test.remove('g') << std::endl;

    sll_test.remove_by_index(3);
    std::cout << "Successful remove by index. Updated size: " << sll_test.length() << std::endl;

    std::cout << "Will remove tail: " << sll_test.at(sll_test.length() - 1);
    sll_test.pop();
    std::cout << ". Updated size: " << sll_test.length() << std::endl;

    std::cout << "Cleared remaining " << sll_test.length() << " nodes." << std::endl;
    sll_test.clear();
}