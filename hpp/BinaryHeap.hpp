// @file         - BinaryHeap.hpp
// @brief        - Defining a binary heap using a binary tree
// @author       - Madhav Malhotra
// @date         - 2023-12-12
// @version      - 0.0.0
// =============================================================================

#ifndef BINARYHEAP_HPP
#define BINARYHEAP_HPP

#include <cstddef>
#include <stdexcept>
#include "./BinaryTree.hpp"

/* 
Declare class
*/

template <typename T>
class BinaryHeap : public BinaryTree<T> {
    private:
        bool max_heap_ = true;

        // @brief           - moves child element up a binary tree
        // @param c_val     - child element value
        // @param c_idx     - child element index
        // @return          - index of added element
        std::size_t bubble_up(T c_val, std::size_t c_idx);

        // @brief           - moves parent element down a binary tree
        // @param p_val     - parent element value
        // @param p_idx     - parent element index
        // @return          - index of added element
        std::size_t bubble_down(T p_val, std::size_t p_idx);


    public:
        // @brief           - adds element and sorts to appropriate position
        // @param val       - element value
        // @return          - index of added element
        std::size_t push(T val);

        // @brief           - removes node at specified index
        // @param idx       - index of node to remove
        // @return          - value at removed node
        T remove_by_index(std::size_t idx);

        // @brief           - sets tree sorting order to min heap
        void set_min_heap() {
            this->max_heap_ = false;
        }

        // @brief           - sets tree sorting order to max heap
        void set_max_heap() {
            this->max_heap_ = true;
        }
};


/* 
Define class - in hpp file due to template issues
*/

// @brief           - moves child element up a binary tree
// @param c_val     - child element value
// @param c_idx     - child element index
// @return          - final index of sorted child
template <typename T>
std::size_t BinaryHeap<T>::bubble_up(T c_val, std::size_t c_idx) {
    int p_idx = this->parent(c_idx);
    // prevent errors from root 
    if (p_idx == -1) {
        return c_idx;
    }

    T p = this->at(p_idx);

    // bubble up
    while ( (this->max_heap_ && p<c_val) || (!this->max_heap_ && p>c_val) ) {
        // update vals
        this->at(c_idx) = this->at(p_idx);
        this->at(p_idx) = c_val;
        
        // update indices
        c_idx = p_idx;
        p_idx = this->parent(c_idx);
        
        // prevent errors from root 
        if (p_idx == -1) {
            break;
        }
        p = this->at(p_idx);
    }

    return c_idx;
}

// @brief           - moves parent element down a binary tree
// @param p_val     - parent element value
// @param p_idx     - parent element index
// @return          - final index of sorted parent
template <typename T>
std::size_t BinaryHeap<T>::bubble_down(T p_val, std::size_t p_idx) {
    // Prep data
    int l_idx = this->left(p_idx);
    int r_idx = this->right(p_idx);

    // Prevent leaf node errors
    if (l_idx == -1 && r_idx == -1) return p_idx;

    // bubble down, put break conditions within loop since numerous
    while (true) {
        int sel_idx = l_idx; // implicitly handles no right child

        // no left child so default to right
        if (l_idx == -1) {      
            sel_idx = r_idx;
        } 
        // need to compare both children
        else if (l_idx > -1 && r_idx > -1) {
            // for max heap, sel = max(left, right)
            if (this->max_heap_ && this->at(r_idx) > this->at(l_idx)) {
                sel_idx = r_idx;
            }
            // for min heap, sel = min(left,right)
            else if (!this->max_heap_ && this->at(r_idx) < this->at(l_idx)) {
                sel_idx = r_idx;
            }
        }
        
        if (
            // stop if max and parent > child
            (this->max_heap_ && p_val > this->at(sel_idx)) ||
            // or min and parent < child
            (!this->max_heap_ && p_val < this->at(sel_idx)) 
        ) break;

        // update vals
        this->at(p_idx) = this->at(sel_idx);
        this->at(sel_idx) = p_val;
        p_idx = sel_idx;
        
        // update indices
        l_idx = this->left(p_idx);
        r_idx = this->right(p_idx);
        
        // Prevent leaf node errors
        if (l_idx == -1 && r_idx == -1) break;
    }

    return p_idx;
}

// @brief           - adds element and sorts to appropriate position
// @param val       - element value
// @return          - index of added element
template <typename T>
std::size_t BinaryHeap<T>::push(T val) {
    BinaryTree<T>::push(val);
    std::size_t c_idx = this->count() - 1;
    return this->bubble_up(val, c_idx);
}

// @brief           - removes node at specified index.
// @param idx       - index of node to remove
// @return          - value at removed node
template <typename T>
T BinaryHeap<T>::remove_by_index(std::size_t idx) {
    if (idx >= this->count()) {
        throw std::range_error("Input index out of range");
    }

    T val = this->at(idx);
    this->at(idx) = this->at(this->count() - 1);
    this->pop();
    
    // bubbling, if els left to bubble
    if (idx < this->count()) {
        this->bubble_up(this->at(idx), idx);
        this->bubble_down(this->at(idx), idx);
    }

    return val;
}

#endif