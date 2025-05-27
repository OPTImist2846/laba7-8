
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
// a. Додавання на початок списку
     void pushFront(T val) {
        std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(val);
        if (head) {
            newNode->next = std::move(head);
        }
        head = std::move(newNode);
        size++;
    }
 // a. Додавання на кінець списку
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
// b. Вилучення першого елемента
    T popFront() {
        if (!head) {
            throw std::runtime_error("List is empty. Cannot pop from front.");
        }
        T val = head->data;
        head = std::move(head->next);
        size--;
        return val;
    }
// b. Вилучення останнього елемента
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
// c. Можливість доступу до елементу за індексом
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
// d. Додавання елементу за індексом
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
// d. Вилучення елементу за індексом
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
 // e. Перевірка на розмір
    int getSize() const {
        return size;
    }
// f. Перевірка чи список не порожній
    bool isEmpty() const {
        return size == 0;
    }
// g. Пошук елемента у списку
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
// h. Можливість виведення списку на екран
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
