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

    void pushBack(T val) {
        std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(val);
        if (!head) {
            head = std::move(newNode);
            tail = head.get();
        } else {
            tail->next = std::move(newNode);
            tail->next->prev = tail; // Set prev of the new node
            tail = tail->next.get();
        }
        size++;
    }

    T popFront() {
        if (!head) {
            throw std::runtime_error("List is empty. Cannot pop from front.");
        }
        T val = head->data;
        head = std::move(head->next);
        if (head) {
            head->prev = nullptr;
        } else {
            tail = nullptr; // List became empty
        }
        size--;
        return val;
    }

    T popBack() {
        if (!head) {
            throw std::runtime_error("List is empty. Cannot pop from back.");
        }
        if (size == 1) {
            T val = head->data;
            head = nullptr;
            tail = nullptr;
            size--;
            return val;
        }

        T val = tail->data;
        tail = tail->prev;
        tail->next = nullptr; // The unique_ptr of the last node is now destroyed
        size--;
        return val;
    }

    T& operator[](int index) {
        if (index < 0 || index >= size) {
            throw std::out_of_range("Index out of bounds.");
        }
        Node<T>* current;
        if (index < size / 2) { // Iterate from head for efficiency
            current = head.get();
            for (int i = 0; i < index; ++i) {
                current = current->next.get();
            }
        } else { // Iterate from tail for efficiency
            current = tail;
            for (int i = size - 1; i > index; --i) {
                current = current->prev;
            }
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

        Node<T>* current;
        if (index < size / 2) {
            current = head.get();
            for (int i = 0; i < index; ++i) {
                current = current->next.get();
            }
        } else {
            current = tail;
            for (int i = size - 1; i >= index; --i) {
                current = current->prev;
            }
        }
        std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(val, current->prev);
        newNode->next = std::move(current->prev->next);
        if (newNode->next) { // If not inserting at the very end
            newNode->next->prev = newNode.get();
        }
        current->prev->next = std::move(newNode);
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

        Node<T>* current;
        if (index < size / 2) {
            current = head.get();
            for (int i = 0; i < index; ++i) {
                current = current->next.get();
            }
        } else {
            current = tail;
            for (int i = size - 1; i > index; --i) {
                current = current->prev;
            }
        }
        T val = current->data;
        current->prev->next = std::move(current->next);
        if (current->next) {
            current->next->prev = current->prev;
        }
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

    friend std::ostream& operator<<(std::ostream& os, const DoublyLinkedList<T>& list) {
        Node<T>* current = list.head.get();
        os << "[";
        while (current) {
            os << current->data;
            if (current->next) {
                os << " <-> ";
            }
            current = current->next.get();
        }
        os << "]";
        return os;
    }
};



#endif //DOUBLYLINKEDLIST_H
