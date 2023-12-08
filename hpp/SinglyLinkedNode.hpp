// @file         - SLNode.hpp
// @brief        - Declaring a singly linked node class for a singly linked list.
// @author       - Madhav Malhotra
// @date         - 2023-12-08
// @version      - 0.0.0
// =======================================================================================

#ifndef SLNode_HPP
#define SLNode_HPP

/*
Declare Node class members
*/

template <typename T>
class SLNode {
    private:
        T data_{};
        SLNode<T>* next_{};
    
    public:
        void setData(T data);
        SLNode<T>* setNext(SLNode<T>* next);
        T getData();
        SLNode<T>* getNext();

        // Cannot define externally while keeping default template type
        SLNode(T data = T{}) {
            this->data_ = data;
            this->next_ = nullptr;
        }
};


/* 
Define Node class members
*/

// @brief            - updates node value
// @param T data    - new value
template <typename T>
void SLNode<T>::setData(T data) {
    this->data_ = data;
}

// @brief            - updates next node
// @param next      - new next node
// @return          - previous pointer to next node, for memory management
template <typename T>
SLNode<T>* SLNode<T>::setNext(SLNode<T>* next) {
    SLNode<T>* prev = this->next_;
    this->next_ = next;
    return prev; // CLASS USERS HANDLE MEMORY DEALLOCATION
}

// @brief            - get node data
template <typename T>
T SLNode<T>::getData() {
    return this->data_;
}

// @brief            - get node pointer
template <typename T>
SLNode<T>* SLNode<T>::getNext() {
    return this->next_;
}

#endif