// @file         - BinaryTree.hpp
// @brief        - Defining a binary tree using a dynamic array
// @author       - Madhav Malhotra
// @date         - 2023-12-11
// @version      - 0.2.1
// @since 0.2.0  - Bug patch in .remove_by_value() with all = true.
// @since 0.1.0  - Made .remove_by_index() virtual for binary heap derived class
// @since 0.0.0  - Added pretty print utility
// =============================================================================

#ifndef BINARYTREEARRAY_HPP
#define BINARYTREEARRAY_HPP

#include <cstddef>
#include <stdexcept>
#include "./DynamicArray.hpp"

/* 
Declare class
*/

template <typename T>
class BinaryTree : public DynamicArray<T> {
    private:
        // @brief           - Shows the nodes of the binary tree
        // @param prefix    - levels/sublevels on each line
        // @param idx       - index of current node
        // @param isleft    - left or right node
        // @author          - Vasili Novikov, translated by Adrian Schneider
        // @source          - https://stackoverflow.com/a/51730733
        void printBT(const std::string& prefix, const std::size_t idx, bool isLeft);

    public:
        // @brief           - nicely prints the nodes of the tree
        void print();

        // @brief           - alias for dynamic array length
        // @return          - number of nodes in binary tree
        std::size_t count() {
            return DynamicArray<T>::length();
        }

        // @brief           - finds left child of input node
        // @param idx       - index of input node
        // @return          - index of left child if it exists, else -1
        int left(std::size_t idx);

        // @brief           - finds right child of input node
        // @param idx       - index of input node
        // @return          - index of right child if it exists, else -1
        int right(std::size_t idx);

        // @brief           - finds parent of input node
        // @param idx       - index of input node
        // @return          - index of parent child if it exists, else -1
        int parent(std::size_t idx);

        // @brief           - removes node at specified index. Replaces with last node.
        // @param idx       - index of node to remove
        // @return          - value at removed node
        // @note            - this is not binary search tree behaviour.
        virtual T remove_by_index(std::size_t idx);
        
        // @brief           - removes root node
        // @return          - value at root node
        T poll();

        // @brief           - removes first node with specified value
        // @param val       - val of node to remove
        // @param all       - whether to remove multiple reoccurrences
        // @return          - true if value removed, else false
        bool remove_by_value(T val, bool all = false) {
            std::size_t len = this->count();
            bool found = false;

            // stop loop upon el removal to avoid out of range
            for (std::size_t i = 0; i < len; ++i) {
                if (this->at(i) == val) {
                    this->remove_by_index(i);
                    found = true;
                    break;
                }
            }

            // only runs the function again if early stop above
            if (all && found) {
                // DO NOT SWITCH ORDER OF OR. COMPILER WILL OPTIMISE TO JUST
                // RETURN FOUND WITHOUT RECURSIVE CALL
                return this->remove_by_value(val, true) || found;
            } else {
                return found;
            }
        }
};


/* 
Define class - in hpp file due to template issues
*/

// @brief           - finds left child of input node
// @param idx       - index of input node
// @return          - index of left child if it exists, else -1
template <typename T>
int BinaryTree<T>::left(std::size_t idx) {
    std::size_t l_idx = 2*idx + 1;
    return (l_idx < this->count()) ? l_idx : -1;
};

// @brief           - finds right child of input node
// @param idx       - index of input node
// @return          - index of right child if it exists, else -1
template <typename T>
int BinaryTree<T>::right(std::size_t idx) {
    std::size_t r_idx = 2*idx + 2;
    return (r_idx < this->count()) ? r_idx : -1;
}

// @brief           - finds parent of input node
// @param idx       - index of input node
// @return          - index of parent if it exists, else -1
template <typename T>
int BinaryTree<T>::parent(std::size_t idx) {
    int p_idx = (idx % 2) ? (idx-1)/2 : (idx-2)/2;
    return (p_idx > -1 && idx > 0) ? p_idx : -1;
}

// @brief           - removes node at specified index. Replaces with last node.
// @param idx       - index of node to remove
// @return          - value at removed node
// @note            - this is not binary SEARCH tree behaviour.
template <typename T>
T BinaryTree<T>::remove_by_index(std::size_t idx) {
    if (idx >= this->count()) {
        throw std::out_of_range("Index must be less than list length");
    }

    T temp = T{this->at(idx)};
    this->at(idx) = this->at(this->count() - 1);
    this->pop();
    return temp;
}

// @brief           - removes root node
// @return          - value at root node
template <typename T>
T BinaryTree<T>::poll() {
    return this->remove_by_index(0);
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
void BinaryTree<T>::printBT(const std::string& prefix, const std::size_t idx, bool isLeft) {
    if ( idx < this->count() ) {
        // print current line
        std::cout << prefix;
        std::cout << (isLeft ? "├──" : "└──" );
        std::cout << this->at(idx) << std::endl;

        // enter the next tree level - left and right branch
        printBT( prefix + (isLeft ? "│   " : "    "), this->left(idx), true);
        printBT( prefix + (isLeft ? "│   " : "    "), this->right(idx), false);
    }
}

// @brief           - Shows the nodes of the binary tree
template <typename T>
void BinaryTree<T>::print() {
    this->printBT("", 0, false);
}

#endif