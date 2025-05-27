
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

     void pushFront(T val) {
        std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(val);
        if (head) {
            newNode->next = std::move(head);
        }
        head = std::move(newNode);
        size++;
    }

    void pushBack(T val) {
        std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(val);
        if (!head) {
            head = std::move(newNode);
        } else {
            Node<T>* current = head.get();
            while (current->next) {
                current = current->next.get();
            }
            current->next = std::move(newNode);
        }
        size++;
    }

    T popBack() {
        if (!head) {
            throw std::runtime_error("List is empty. Cannot pop from back.");
        }
        if (size == 1) {
            T val = head->data;
            head = nullptr;
            size--;
            return val;
        }

        Node<T>* current = head.get();
        while (current->next && current->next->next) {
            current = current->next.get();
        }
        T val = current->next->data;
        current->next = nullptr;
        size--;
        return val;
    }
};

#endif //SINGLYLINKEDLIST_H
