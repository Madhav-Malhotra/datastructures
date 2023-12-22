// @file         LinearProbing.hpp
// @brief        Defining a hashtable with open addressing with linear probing
// @author       Madhav Malhotra
// @date         2023-12-20
// @version      0.0.0
// =============================================================================

#ifndef HASHTABLE_LINEAR_PROBING_HPP
#define HASHTABLE_LINEAR_PROBING_HPP

#include <iostream>
#include <cstddef>
#include <stdexcept>
#include <functional>
#include "./KeyValue.hpp"
#include "../array/DynamicArray.hpp"

/* 
Declare class
*/

template <typename K, typename V>
class LP_HashTable {
    protected:
        DynamicArray< KeyValue<K,V> > arr_{};
        float load_threshold_{0.7};
        std::size_t count_{};

        // @brief           hashes input key to index in array.
        // @param key       immutable key to hash.
        // @return          index linked list to add key's val to.
        std::size_t hash(K key);

        // @brief           offsets hash bucket index in collisions
        // @param iter      iteration of sequence, 0 < iter < infty
        // @return          0 < offset < infty
        virtual std::size_t probe(std::size_t iter);
        
    public:
        // destructor
        ~LP_HashTable();
        
        // @brief           get count
        // @return          number of key value pairs in hash table
        std::size_t count();

        // @brief           get load threshold (max kv pairs / hash table capacity)
        // @return          load threshold setting
        float load_threshold();

        // @brief           get load factor (current kv pairs / hash table capacity)
        // @return          current load factor
        float load_factor();

        // @brief           get keys
        // @param num       output parameter, number of keys
        // @return          pointer to first key
        K* keys(std::size_t& num);

        // @brief           get values
        // @param num       output parameter, number of values
        // @return          pointer to first value
        V* values(std::size_t& num);

        // @brief                set load factor
        // @param load_threshold    0 < factor <= 1. Recommended range: 0.4-0.7
        void set_load_threshold(float load_threshold);

        // @brief           add a key value pair to the hash table
        // @param key       immutable key for new key value pair
        // @param val       arbitrary data type value for key val pair
        // @return          false if failed for reasons like duplicate keys
        bool add(K key, V val);

        // @brief           remove a key value pair to the hash table
        // @param key       immutable key to find kv pair to remove
        // @return          false if failed for reasons like key not found
        bool remove(K key);

        // @brief           access value stored at specified key
        // @param key       key to retrieve value from
        // @param found     output parameter, set to false if key not found
        // @return          default val if key not found, else stored val 
        V at(K key, bool& found);
        
        // @brief           moves els to 2x larger array to reduce collisions
        void double_capacity();

        // @brief           deletes all elements
        void clear();

        // @brief           pretty prints saved data to console
        void print();
};


/* 
Define class in hpp file due to template issues
*/

// Destructor, getters, and setters.
template <typename K, typename V>
LP_HashTable<K,V>::~LP_HashTable() {
    this->clear();
}

template <typename K, typename V>
std::size_t LP_HashTable<K,V>::count() {
    return this->count_;
}

template <typename K, typename V>
float LP_HashTable<K,V>::load_threshold() {
    return this->load_threshold_;
}

template <typename K, typename V>
float LP_HashTable<K,V>::load_factor() {
    return float(this->count_) / float(this->arr_.capacity());
}

template <typename K, typename V>
void LP_HashTable<K,V>::set_load_threshold(float load_threshold) {
    if (load_threshold > 0 && load_threshold <= 1) {
        this->load_threshold_ = load_threshold;
    } else {
        throw std::invalid_argument("Load factor is not in range (0, 1]");
    }
}

// @brief           hashes input key to index in array.
// @param key       immutable key to hash.
// @return          index linked list to add key's val to.
template <typename K, typename V>
std::size_t LP_HashTable<K,V>::hash(K key) {
    std::size_t hash = std::hash<K>{}(key);
    return hash % this->arr_.capacity();
}

// @brief           offsets hash bucket index in collisions
// @param iter      iteration of sequence, 0 < iter < infty
// @return          0 < offset < infty
template <typename K, typename V>
std::size_t LP_HashTable<K,V>::probe(std::size_t iter) {
    return iter;
}

// @brief           add a key value pair to the hash table
// @param key       immutable key for new key value pair
// @param val       arbitrary data type value for key val pair
// @return          false if failed for reasons like duplicate keys
template <typename K, typename V>
bool LP_HashTable<K,V>::add(K key, V val) {
    // obtain base hash index
    std::size_t base = this->hash(key);
    std::size_t idx = base + 0;
    KeyValue<K,V> curr = this->arr_.at(base + 0);
    std::size_t iter{1};

    // while bucket isn't null or a tombstone,
    while( !(curr.notinit || curr.tomb) ) {
        // keep offsetting with probe
        if (curr.key == key) return false;
        idx = (base + this->probe(iter)) % this->arr_.capacity();
        curr = this->arr_.at(idx);
        ++iter;
    }

    // when empty/tomb bucket found, add value
    this->count_ += (curr.tomb) ? 0 : 1;

    curr.key = key;
    curr.val = val;
    curr.notinit = false;
    curr.tomb = false;
    this->arr_.set(curr, idx);

    if (this->load_factor() > this->load_threshold_) this->double_capacity();
    return true;
}

// @brief           remove a key value pair to the hash table
// @param key       immutable key to find kv pair to remove
// @return          false if failed for reasons like key not found
template <typename K, typename V>
bool LP_HashTable<K,V>::remove(K key) {
    // obtain base hash index
    std::size_t base = this->hash(key);
    std::size_t idx = base + 0;
    KeyValue<K,V> curr = this->arr_.at(idx);
    std::size_t iter{0};

    // While bucket isn't null,
    while(!curr.notinit) {
        // check if key found.
        if (curr.key == key) {
            curr.key = K{};
            curr.val = V{};
            curr.tomb = true;
            this->arr_.set(curr, idx);
            return true;
        }

        // Check next bucket if not.
        ++iter;
        idx = (base + this->probe(iter)) % this->arr_.capacity();
        curr = this->arr_.at(idx);
    }

    return false;
}

// @brief           access value stored at specified key
// @param key       key to retrieve value from
// @param found     output parameter, set to false if key not found
// @return          default val if key not found, else stored val
template <typename K, typename V>
V LP_HashTable<K,V>::at(K key, bool& found) {
    // obtain base hash index
    std::size_t base = this->hash(key);
    KeyValue<K,V> curr = this->arr_.at(base + 0);

    // data to track while offsetting
    std::size_t iter{1};
    int first_tomb{-1};
    std::size_t last_free{0};

    found = false;
    V val{};

    // While bucket isn't null and key hasn't been found,
    while(!curr.notinit && !found) {
        // keep offsetting with probe,
        std::size_t idx = (base + this->probe(iter)) % this->arr_.capacity();
        curr = this->arr_.at(idx);

        // until key found.
        if (curr.key == key) {
            found = true;
            val = curr.val;
        }

        // Track the first tombstone and last free bucket found.
        if (!curr.tomb) last_free = idx;
        else if (first_tomb < 0) first_tomb = idx;

        // Whenever a first tombstone and last free bucket exist, swap them.
        if (first_tomb > -1 && last_free > std::size_t(first_tomb) ) {
            KeyValue<K,V> tomb = this->arr_.at(first_tomb);
            KeyValue<K,V> last = this->arr_.at(last_free);

            tomb.tomb = false;
            tomb.key = last.key;
            tomb.val = last.val;
            this->arr_.set(tomb, first_tomb);
            first_tomb = last_free;

            last.key = K{};
            last.val = V{};
            last.notinit = false;
            last.tomb = true;
            this->arr_.set(last, last_free);
            last_free = 0;
        }
        ++iter;
    }

    return val;
}

// @brief           moves els to 2x larger array to reduce collisions
template <typename K, typename V>
void LP_HashTable<K,V>::double_capacity() {
    // create new array
    std::size_t cap = this->arr_.capacity();
    DynamicArray<KeyValue<K,V>> old = this->arr_;

    this->arr_ = DynamicArray<KeyValue<K,V>>(cap * 2);
    this->count_ = 0;

    for (std::size_t i = 0; i < cap; ++i) {
        KeyValue<K,V> curr = old.at(i);
        if (!(curr.notinit || curr.tomb)) {
            this->add(curr.key, curr.val);
        }
    }

    // update array
    old.clear();
    std::cout << "info: doubled hash table capacity" << std::endl;
}

// @brief           removes all stored data in the hashtable
template <typename K, typename V>
void LP_HashTable<K,V>::clear() {
    this->arr_.clear();
    this->count_ = 0;
}

// @brief           pretty print hashtable elements
template <typename K, typename V>
void LP_HashTable<K,V>::print() {
    std::size_t cap = this->arr_.capacity();
    for (std::size_t i = 0; i < cap; ++i) {
        std::cout << this->arr_.at(i);
    }
    std::cout << std::endl;
}


#endif