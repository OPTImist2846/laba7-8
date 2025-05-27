#ifndef DOUBLYLINKEDLIST_H
#define DOUBLYLINKEDLIST_H
#include <iostream>
#include <memory>
#include <stdexcept>
#include "Node.h"

template <typename T>

class DoublyLinkedList {
private:
    std::unique_ptr<Node<T>> head;
    Node<T>* tail; // Raw pointer to the tail, as unique_ptr cannot be held by multiple owners
    int size;
};



#endif //DOUBLYLINKEDLIST_H
