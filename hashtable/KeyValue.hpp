// @file         - KeyValue.hpp
// @brief        - Defining a key value struct for a hash table
// @author       - Madhav Malhotra
// @date         - 2023-12-17
// @version      - 0.0.0
// =============================================================================

#ifndef KEY_VALUE_HPP
#define KEY_VALUE_HPP

#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename K, typename V>
struct KeyValue {
    K key;
    V val;
};

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const KeyValue<K,V>& kv) {
    os << kv.key << ": " << kv.val << ", ";
    return os;
}

#endif
