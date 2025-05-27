
#ifndef SINGLYLINKEDLIST_H
#define SINGLYLINKEDLIST_H

#include <iostream>
#include <memory>
#include <stdexcept>
#include "Node.h"
template <typename T>
class SinglyLinkedList {
private:
    std::unique_ptr<Node<T>> head;
    int size;

public:
    // Constructor initializes an empty list
    SinglyLinkedList() : head(nullptr), size(0) {}

    // Destructor (unique_ptr automatically handles memory deallocation of nodes)
    ~SinglyLinkedList() = default;
};

#endif //SINGLYLINKEDLIST_H
