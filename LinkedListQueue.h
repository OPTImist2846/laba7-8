#ifndef LINKEDLISTQUEUE_H
#define LINKEDLISTQUEUE_H
#include "Node.h" // Потребуємо Node структуру
#include <memory>    // For std::unique_ptr
#include <stdexcept> // For std::runtime_error

template <typename T>
class LinkedListQueue {
private:
    std::unique_ptr<Node<T>> frontNode; // Голова черги (перший елемент)
    Node<T>* rearNode;                 // Хвіст черги (останній елемент) - сирий покажчик
    int currentSize;

public:
    // Конструктор
    LinkedListQueue() : frontNode(nullptr), rearNode(nullptr), currentSize(0) {}

    // Деструктор (unique_ptr автоматично звільняє пам'ять)
    ~LinkedListQueue() = default;

    // a. Enqueue: Додавання елементу в кінець черги
    void enqueue(T val) {
        std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(val);
        if (isEmpty()) {
            frontNode = std::move(newNode); // Якщо черга порожня, новий вузол стає і front, і rear
            rearNode = frontNode.get();
        } else {
            rearNode->next = std::move(newNode); // Поточний rear вказує на новий вузол
            rearNode = rearNode->next.get();    // rear переміщується на новий вузол
        }
        currentSize++;
    }

    // a. Dequeue: Видалення елементу з початку черги
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue underflow: Cannot dequeue from an empty queue.");
        }
        T val = frontNode->data;
        frontNode = std::move(frontNode->next); // front переміщується на наступний вузол
        if (frontNode == nullptr) { // Якщо черга стала порожньою після dequeue
            rearNode = nullptr;    // rear також має бути nullptr
        }
        currentSize--;
        return val;
    }

    // c. Peek: Отримання елементу з початку черги без видалення
    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty: Cannot peek at an empty queue.");
        }
        return frontNode->data;
    }

    // d. isEmpty: Перевірка, чи черга порожня
    bool isEmpty() const {
        return frontNode == nullptr; // або currentSize == 0;
    }

    // d. isFull: Для зв'язаного списку черга ніколи не є "повна"
    bool isFull() const {
        return false;
    }

    // Отримання поточного розміру черги
    int getSize() const {
        return currentSize;
    }
};
#endif //LINKEDLISTQUEUE_H
