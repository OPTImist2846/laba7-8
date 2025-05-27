
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

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds.");
        }
        Node<T>* current = head.get();
        for (int i = 0; i < index; ++i) {
            current = current->next.get();
        }
        return current->data;
    }

     void insert(int index, T val) {
        if (index < 0 || index > size) {
            throw std::out_of_range("Index out of bounds for insertion.");
        }
        if (index == 0) {
            pushFront(val);
            return;
        }
        if (index == size) {
            pushBack(val);
            return;
        }

        Node<T>* current = head.get();
        for (int i = 0; i < index - 1; ++i) {
            current = current->next.get();
        }
        std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(val);
        newNode->next = std::move(current->next);
        current->next = std::move(newNode);
        size++;
    }

    T removeAt(int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds for removal.");
        }
        if (index == 0) {
            return popFront();
        }
        if (index == size - 1) {
            return popBack();
        }

        Node<T>* current = head.get();
        for (int i = 0; i < index - 1; ++i) {
            current = current->next.get();
        }
        T val = current->next->data;
        current->next = std::move(current->next->next);
        size--;
        return val;
    }

    int getSize() const {
        return size;
    }

    bool isEmpty() const {
        return size == 0;
    }

    int find(T val) const {
        Node<T>* current = head.get();
        int index = 0;
        while (current) {
            if (current->data == val) {
                return index;
            }
            current = current->next.get();
            index++;
        }
        return -1; // Element not found
    }

     friend std::ostream& operator<<(std::ostream& os, const SinglyLinkedList<T>& list) {
        Node<T>* current = list.head.get();
        os << "[";
        while (current) {
            os << current->data;
            if (current->next) {
                os << " -> ";
            }
            current = current->next.get();
        }
        os << "]";
        return os;
    }
};

#endif //SINGLYLINKEDLIST_H
