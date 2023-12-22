// @file         - SeparateChaining.hpp
// @brief        - Defining a hashtable using separate chaining for collisions
// @author       - Madhav Malhotra
// @date         - 2023-12-17
// @version      - 0.0.0
// =============================================================================

#ifndef HASHTABLE_SEPARATE_CHAINING_HPP3
#define HASHTABLE_SEPARATE_CHAINING_HPP3

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <functional>
#include "./KeyValue.hpp"
#include "../array/DynamicArray.hpp"
#include "../linkedlist/SinglyLinkedList.hpp"

/* 
Declare class
*/

template <typename K, typename V>
class SC_HashTable {
    private:
        // array of pointers to linked lists that hold key val pairs
        DynamicArray< SLList<KeyValue<K,V>>* > arr_{};
        std::size_t max_depth_{5};
        std::size_t count_{};

        // @brief           - hashes input key to index in array.
        // @param key       - immutable key to hash.
        // @return          - index linked list to add key's val to.
        std::size_t hash(K key);
        
    public:
        // destructor, getters, and setters
        ~SC_HashTable();
        std::size_t count();
        std::size_t max_depth();
        void set_max_depth(std::size_t depth);

        // @brief           - add a key value pair to the hash table
        // @param key       - immutable key for new key value pair
        // @param val       - arbitrary data type value for key val pair
        // @return          - false if failed for reasons like duplicate keys
        bool add(K key, V val);

        // @brief           - remove a key value pair to the hash table
        // @param key       - immutable key to find kv pair to remove
        // @return          - false if failed for reasons like key not found
        bool remove(K key);

        // @brief           - access value stored at specified key
        // @param key       - key to retrieve value from
        // @param found     - output parameter, set to false if key not found
        // @return          - default val if key not found, else stored val 
        V at(K key, bool& found);
        
        // @brief           - moves els to 2x larger array to reduce collisions
        void double_capacity();

        // @brief           - deletes all elements
        void clear();

        // @brief           - pretty prints saved data to console
        void print();
};


/* 
Define class - in hpp file due to template issues
*/

// Destructor, getters, and setters.
template <typename K, typename V>
SC_HashTable<K,V>::~SC_HashTable() {
    this->clear();
}

template <typename K, typename V>
std::size_t SC_HashTable<K,V>::count() {
    return this->count_;
}

template <typename K, typename V>
std::size_t SC_HashTable<K,V>::max_depth() {
    return this->max_depth_;
}

template <typename K, typename V>
void SC_HashTable<K,V>::set_max_depth(std::size_t depth) {
    this->max_depth_ = depth;
}

// @brief           - hashes input key to index in array.
// @param key       - immutable key to hash.
// @return          - index linked list to add key's val to.
template <typename K, typename V>
std::size_t SC_HashTable<K,V>::hash(K key) {
    std::size_t hash = std::hash<K>{}(key);
    return hash % this->arr_.capacity();
}

// @brief           - add a key value pair to the hash table
// @param key       - immutable key for new key value pair
// @param val       - arbitrary data type value for key val pair
// @return          - false if failed for reasons like duplicate keys
template <typename K, typename V>
bool SC_HashTable<K,V>::add(K key, V val) {
    // setup data
    bool duplicates = false;
    std::size_t idx = this->hash(key);
    KeyValue<K,V> kv = {key, val};
    SLList<KeyValue<K,V>>* list = this->arr_.at(idx);

    // handle un-initialised list
    if (list == nullptr) {
        list = new SLList<KeyValue<K,V>>{};
        this->arr_.set(list, idx);
    }

    // check for duplicate keys
    std::size_t len = list->length();
    SLNode<KeyValue<K,V>>* par = list->head();
    for (std::size_t i = 0; i < len; ++i) {
        if (par && par->getData().key == key) {
            duplicates = true;
            break;
        }
        par = par->getNext();
    }

    // otherwise, add new key-value pair
    if (!duplicates) {
        list->push(kv);
        ++this->count_;
    }

    // handle excessive list depth
    if (list->length() >= this->max_depth_) {
        this->double_capacity();
    }

    return !duplicates;
}

// @brief           - remove a key value pair to the hash table
// @param key       - immutable key to find kv pair to remove
// @return          - false if failed for reasons like key not found
template <typename K, typename V>
bool SC_HashTable<K,V>::remove(K key) {
    std::size_t idx = this->hash(key);
    SLList<KeyValue<K,V>>* list = this->arr_.at(idx);

    if (list) {
        // check for key to remove
        std::size_t len = list->length();
        SLNode<KeyValue<K,V>>* par = list->head();
        for (std::size_t i = 0; i < len; ++i) {
            if (par && par->getData().key == key) {
                list->remove_by_index(i);
                --this->count_;
                return true;
            }
            par = par->getNext();
        }
    }

    return false; // implicitly handles unitialised list
}

// @brief           - access value stored at specified key
// @param key       - key to retrieve value from
// @param found     - output parameter, set to false if key not found
// @return          - default val if key not found, else stored val
template <typename K, typename V>
V SC_HashTable<K,V>::at(K key, bool& found) {
    // find relevant list
    found = false;
    std::size_t idx = this->hash(key);
    SLList<KeyValue<K,V>>* list = this->arr_.at(idx);

    if (list) {
        // check if desired key is there
        std::size_t len = list->length();
        SLNode<KeyValue<K,V>>* par = list->head();
        for (std::size_t i = 0; i < len; ++i) {
            if (par && par->getData().key == key) {
                found = true;
                return par->getData().val;
            }
            par = par->getNext();
        }
    }

    return V{}; // implicitly handles all exceptions
}

// @brief           - moves els to 2x larger array to reduce collisions
template <typename K, typename V>
void SC_HashTable<K,V>::double_capacity() {
    // setup data
    KeyValue<K,V>* old_els = new KeyValue<K,V>[this->count_];
    std::size_t tail = 0;
    std::size_t og_cap = this->arr_.capacity();
    this->arr_.double_capacity();
    
    // remove linked list elements
    for (std::size_t i = 0; i < og_cap; ++i) {
        SLList<KeyValue<K,V>>* list = this->arr_.at(i);
        std::size_t len = (list) ? list->length() : 0;

        for (std::size_t j = 0; j < len; ++j) {
            *(old_els + tail) = this->arr_.at(i)->remove_by_index(0);
            ++tail;
        }
    }

    // rehash elements
    for (std::size_t i = 0; i < this->count_; ++i) {
        KeyValue<K,V> kv = *(old_els + i);
        std::size_t idx = this->hash(kv.key);
        SLList<KeyValue<K,V>>* list = this->arr_.at(idx);

        if (!list) {
            list = new SLList<KeyValue<K,V>>{};
            this->arr_.set(list, idx);
        }
        list->push(kv);
    }

    delete[] old_els;
    old_els = nullptr;
}

// @brief           - removes all stored data in the hashtable
template <typename K, typename V>
void SC_HashTable<K,V>::clear() {
    // clear linked lists
    for (std::size_t i = 0; i < this->arr_.capacity(); ++i) {
        SLList<KeyValue<K,V>>* list = this->arr_.at(i);
        if (list != nullptr) {
            list->clear();
            delete list;
        }
    }

    // reset array
    this->arr_.clear();
    this->count_ = 0;
}

// @brief           - pretty print hashtable elements
template <typename K, typename V>
void SC_HashTable<K,V>::print() {

    std::size_t cap = this->arr_.capacity();
    for (std::size_t i = 0; i < cap; ++i) {
        std::cout << i;
        SLList<KeyValue<K,V>>* list = this->arr_.at(i);

        if (list == nullptr || !list->length()) {
            std::cout << "| null" << std::endl;
        } else {
            std::cout << "| "; 
            list->print(); 
        }
    }
}


#endif