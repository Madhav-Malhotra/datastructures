// @file         - DynamicArray.cpp
// @brief        - Defining a dynamic array class
// @author       - Madhav Malhotra
// @date         - 2023-12-08
// @version      - 1.0.0
// @since 0.0.0  - Split code into header and cpp for reusability
// =======================================================================================

#include <iostream>
#include <stdexcept>
#include "../hpp/DynamicArray.hpp"




// @brief            - constructor
// @param cap       - number of elements in array, >0.
template <typename T>
DynamicArray<T>::DynamicArray(std::size_t cap = 10) {
    // handle 0 capacity error
    if (cap < 1) {
        throw std::domain_error("Invalid input capacity: " + std::to_string(cap));
    }

    // allocate memory
    this->capacity_ = cap;
    this->p_start_ = new T[capacity_];
}

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
        throw std::domain_error("Invalid input index: " + std::to_string(idx));
    }

    return *(this->p_start_ + idx);
}

// @brief                - removes last array element
// @return              - last array element
template <typename T>
T DynamicArray<T>::pop() {
    if (this->size_ == 0) {
        throw std::domain_error("No elements to pop");
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

int main() {
    DynamicArray<int> a_test;

    // Getter methods
    std::cout << "Initialised elements: " + std::to_string(a_test.length()) << std::endl;
    std::cout << "Reserved blocks: " + std::to_string(a_test.capacity()) << std::endl;

    // index
    for (std::size_t i = 1; i < 25; ++i) {
        a_test.push(i);
    }
    std::cout << "Size after pushes: " + std::to_string(a_test.length()) << std::endl;

    // index
    a_test.at(0) = 15;
    std::cout << "Edit by index: " + std::to_string(a_test.at(0)) << std::endl;

    // pop
    std::cout << "Popped: " + std::to_string(a_test.pop()); 
    std::cout << ". Size: " + std::to_string(a_test.length()) << std::endl;

    // clear
    a_test.clear();
    std::cout << "Cleared: " + std::to_string(a_test.length()) << std::endl;

    return 0;
}