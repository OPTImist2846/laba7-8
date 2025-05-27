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
    };
#endif //LINKEDLISTSTACK_H
