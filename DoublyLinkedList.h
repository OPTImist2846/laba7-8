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

public:
    DoublyLinkedList() : head(nullptr), tail(nullptr), size(0) {}

    // Destructor (unique_ptr handles head, remaining nodes are linked via next)
    ~DoublyLinkedList() = default;

    void pushFront(T val) {
        std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(val);
        if (!head) {
            head = std::move(newNode);
            tail = head.get();
        } else {
            newNode->next = std::move(head);
            head->prev = newNode.get();
            head = std::move(newNode);
        }
        size++;
    }
};



#endif //DOUBLYLINKEDLIST_H
