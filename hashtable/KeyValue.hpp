// @file         - KeyValue.hpp
// @brief        - Defining a key value struct for a hash table
// @author       - Madhav Malhotra
// @date         - 2023-12-22
// @version      - 0.1.0
// @since 0.0.0  - Added tombstone support for open addressing collision schemes
// =============================================================================

#ifndef KEY_VALUE_HPP
#define KEY_VALUE_HPP

#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename K, typename V>
struct KeyValue {
    K key{};
    V val{};
    bool notinit{true};
    bool tomb{false};
};

template <typename K, typename V>
std::ostream& operator<<(std::ostream& os, const KeyValue<K,V>& kv) {
    if (kv.notinit) os << "null, ";
    else if (kv.tomb) os << "T, "; 
    else os << kv.key << ": " << kv.val << ", ";
    return os;
}

#endif
