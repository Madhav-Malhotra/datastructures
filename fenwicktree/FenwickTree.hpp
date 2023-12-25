// @file         FenwickTree.hpp
// @brief        Defining a fenwick tree using a static array
// @author       Madhav Malhotra
// @date         2023-12-23
// @version      0.0.0
// =============================================================================

#ifndef FENWICK_TREE_HPP
#define FENWICK_TREE_HPP

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <type_traits>

/* 
Declare class
*/

template <typename T>
class FenwickTree {
    static_assert(std::is_arithmetic<T>::value || std::is_same<T, char>::value,
                  "Fenwick tree requires numerical data type");

    private:
        std::size_t cap_ = 0;
        T* elements_ = nullptr;
        T* sums_ = nullptr;

        // @brief            - gets decimal val of idx's rightmost '1' bit onward
        // @param idx        - idx to do above operation on
        std::size_t LSB_value(std::size_t idx);

    public:
        // @brief            - creates a new Fenwick tree
        // @param cap        - max els in Fenwick tree (must be 1+)
        FenwickTree(std::size_t cap = 8) {
            if (!cap) {
                throw std::invalid_argument(
                    "Error: FenwickTree constructor. Capacity cannot be 0."
                );
            }

            this->cap_ = cap;
            this->elements_ = new T[this->cap_]{0};
            this->sums_ = new T[this->cap_]{0};
        }
        ~FenwickTree();

        // @brief           - returns Fenwick tree max length
        // @return          - capacity of Fenwick tree
        std::size_t get_cap();

        // @brief           - updates array element
        // @param idx       - index of element to update
        // @param val       - new element value
        void set_el(std::size_t idx, T val);

        // @brief           - calculates a partial sum of els till some index
        // @param end       - index of last array element included in sum
        // @return          - sum of elements up to end index
        T partial_sum(std::size_t end);

        // @brief           - calculates a range sum
        // @param start     - index of first array element included in sum
        // @param end       - index of last array element included in sum
        // @return          - sum of elements in indicated range
        T range_sum(std::size_t start, std::size_t end);

        // @brief           - frees all dynamically allocated memory
        void clear();   

        // @brief           - pretty prints array elements and partial sums
        void print();     
};

/* 
Define class in hpp file due to template issues
*/

// @brief            - gets decimal val of idx's rightmost '1' bit onward
// @param idx        - idx (1 based) to do above operation on
template <typename T>
std::size_t FenwickTree<T>::LSB_value(std::size_t idx) {
    if (idx == 0) {
        throw std::invalid_argument("0 index received for 1-based Fenwick Tree");
    }

    std::size_t shift{0};

    // idx & 1 is 0b00...1 if idx rightmost bit is 1. Else it's 0b00...0
    while ( !(idx & std::size_t(1)) ) {
        ++shift;
        idx = idx >> 1;
    }

    return 1 << shift;
}

template <typename T>
FenwickTree<T>::~FenwickTree() {
    this->clear();
}

template <typename T>
void FenwickTree<T>::clear() {
    delete[] this->elements_;
    delete[] this->sums_;
    this->elements_ = nullptr;
    this->sums_ = nullptr;
    this->cap_ = 0;
}

// @brief           - returns Fenwick tree max length
// @return          - capacity of Fenwick tree
template <typename T>
std::size_t FenwickTree<T>::get_cap() {
    return this->cap_;
}

// @brief           - updates array element
// @param idx       - index (1-based) of element to update
// @param val       - new element value
template <typename T>
void FenwickTree<T>::set_el(std::size_t idx, T val) {
    if (idx == 0) {
        throw std::invalid_argument("0 index received for 1-based Fenwick Tree");
    }

    // update elements
    T change = val - this->elements_[idx-1];
    this->elements_[idx-1] = val;

    // update partial sums
    while (idx <= this->cap_) {
        this->sums_[idx-1] += change;
        idx += this->LSB_value(idx);
    }
}

// @brief           - calculates a partial sum of els till some index
// @param end       - index (1-based) of last array element included in sum
// @return          - sum of elements up to end index
template <typename T>
T FenwickTree<T>::partial_sum(std::size_t end) {
    T sum{};

    while (end) {
        sum += this->sums_[end-1];
        end -= this->LSB_value(end);
    } 

    return sum;
}

// @brief           - calculates a range sum
// @param start     - index (1-based) of first array element included in sum
// @param end       - index (1-based) of last array element included in sum
// @return          - sum of elements in indicated range
template <typename T>
T FenwickTree<T>::range_sum(std::size_t start, std::size_t end) {
    if (end < start) {
        throw std::invalid_argument("End index cannot be smaller than start");
    }

    return this->partial_sum(end) - this->partial_sum(start-1);
}

// @brief           - pretty prints array elements and partial sums
template <typename T>
void FenwickTree<T>::print() {
    std::cout << "Elements: ";
    for (std::size_t i = 0; i < this->cap_; ++i) {
        std::cout << this->elements_[i] << ", ";
    }

    std::cout << std::endl << "Sums: ";
    for (std::size_t i = 0; i < this->cap_; ++i) {
        std::cout << this->sums_[i] << ", ";
    }

    std::cout << std::endl;
}

#endif