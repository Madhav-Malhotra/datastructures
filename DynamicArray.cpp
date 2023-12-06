// @file         - DynamicArray.cpp
// @brief        - Creating an automatic dynamic array class
// @author       - Madhav Malhotra
// @date         - 2023-12-05
// @version      - 0.0.0
// =======================================================================================

#include <iostream>
#include <stdexcept>

template <typename T>


class DynamicArray {
    private:
        std::size_t capacity_{0};
        std::size_t size_{0};
        T* p_start_{};
    
    public:

        // @desc            - constructor
        // @param cap       - number of elements in array, >0.
        DynamicArray(std::size_t cap = 10) {
            // handle 0 capacity error
            if (cap < 1) {
                throw std::domain_error("Invalid input capacity: " + std::to_string(cap));
            }

            // allocate memory
            this->capacity_ = cap;
            this->p_start_ = new T[capacity_];
        }

        // @desc               - returns number of reserved memory blocks
        std::size_t capacity() {
            return this->capacity_;
        }

        // @desc               - returns number of occupied memory blocks
        std::size_t length() {
            return this->size_;
        }

        // @desc                - indexes some array element
        // @param idx           - integer between 0 and array size - 1
        // @return              - reference to array element selected
        T& at(std::size_t idx) {
            if (idx >= this->size_) {
                throw std::domain_error("Invalid input index: " + std::to_string(idx));
            }

            return *(this->p_start_ + idx);
        }

        // @desc                - removes last array element
        // @return              - last array element
        T pop() {
            if (this->size_ == 0) {
                throw std::domain_error("No elements to pop");
            }

            T el = *(this->p_start_ + this->size_ - 1);
            // reset memory block for security
            *(this->p_start_ + this->size_ - 1) = T{};
            --this->size_;
            return el;
        }

        // @desc                - adds element to end of array
        // @param val           - value of element
        void push(T val) {
            // avoid overwriting unreserved data
            if (this->size_ >= this->capacity_) {
                double_capacity();
            } 

            ++this->size_;
            *(this->p_start_ + this->size_ - 1) = val;
        }

        // @desc                - copies current data into 2x as large array
        void double_capacity() {
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

        // @desc                - frees up allocated memory
        void clear()  {
            // clear elements for security
            for (std::size_t i = 0; i < size_; ++i) {
                *(p_start_ + size_ - 1) = T{};
            }
            
            size_ = 0;
            capacity_ = 0;
            delete[] p_start_;
            p_start_ = nullptr;
        }
};

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