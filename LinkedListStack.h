#ifndef LINKED_LIST_STACK_H
#define LINKED_LIST_STACK_H

#include "Node.h"
#include <memory>
#include <stdexcept>

template <typename T>
class LinkedListStack {
private:
    std::unique_ptr<Node<T>> topNode;
    int currentSize;

public:
    // Конструктор: ініціалізує порожній стек
    LinkedListStack() : topNode(nullptr), currentSize(0) {}

    // Деструктор: unique_ptr автоматично звільняє пам'ять всіх вузлів
    ~LinkedListStack() = default;

    // a. Push: Додає елемент на вершину стеку
    void push(T val) {
        std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(val);
        if (topNode) {
            newNode->next = std::move(topNode); // Новий вузол вказує на поточний topNode
        }
        topNode = std::move(newNode); // Новий вузол стає topNode
        currentSize++;
    }

    // b. Pop: Видаляє і повертає елемент з вершини стеку
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack underflow: Cannot pop from an empty stack.");
        }
        T val = topNode->data;
        topNode = std::move(topNode->next); // topNode переміщується на наступний вузол
        currentSize--;
        return val;
    }
    };
#endif //LINKEDLISTSTACK_H
