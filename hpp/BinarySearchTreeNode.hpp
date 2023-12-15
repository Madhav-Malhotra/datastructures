// @file         - BSTNode.hpp
// @brief        - Declaring a node class for a binary search tree
// @author       - Madhav Malhotra
// @date         - 2023-12-15
// @version      - 0.0.0
// =======================================================================================


#ifndef BSTNode_HPP
#define BSTNode_HPP

/*
Declare Node class members
*/

template <typename T>
class BSTNode {
    private:
        T data_{};
        BSTNode<T>* left_{};
        BSTNode<T>* right_{};
        BSTNode<T>* parent_{};
    
    public:
        void setData(T data);
        BSTNode<T>* setLeft(BSTNode<T>* left);
        BSTNode<T>* setRight(BSTNode<T>* right);
        BSTNode<T>* setParent(BSTNode<T>* parent);

        T getData();
        BSTNode<T>* getLeft();
        BSTNode<T>* getRight();
        BSTNode<T>* getParent();

        // Cannot define externally while keeping default template type
        BSTNode(T data = T{}) {
            this->data_ = data;
            this->left_ = nullptr;
            this->right_ = nullptr;
        }
};


/* 
Define Node class members
*/

// @brief           - updates node value
// @param T data    - new value
template <typename T>
void BSTNode<T>::setData(T data) {
    this->data_ = data;
}

// @brief           - updates left child node
// @param left      - new left child
// @return          - old pointer to left child, for memory management
template <typename T>
BSTNode<T>* BSTNode<T>::setLeft(BSTNode<T>* left) {
    BSTNode<T>* prev = this->left_;
    this->left_ = left;
    return prev; // CLASS USERS HANDLE MEMORY DEALLOCATION
}

// @brief           - updates right child node
// @param right     - new right child
// @return          - old pointer to right child, for memory management
template <typename T>
BSTNode<T>* BSTNode<T>::setRight(BSTNode<T>* right) {
    BSTNode<T>* prev = this->right_;
    this->right_ = right;
    return prev; // CLASS USERS HANDLE MEMORY DEALLOCATION
}

// @brief           - updates parent node
// @param right     - new parent
// @return          - old pointer to parent, for memory management
template <typename T>
BSTNode<T>* BSTNode<T>::setParent(BSTNode<T>* parent) {
    BSTNode<T>* prev = this->parent_;
    this->parent_ = parent;
    return prev; // CLASS USERS HANDLE MEMORY DEALLOCATION
}

// @brief            - get node data
template <typename T>
T BSTNode<T>::getData() {
    return this->data_;
}

// @brief            - get left node pointer
template <typename T>
BSTNode<T>* BSTNode<T>::getLeft() {
    return this->left_;
}

// @brief            - get right node pointer
template <typename T>
BSTNode<T>* BSTNode<T>::getRight() {
    return this->right_;
}

// @brief            - get right node pointer
template <typename T>
BSTNode<T>* BSTNode<T>::getParent() {
    return this->parent_;
}

#endif