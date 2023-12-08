// @file         - DynamicArray.hpp
// @brief        - Declaring a dynamic array class
// @author       - Madhav Malhotra
// @date         - 2023-12-08
// @version      - 0.0.0
// =======================================================================================

#ifndef DYNAMICARRAY_H
#define DYNAMICARRAY_H

template <typename T>
class DynamicArray {
    private:
        std::size_t capacity_{};
        std::size_t size_{};
        T* p_start_{};
    
    public:
        // @brief           - creates new array with a capacity of 10 elements
        // @param cap       - number of elements in array, >0.
        DynamicArray(std::size_t cap = 10);

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

        // @brief                - increases allocated memory by 2x
        void double_capacity();

        // @brief                - frees up all allocated memory
        void clear();
};

#endif