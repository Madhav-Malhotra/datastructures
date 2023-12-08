// @file         - DLNode.hpp
// @brief        - Declaring a doubly linked node class for a doubly linked list
// @author       - Madhav Malhotra
// @date         - 2023-12-08
// @version      - 0.0.0
// =======================================================================================


#ifndef DLNode_HPP
#define DLNode_HPP

/*
Declare Node class members
*/

template <typename T>
class DLNode {
    private:
        T data_;
        DLNode<T>* next_;
        DLNode<T>* last_;
    
    public:
        void setData(T data);
        DLNode<T>* setNext(DLNode<T>* next);
        DLNode<T>* setLast(DLNode<T>* last);

        T getData();
        DLNode<T>* getNext();
        DLNode<T>* getLast();

        // Cannot define externally while keeping default template type
        DLNode(T data = T{}) {
            this->data_ = data;
            this->next_ = nullptr;
            this->last_ = nullptr;
        }
};


/* 
Define Node class members
*/

// @brief            - updates node value
// @param T data    - new value
template <typename T>
void DLNode<T>::setData(T data) {
    this->data_ = data;
}

// @brief            - updates next node
// @param next      - new next node
// @return          - old pointer to next node, for memory management
template <typename T>
DLNode<T>* DLNode<T>::setNext(DLNode<T>* next) {
    DLNode<T>* prev = this->next_;
    this->next_ = next;
    return prev; // CLASS USERS HANDLE MEMORY DEALLOCATION
}

// @brief            - updates last node
// @param last      - new last node
// @return          - old pointer to last node, for memory management
template <typename T>
DLNode<T>* DLNode<T>::setLast(DLNode<T>* last) {
    DLNode<T>* prev = this->last_;
    this->last_ = last;
    return prev; // CLASS USERS HANDLE MEMORY DEALLOCATION
}

// @brief            - get node data
template <typename T>
T DLNode<T>::getData() {
    return this->data_;
}

// @brief            - get next node pointer
template <typename T>
DLNode<T>* DLNode<T>::getNext() {
    return this->next_;
}

// @brief            - get last node pointer
template <typename T>
DLNode<T>* DLNode<T>::getLast() {
    return this->last_;
}

#endif