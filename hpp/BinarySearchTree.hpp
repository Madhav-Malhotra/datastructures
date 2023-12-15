// @file         - BinarySearchTree.hpp
// @brief        - Defining a binary search tree using a node class
// @author       - Madhav Malhotra
// @date         - 2023-12-15
// @version      - 0.0.0
// =============================================================================

#ifndef BINARYSEARCHTREENODE_HPP
#define BINARYSEARCHTREENODE_HPP

#include <cstddef>
#include <stdexcept>
#include "./BinarySearchTreeNode.hpp"
#include "./DynamicArray.hpp"
#include "./Queue.hpp"

/* 
Declare class
*/

template <typename T>
class BinarySearchTree {
    private:
        BSTNode<T>* root_ = nullptr;
        std::size_t count_ = 0;

        // @brief           - adds node
        // @param val       - value of node to add
        // @param root      - value of node to add
        void pushRecursive(T val, BSTNode<T>* root);
        
        // @brief           - finds min value in subtree
        // @param root      - pointer to root of subtree
        // @return          - pointer to min value node in subtree
        BSTNode<T>* min(BSTNode<T>* root);

        // @brief           - Shows the nodes of the binary tree
        // @param prefix    - levels/sublevels on each line
        // @param idx       - index of current node
        // @param isleft    - left or right node
        // @author          - Vasili Novikov, translated by Adrian Schneider
        // @source          - https://stackoverflow.com/a/51730733
        void printBT(const std::string& prefix, BSTNode<T>* root, bool isLeft);

    public:
        // @brief           - nicely prints the nodes of the tree
        void print();

        // @brief           - returns number of nodes in tree
        std::size_t count() {
            return count_;
        }

        BSTNode<T>* root() {
            return root_;
        }

        // @brief           - removes node at specified memory address
        // @param node      - pointer to node
        void remove(BSTNode<T>* node);

        // @brief           - adds node
        // @param val       - value of node to add
        void push(T val);
        
        // @brief           - removes root node
        // @return          - value at root node
        void poll();

        // @brief           - deletes all data
        void clear();

        // @brief           - removes first node with specified value
        // @param val       - val of node to remove
        // @param all       - whether to remove multiple reoccurrences
        // @return          - true if value removed, else false
        bool remove_by_value(T val, bool all = false) {
            // prep data for breadthwise search
            DynamicArray<BSTNode<T>*> to_remove{};
            Queue<BSTNode<T>*> to_check{};
            to_check.enqueue(this->root_);

            // see unchecked els while (el not yet deleted in single del mode)
            while ((to_remove.length() != 1 || all) && to_check.length()) {
                // check parent
                BSTNode<T>* p = to_check.dequeue();
                if (p->getData() == val) {
                    to_remove.push(p);
                }
                
                // update queue
                BSTNode<T>* l = p->getLeft();
                BSTNode<T>* r = r->getRight();
                if (l) to_check.enqueue(l);
                if (r) to_check.enqueue(r);
            }

            // remove els
            for (std::size_t i = 0; i < to_remove.length(); ++i) {
                this->remove(to_remove.at(i));
            }
            return bool(to_remove.length());
        }
};


/* 
Define class - in hpp file due to template issues
*/

// @brief           - finds min value in subtree
// @param root      - pointer to root of subtree
// @return          - pointer to min value node in subtree
template <typename T>
BSTNode<T>* BinarySearchTree<T>::min(BSTNode<T>* root) {
    BSTNode<T>* l = root->getLeft();
    return (l) ? this->min(l) : root;
}

// @brief           - adds node
// @param val       - value of node to add
// @param root      - node position being considered
template <typename T>
void BinarySearchTree<T>::pushRecursive(T val, BSTNode<T>* root) {
    // handle empty tree
    if (root == nullptr) {
        this->root_ = new BSTNode<T>{};
        this->root_->setData(val);
    }

    T data = root->getData();
    BSTNode<T>* l = root->getLeft();
    BSTNode<T>* r = root->getRight();
    
    if (val <= data) {
        if (l) this->pushRecursive(val, l);
        else {
            BSTNode<T>* node = new BSTNode<T>{};
            node->setData(val);
            root->setLeft(node);
            node->setParent(root);
        }
    } else {
        if (r) this->pushRecursive(val, r);
        else {
            BSTNode<T>* node = new BSTNode<T>{};
            node->setData(val);
            root->setRight(node);
            node->setParent(root);
        }
    }
}

// @brief          - adds node
// @param val      - value of new node
template <typename T>
void BinarySearchTree<T>::push(T val) { 
    this->pushRecursive(val, this->root_);
    ++this->count_;
}

// @brief           - removes node at specified memory address
// @param node      - pointer to specified node
template <typename T>
void BinarySearchTree<T>::remove(BSTNode<T>* node) {
    BSTNode<T>* l = node->getLeft();
    BSTNode<T>* r = node->getRight();
    BSTNode<T>* p = node->getParent();
    
    // leaf node
    if (!(l || r)) {
        // check for parent to avoid bugs from singleton tree
        if (p) {
            (p->getLeft() == node) ? p->setLeft(nullptr) : p->setRight(nullptr);
        }
        delete node;
    }
    // both subtrees
    else if (l && r) {
        // remove min node in right subtree (NOT always a leaf)
        BSTNode<T>* min = this->min(r);
        node->setData(min->getData());
        this->remove(min);
        min = nullptr;
    }
    // single subtree
    else {
        if (p) {
            if (p->getLeft() == node) {
                p->setLeft((l) ? l : r);
            } else {
                p->setRight((l) ? l : r);
            }
        }
        delete node;
    }

    // cleanup
    node = p = l = r = nullptr;
    --this->count_;
}

// @brief           - removes root node
// @return          - value at root node
template <typename T>
void BinarySearchTree<T>::poll() {
    this->remove(this->root_);
}

// @brief           - clears all nodes
template <typename T>
void BinarySearchTree<T>::clear() {
    Queue<BSTNode<T>*> to_clear{};
    to_clear.enqueue(this->root_);

    while (to_clear.length()) {
        BSTNode<T>* p = to_clear.dequeue();
        BSTNode<T>* l = p->getLeft();
        BSTNode<T>* r = p->getRight();

        if (l) to_clear.enqueue(l);
        if (r) to_clear.enqueue(r);
        delete p;
        p = nullptr;
    }

    this->count_ = 0;
    this->root_ = nullptr;
}


/* 
Pretty print utility - https://stackoverflow.com/a/51730733
*/

// @brief           - Shows the nodes of the binary tree
// @param prefix    - levels/sublevels on each line
// @param idx       - index of current node
// @param isleft    - left or right node
// @author          - Vasili Novikov, translated by Adrian Schneider
// @source          - https://stackoverflow.com/a/51730733
template <typename T>
void BinarySearchTree<T>::printBT(const std::string& prefix, BSTNode<T>* root, bool isLeft) {
    if (root) {
        // print current line
        std::cout << prefix;
        std::cout << (isLeft ? "├──" : "└──" );
        std::cout << root->getData() << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), root->getLeft(), true);
        printBT( prefix + (isLeft ? "│   " : "    "), root->getRight(), false);
    }
}

// @brief           - Shows the nodes of the binary tree
template <typename T>
void BinarySearchTree<T>::print() {
    this->printBT("", this->root_, false);
}

#endif