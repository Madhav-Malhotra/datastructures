// @file         - SLList.cpp
// @brief        - Defining a singly linked list class
// @author       - Madhav Malhotra
// @date         - 2023-12-08
// @version      - 1.0.0
// @since 0.0.0  - Split code into header and cpp for reusability
// =======================================================================================


#include <vector>
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

// @brief            - adds node to end of list
// @param node      - node to add
template <typename T>
void SLList<T>::push(SLNode<T>* node) {
    if (node == nullptr) {
        throw std::invalid_argument("Cannot add a null node");
    }

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
// @param node     - node to remove
// @return         - memory address of node removed, for memory management
template <typename T>
SLNode<T>* SLList<T>::remove(SLNode<T>* node) {
    if (node == nullptr) {
        throw std::invalid_argument("Cannot remove null node");
    } else if (this->head_ == nullptr) {
        throw std::range_error("Cannot remove node from empty list");
    }

    // three pointers to track to avoid bugs
    SLNode<T>* curr = this->head_->getNext();
    SLNode<T>* prev = this->head_;
    SLNode<T>* removed = nullptr;

    // special case: remove head, no prev
    if (this->head_ == node) {
        removed = this->head_;
        this->head_ = this->head_->getNext();
    } else {
        while (curr != nullptr) {
            if (curr == node) {
                removed = curr;
                prev->setNext(curr->getNext());
                
                // avoid dangling tail pointer
                if (removed == this->tail_) {
                    this->tail_ = prev;
                }
                break;
            } else {
                prev = curr;
                curr = curr->getNext();
            }
        }
    }

    // Clean up before returning
    if (removed != nullptr) {
        --this->size_;
    }
    curr = nullptr;
    prev = nullptr;
    return removed;
}

// @brief           - removes node from list by index
// @param idx      - index to remove, 0 <= idx < size_
// @return         - memory address of node removed, for memory management
template <typename T>
SLNode<T>* SLList<T>::remove_by_index(std::size_t idx) {
    if (idx >= this->size_) {
        throw std::invalid_argument("Index beyond array length");
    }

    // three pointers to track to avoid bugs
    SLNode<T>* curr = this->head_->getNext();
    SLNode<T>* prev = this->head_;
    SLNode<T>* removed = nullptr;

    // special case, remove head, no prev
    if (idx == 0) {
        removed = this->head_;
        this->head_ = this->head_->getNext();
    } else {
        for (std::size_t i = 1; i <= idx; ++i) {
            // found the node to remove
            if (i == idx) {
                removed = curr;
                prev->setNext(curr->getNext()); 

                // avoid dangling tail pointer
                if (i == this->size_ - 1) {
                    this->tail_ = prev;
                }
            } 
            // continue to next node
            else {
                prev = curr;
                curr = curr->getNext();
            }
        }
    }

    // Clean up before returning
    --this->size_;
    curr = nullptr;
    prev = nullptr;
    return removed;
}

// @brief            - returns node at specified index
template <typename T>
SLNode<T>* SLList<T>::at(std::size_t idx) {
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
// @return          - memory address of node removed, for memory management
template <typename T>
SLNode<T>* SLList<T>::pop() {
    if (this->size_ == 0) {
        throw std::range_error("Cannot pop from empty list");
    }
    return this->remove_by_index(this->size_ - 1); // CLASS USER MUST DEALLOCATE
}

// @brief            - clears all nodes in linked list
// @return          - vector of all nodes removed, for memory management. 
template <typename T>
std::vector<SLNode<T>*> SLList<T>::clear() {
    std::vector<SLNode<T>*> v_nodes(this->size_, nullptr);
    SLNode<T>* curr = this->head_;

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
    SLNode<char> a = SLNode<char>('a');
    SLNode<char> b = SLNode<char>('b');
    SLNode<char> c = SLNode<char>('c');
    SLNode<char> d = SLNode<char>('d');
    SLNode<char> e = SLNode<char>('e');
    SLNode<char> f = SLNode<char>('f');
    SLNode<char>g{};

    a.setNext(&b);
    b.setNext(&c);
    c.setNext(&d);
    d.setNext(&e);
    e.setNext(&f);

    std::cout << a.getData() << b.getData() << c.getData() << std::endl;
    std::cout << a.getNext() << b.getNext() << c.getNext() << std::endl;

    // Initialise linked list
    SLList<char> sll_test{};
    std::cout << "Initial size: " << sll_test.length() << std::endl;
    
    sll_test.push(&a);
    std::cout << "Head: " << sll_test.head() << ". Tail: " << sll_test.tail() << std::endl;
    sll_test.push(&b);
    std::cout << "Head: " << sll_test.head() << ". Tail: " << sll_test.tail() << std::endl;
    sll_test.push(&c);
    sll_test.push(&d);
    sll_test.push(&e);
    sll_test.push(&f);
    std::cout << "Updated size: " << sll_test.length() << std::endl;

    // Test removal functions
    std::cout << "Successful remove by pointer: " << sll_test.remove(&a); 
    std::cout << ". Updated size: " << sll_test.length() << std::endl;

    std::cout << "Cannot find pointer to remove: " << sll_test.remove(&g) << std::endl;
    std::cout << "Successful remove by index: " << sll_test.remove_by_index(3); 
    std::cout << ". Updated size: " << sll_test.length() << std::endl;

    std::cout << "Will remove tail: " << sll_test.at(sll_test.length() - 1);
    std::cout << ". Removed: " << sll_test.pop() << std::endl;

    std::cout << "Cleared remaining " << sll_test.length() << " nodes." << std::endl;
    sll_test.clear();
}