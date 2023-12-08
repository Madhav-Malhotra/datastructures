// @file         - DLList.cpp
// @brief        - Defining a doubly linked list class
// @author       - Madhav Malhotra
// @date         - 2023-12-08
// @version      - 1.0.0
// @since 0.0.0  - Split code into header and cpp for reusability
// =======================================================================================

#include <vector>
#include <cstddef>
#include <iostream>
#include <stdexcept>
#include "../hpp/DoublyLinkedNode.hpp"
#include "../hpp/DoublyLinkedList.hpp"

/* 
Define Doubly Linked List
*/

template <typename T>
DLList<T>::DLList() {
    this->head_ = nullptr;
    this->tail_ = nullptr;
    this->size_ = 0;
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
// @param node      - node to add
template <typename T>
void DLList<T>::push(DLNode<T>* node) {
    if (node == nullptr) {
        throw std::invalid_argument("Cannot add a null node");
    }

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

// @brief           - removes node from list
// @param node     - node to remove
// @return         - memory address of node removed, for memory management
template <typename T>
DLNode<T>* DLList<T>::remove(DLNode<T>* node) {
    if (node == nullptr) {
        throw std::invalid_argument("Cannot remove null node");
    } else if (this->head_ == nullptr) {
        throw std::range_error("Cannot remove node from empty list");
    }

    // pointers to track to avoid bugs
    DLNode<T>* curr = this->head_->getNext();
    DLNode<T>* removed = nullptr;

    // special case: remove head, no prev
    if (this->head_ == node) {
        removed = this->head_;
        this->head_ = this->head_->getNext();
        this->head_->setLast(nullptr);
    } else {
        while (curr != nullptr) {
            if (curr == node) {
                removed = curr;
                // avoid dangling tail pointer
                if (curr == this->tail_) {
                    this->tail_ = curr->getLast();
                    this->tail_->setNext(nullptr);
                } else {
                    curr->getLast()->setNext(curr->getNext());
                    curr->getNext()->setLast(curr->getLast());
                }
                break;
            } else {
                curr = curr->getNext();
            }
        }
    }

    // Clean up before returning
    if (removed != nullptr) {
        --this->size_;
    }
    curr = nullptr;
    return removed;   // CLASS USERS HANDLE MEMORY DEALLOCATION
}

// @brief           - removes node from list by index
// @param idx      - index to remove, 0 <= idx < size_
// @return         - memory address of node removed, for memory management
template <typename T>
DLNode<T>* DLList<T>::remove_by_index(std::size_t idx) {
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
    } else {
        for (std::size_t i = 1; i <= idx; ++i) {
            // found the node to remove
            if (i == idx) {
                removed = curr;
                // avoid dangling tail pointer
                if (i == this->size_ - 1) {
                    this->tail_ = curr->getLast();
                    this->tail_->setNext(nullptr);
                } else {
                    curr->getLast()->setNext(curr->getNext());
                    curr->getNext()->setLast(curr->getLast());
                }
            } 
            // continue to next node
            else {
                curr = curr->getNext();
            }
        }
    }

    // Clean up before returning
    --this->size_;
    curr = nullptr;
    return removed;  // CLASS USERS HANDLE MEMORY DEALLOCATION
}

// @brief            - returns node at specified index
template <typename T>
DLNode<T>* DLList<T>::at(std::size_t idx) {
    if (idx >= this->size_) {
        throw std::invalid_argument("Index beyond array length");
    }

    DLNode<T>* curr = this->head_;

    for (std::size_t i = 0; i < idx; ++i) {
        if (idx == i) {
            break;
        }
        curr = curr->getNext();
    }

    return curr;
}

// @brief            - helper wrapper on top of remove_by_index
// @return          - memory address of node removed, for memory management
template <typename T>
DLNode<T>* DLList<T>::pop() {
    if (this->size_ == 0) {
        throw std::range_error("Cannot pop from empty list");
    }
    return this->remove_by_index(this->size_ - 1); // CLASS USER MUST DEALLOCATE
}

// @brief            - clears all nodes in linked list
// @return          - vector of all nodes removed, for memory management. 
template <typename T>
std::vector<DLNode<T>*> DLList<T>::clear() {
    std::vector<DLNode<T>*> v_nodes(this->size_, nullptr);
    DLNode<T>* curr = this->head_;

    for (std::size_t i = 0; i < this->size_; ++i) {
        v_nodes.push_back(curr);
        curr = curr->getNext();
    }

    this->head_ = nullptr;
    this->tail_ = nullptr;
    this->size_ = 0;

    return v_nodes;
}


int main() {
    // Initialise nodes
    DLNode<char> a = DLNode<char>('a');
    DLNode<char> b = DLNode<char>('b');
    DLNode<char> c = DLNode<char>('c');
    DLNode<char> d = DLNode<char>('d');
    DLNode<char> e = DLNode<char>('e');
    DLNode<char> f = DLNode<char>('f');
    DLNode<char>g{};

    a.setNext(&b); b.setLast(&a);
    b.setNext(&c); c.setLast(&b);
    c.setNext(&d); d.setLast(&c);
    d.setNext(&e); e.setLast(&d);
    e.setNext(&f); f.setLast(&e);

    std::cout << a.getData() << b.getData() << c.getData() << std::endl;
    std::cout << a.getNext() << b.getNext() << c.getNext() << std::endl;

    // Initialise linked list
    DLList<char> dll_test{};
    std::cout << "Initial size: " << dll_test.length() << std::endl;
    
    dll_test.push(&a);
    std::cout << "Head: " << dll_test.head() << ". Tail: " << dll_test.tail() << std::endl;
    dll_test.push(&b);
    std::cout << "Head: " << dll_test.head() << ". Tail: " << dll_test.tail() << std::endl;
    dll_test.push(&c);
    dll_test.push(&d);
    dll_test.push(&e);
    dll_test.push(&f);
    std::cout << "Updated size: " << dll_test.length() << std::endl;

    // Test removal functions
    std::cout << "Successful remove by pointer: " << dll_test.remove(&a); 
    std::cout << ". Updated size: " << dll_test.length() << std::endl;

    std::cout << "Cannot find pointer to remove: " << dll_test.remove(&g) << std::endl;
    std::cout << "Successful remove by index: " << dll_test.remove_by_index(3); 
    std::cout << ". Updated size: " << dll_test.length() << std::endl;

    std::cout << "Will remove tail: " << dll_test.at(dll_test.length() - 1);
    std::cout << ". Removed: " << dll_test.pop() << std::endl;

    std::cout << "Cleared remaining " << dll_test.length() << " nodes." << std::endl;
    dll_test.clear();
}