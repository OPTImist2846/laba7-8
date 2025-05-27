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

    };
#endif //LINKEDLISTSTACK_H
