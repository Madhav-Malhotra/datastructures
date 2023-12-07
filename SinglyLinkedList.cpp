#include <cstddef>
#include <iostream>
#include <stdexcept>

template <typename T>
class Node {
    private:
        T data_;
        Node<T>* next_;

    public:
        // Constructor
        Node(T data = T{}) {
            this->data_ = data;
            this->next_ = nullptr;
        }

        // @desc            - updates node value
        // @param T data    - new value
        void setData(T data) {
            this->data_ = data;
        }

        // @desc            - updates next node
        // @param next      - new next node
        // @return          - previous pointer to next node, for memory management
        Node<T>* setNext(Node<T>* next) {
            Node<T>* prev = this->next_;
            this->next_ = next;
            return prev; // CLASS USERS HANDLE MEMORY DEALLOCATION
        }

        // @desc            - get node data
        T getData() {
            return this->data_;
        }

        // @desc            - get node pointer
        Node<T>* getNext() {
            return this->next_;
        }
};

template <typename T>
class SinglyLinkedList {
    private:
        Node<T>* head_;
        Node<T>* tail_;
        int size_;
    
    public:
        // Constructor
        SinglyLinkedList() {
            this->head_ = nullptr;
            this->tail_ = nullptr;
            this->size_ = 0;
        }

        // @desc            - returns number of nodes
        std::size_t length() {
            return this->size_;
        }

        // @desc            - returns first node
        Node<T>* head() {
            return this->head_;
        }

        // @desc            - returns last node
        Node <T>* tail() {
            return this->tail_;
        } 

        // @desc            - adds node to end of list
        // @param node      - node to add
        void add(Node<T>* node) {
            if (node == nullptr) {
                throw std::invalid_argument("Cannot add a null node");
            }

            // Only init head if list is empty
            if (this->head_ == nullptr) {
                this->head_ = node;
            } else {
                this->tail_->setNext(node);
            }

            this->tail_ = node;
            this->size_ += 1;
        }

        // @desc           - removes node from list
        // @param node     - node to remove
        // @return         - memory address of node removed, for memory management
        Node<T>* remove(Node<T>* node) {
            if (node == nullptr) {
                throw std::invalid_argument("Cannot remove null node");
            } else if (this->head_ == nullptr) {
                throw std::range_error("Cannot remove node from empty list");
            }

            // three pointers to track to avoid bugs
            Node<T>* curr = this->head_->getNext();
            Node<T>* prev = this->head_;
            Node<T>* removed = nullptr;

            // special case: remove head, no prev
            if (this->head_ == node) {
                removed = this->head_;
                this->head_ = this->head_->getNext();
            } else {
                while (curr != nullptr) {
                    if (curr == node) {
                        removed = curr;
                        prev->setNext(curr->getNext());
                        
                        // avoid dangling tail pointer
                        if (removed == this->tail_) {
                            this->tail_ = prev;
                        }
                        break;
                    } else {
                        prev = curr;
                        curr = curr->getNext();
                    }
                }
            }

            // Clean up before returning
            if (removed != nullptr) {
                --this->size_;
            }
            curr = nullptr;
            prev = nullptr;
            return removed;
        }

        // @desc           - removes node from list by index
        // @param idx      - index to remove, 0 <= idx < size_
        // @return         - memory address of node removed, for memory management
        Node<T>* remove_by_idx(std::size_t idx) {
            if (idx >= this->size_) {
                throw std::invalid_argument("Index beyond array length");
            }

            // three pointers to track to avoid bugs
            Node<T>* curr = this->head_->getNext();
            Node<T>* prev = this->head_;
            Node<T>* removed = nullptr;

            // special case, remove head, no prev
            if (idx == 0) {
                removed = this->head_;
                this->head_ = this->head_->getNext();
            } else {
                for (std::size_t i = 1; i <= idx; ++i) {
                    // found the node to remove
                    if (i == idx) {
                       removed = curr;
                       prev->setNext(curr.getNext()); 

                       // avoid dangling tail pointer
                       if (i == this->size_ - 1) {
                            this->tail_ = prev;
                       }
                    } 
                    // continue to next node
                    else {
                        prev = curr;
                        curr = curr->getNext();
                    }
                }
            }

            // Clean up before returning
            --this->size_;
            curr = nullptr;
            prev = nullptr;
            return removed;
        }
}; 

int main() {
    // Initialise nodes
    Node<char> a = Node<char>('a');
    Node<char> b = Node<char>('b');
    Node<char> c = Node<char>('c');
    Node<char>d{};

    a.setNext(&b);
    b.setNext(&c);

    std::cout << a.getData() << b.getData() << c.getData() << std::endl;
    std::cout << a.getNext() << b.getNext() << c.getNext() << std::endl;

    // Initialise linked list
    SinglyLinkedList<char> sll_test{};
    std::cout << "Initial size: " << sll_test.length() << std::endl;
    
    sll_test.add(&a);
    std::cout << "Head: " << sll_test.head() << ". Tail: " << sll_test.tail() << std::endl;
    sll_test.add(&b);
    std::cout << "Head: " << sll_test.head() << ". Tail: " << sll_test.tail() << std::endl;
    sll_test.add(&c);
    std::cout << "Updated size: " << sll_test.length() << std::endl;

    // Test removal functions
    std::cout << "Successful remove by pointer: " << sll_test.remove(&a) << ". Updated size: " << sll_test.length() << std::endl;
    std::cout << "Cannot find pointer to remove: " << sll_test.remove(&d) << std::endl;
}