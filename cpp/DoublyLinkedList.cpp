// @file         - DLList.cpp
// @brief        - Defining a doubly linked list class
// @author       - Madhav Malhotra
// @date         - 2023-12-08
// @version      - 2.0.0
// @since 1.0.0  - Handled memory management internally
// @since 0.0.0  - Split code into header and cpp for reusability
// =======================================================================================

#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "../hpp/DoublyLinkedNode.hpp"
#include "../hpp/DoublyLinkedList.hpp"

/* 
Define Doubly Linked List
*/

// @brief             - constructor
template <typename T>
DLList<T>::DLList() {
    this->head_ = nullptr;
    this->tail_ = nullptr;
    this->size_ = 0;
}

// @brief             - prints array values to std::cout
template <typename T>
void DLList<T>::print() {
    DLNode<T>* curr = this->head_;
    for (std::size_t i = 0; i < this->size_; ++i) {
        std::cout << curr->getData() << " ";
        curr = curr->getNext();
    }

    std::cout << std::endl;
}

// @brief            - returns number of nodes
template <typename T>
std::size_t DLList<T>::length() {
    return this->size_;
}

// @brief            - returns address to first node
template <typename T>
DLNode<T>* DLList<T>::head() {
    return this->head_;
}

// @brief            - returns address to last node
template <typename T>
DLNode <T>* DLList<T>::tail() {
    return this->tail_;
} 

// @brief            - adds node to end of list
// @param val        - data in node to add
template <typename T>
void DLList<T>::push(T val) {
    DLNode<T>* node = new DLNode<T>(val);

    // Only init head if list is empty
    if (this->head_ == nullptr) {
        this->head_ = node;
    } else {
        this->tail_->setNext(node);
        node->setLast(this->tail_);
    }

    this->tail_ = node;
    ++this->size_;
}

// @brief           - inserts element at start of list
// @param val       - value of new node
template <typename T>
void DLList<T>::shift(T val) {
    DLNode<T>* node = new DLNode<T>(val);

    // Only init tail if list is empty
    if (this->size_ == 0) {
        this->tail_ = node;
    } else {
        this->head_->setLast(node);
        node->setNext(this->head_);
    }

    this->head_ = node;
    ++this->size_;
}

// @brief           - removes node from list
// @param val       - node value to remove
// @param all       - whether to remove multiple value occurrences, default false.
// @return          - true if value(s) removed, else false
// @note            - defined in hpp to support default argument
/* 
Intentionally blank
*/


// @brief           - removes node from list by index
// @param idx      - index to remove, 0 <= idx < size_
template <typename T>
void DLList<T>::remove_by_index(std::size_t idx) {
    // also captures null list condition
    if (idx >= this->size_) {
        throw std::invalid_argument("Index beyond array length");
    }

    // pointers to track to avoid bugs
    DLNode<T>* curr = this->head_->getNext();
    DLNode<T>* removed = nullptr;

    // special case, remove head, no prev
    if (idx == 0) {
        removed = this->head_;
        this->head_ = this->head_->getNext();
        this->head_->setLast(nullptr);
    } 
    // special case, remove tail, no next
    else if (idx == this->size_ - 1) {
        removed = this->tail_;
        this->tail_ = removed->getLast();
        this->tail_->setNext(nullptr);
    } else {
        // skip to node to remove
        for (std::size_t i = 1; i < idx; ++i) {
            curr = curr->getNext();
        }

        removed = curr;
        curr->getLast()->setNext(curr->getNext());
        curr->getNext()->setLast(curr->getLast());
    }

    // Clean up
    --this->size_;
    delete removed;
    removed = nullptr;
    curr = nullptr;
}

// @brief            - helper wrapper on top of remove_by_index
template <typename T>
void DLList<T>::pop() {
    if (this->size_ == 0) {
        throw std::range_error("Cannot pop from empty list");
    }
    this->remove_by_index(this->size_ - 1);
}

// @brief            - returns node at specified index
template <typename T>
DLNode<T>* DLList<T>::at(std::size_t idx) {
    if (idx >= this->size_) {
        throw std::invalid_argument("Index beyond array length");
    }

    DLNode<T>* curr = this->head_;
    for (std::size_t i = 0; i < idx; ++i) {
        curr = curr->getNext();
    }

    return curr;
}

// @brief            - clears all nodes in linked list
template <typename T>
void DLList<T>::clear() {
    DLNode<T>* curr = this->head_;
    DLNode<T>* removing = nullptr;

    for (std::size_t i = 0; i < this->size_; ++i) {
        removing = curr;
        curr = curr->getNext();
        delete removing;
    }

    curr = nullptr;
    removing = nullptr;

    // reset state
    this->head_ = nullptr;
    this->tail_ = nullptr;
    this->size_ = 0;
}


int main() {
    // Initialise linked list
    DLList<char> dll_test{};
    std::cout << "Initial size: " << dll_test.length() << std::endl;
    
    dll_test.push('a');
    dll_test.print();
    dll_test.push('b');
    dll_test.print();
    dll_test.shift('c');
    dll_test.print();

    dll_test.push('c');
    dll_test.push('c');
    dll_test.push('d');
    dll_test.push('e');
    dll_test.push('f');
    std::cout << "Updated size: " << dll_test.length() << std::endl;

    // Test removal functions 

    std::cout << "Successful remove by value: " << dll_test.remove('a'); 
    std::cout << ". Updated size: " << dll_test.length() << std::endl;

    std::cout << "Cannot find value to remove: " << dll_test.remove('g') << std::endl;

    std::cout << "Successful remove multiple by value: " << dll_test.remove('c', true); 
    std::cout << ". Updated size: " << dll_test.length() << std::endl;

    std::cout << "Successful remove by index.";
    dll_test.remove_by_index(3); 
    std::cout << " Updated size: " << dll_test.length() << std::endl;

    std::cout << "Will remove tail: " << dll_test.at(dll_test.length() - 1);
    dll_test.pop();
    std::cout << ". Updated size: " << dll_test.length() << std::endl;

    std::cout << "Cleared remaining " << dll_test.length() << " nodes." << std::endl;
    dll_test.clear();
}