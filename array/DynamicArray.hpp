// @file         - DynamicArray.hpp
// @brief        - Declaring a dynamic array class
// @author       - Madhav Malhotra
// @date         - 2023-12-12
// @version      - 1.1.1
// @since 1.1.0  - Updated error types from out of range indices
// @since 1.0.0  - Added new insert function to support derived binary trees
// @since 0.0.0  - moved member function definitions to hpp due to template issues
// =============================================================================

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

#include <cstddef>
#include <iostream>

/* 
Declare class
*/

template <typename T>
class DynamicArray {
    private:
        std::size_t capacity_{};
        std::size_t size_{};
        T* p_start_{};
    
    public:
        // @brief           - creates new array with a capacity of 10 elements
        // @param cap       - number of elements in array, >0.
        // @note            - defined here to support default argument
        DynamicArray(std::size_t cap = 10) {
            // handle 0 capacity error
            if (cap < 1) {
                throw std::domain_error("Invalid input capacity: " + std::to_string(cap));
            }

            // allocate memory
            this->capacity_ = cap;
            this->p_start_ = new T[capacity_];
        }

        // @brief               - returns number of reserved memory blocks
        std::size_t capacity();

        // @brief               - returns number of occupied memory blocks
        std::size_t length();

        // @brief               - indexes some array element
        // @param idx           - integer between 0 and array size - 1
        // @return              - reference to array element selected
        T& at(std::size_t idx);

        // @brief               - removes last array element
        // @return              - last array element
        T pop();

        // @brief               - adds element to end of array
        // @param val           - value of element
        void push(T val);

        // @brief           - appends a value at specified index
        // @param val       - value of new element
        // @param idx       - desired location of new element, 0 <= idx < length
        void insert(T val, std::size_t idx);
        

        // @brief                - increases allocated memory by 2x
        void double_capacity();

        // @brief                - frees up all allocated memory
        void clear();
};


/* 
Define class
*/

// @brief               - returns number of reserved memory blocks
template <typename T>
std::size_t DynamicArray<T>::capacity() {
    return this->capacity_;
}

// @brief               - returns number of occupied memory blocks
template <typename T>
std::size_t DynamicArray<T>::length() {
    return this->size_;
}

// @brief                - indexes some array element
// @param idx           - integer between 0 and array size - 1
// @return              - reference to array element selected
template <typename T>
T& DynamicArray<T>::at(std::size_t idx) {
    if (idx >= this->size_) {
        throw std::range_error("Invalid input index: " + std::to_string(idx));
    }

    return *(this->p_start_ + idx);
}

// @brief                - removes last array element
// @return              - last array element
template <typename T>
T DynamicArray<T>::pop() {
    if (this->size_ == 0) {
        throw std::range_error("No elements to pop");
    }

    T el = *(this->p_start_ + this->size_ - 1);
    // reset memory block for security
    *(this->p_start_ + this->size_ - 1) = T{};
    --this->size_;
    return el;
}

// @brief               - adds element to end of array
// @param val           - value of element
template <typename T>
void DynamicArray<T>::push(T val) {
    // avoid overwriting unreserved data
    if (this->size_ >= this->capacity_) {
        double_capacity();
    } 

    ++this->size_;
    *(this->p_start_ + this->size_ - 1) = val;
}

// @brief           - appends a value at specified index
// @param val       - value of new element
// @param idx       - desired location of new element, 0 <= idx < length
template <typename T>
void DynamicArray<T>::insert(T val, std::size_t idx) {
    // handle special cases
    if (idx == this->size_ - 1) {
        this->push(val);
    } else if (this->size_ > this->capacity_ - 2) {
        double_capacity();
    }

    // shift other elements
    for (int i = this->size_ -1; i >= int(idx); --i) {
        *(this->p_start_ + i + 1) = *(this->p_start_ + i);
    }

    // insert new el
    *(this->p_start_ + idx) = val;
    ++this->size_;
}

// @brief                - copies current data into 2x as large array
template <typename T>
void DynamicArray<T>::double_capacity() {
    this->capacity_ *= 2;
    T* p_start_new = new T[this->capacity_];

    // clear old data for security as we go.
    for (std::size_t i = 0; i < this->size_; ++i) {
        *(p_start_new + i) = *(this->p_start_ + i);
        *(this->p_start_ + i) = T{};
    }

    // CAREFULLY free OLD memory, nullify NEW pointer
    delete[] this->p_start_;
    this->p_start_ = p_start_new;
    p_start_new = nullptr;

    std::cout << "info: capacity doubled to " + std::to_string(this->capacity_) << std::endl;
}

// @brief                - frees up allocated memory
template <typename T>
void DynamicArray<T>::clear()  {
    // clear elements for security
    for (std::size_t i = 0; i < this->size_; ++i) {
        *(this->p_start_ + this->size_ - 1) = T{};
    }
    
    this->size_ = 0;
    this->capacity_ = 0;
    delete[] this->p_start_;
    this->p_start_ = nullptr;
}

#endif