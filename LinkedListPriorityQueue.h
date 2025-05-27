
#ifndef LINKEDLISTPRIORITYQUEUE_H
#define LINKEDLISTPRIORITYQUEUE_H

#include "Node.h"    // Включаємо базову структуру Node
#include <memory>    // Для std::unique_ptr
#include <stdexcept> // Для std::runtime_error

template <typename T>
class LinkedListPriorityQueue {
private:
    std::unique_ptr<Node<T>> head; // Голова списку
    int currentSize;

public:
    // Конструктор
    LinkedListPriorityQueue() : head(nullptr), currentSize(0) {}

    // Деструктор: unique_ptr автоматично звільняє пам'ять
    ~LinkedListPriorityQueue() = default;

    // Enqueue: Додає елемент у відсортованому порядку (менше значення = вищий пріоритет)
    void enqueue(T val) {
        std::unique_ptr<Node<T>> newNode = std::make_unique<Node<T>>(val);

        if (!head || val < head->data) { // Якщо список порожній або новий елемент має вищий пріоритет, ніж голова
            newNode->next = std::move(head);
            head = std::move(newNode);
        } else {
            Node<T>* current = head.get();
            // Знаходимо місце для вставки: ідемо, поки наступний елемент існує
            // і має пріоритет, що не вищий за новий елемент
            while (current->next && current->next->data <= val) {
                current = current->next.get();
            }
            newNode->next = std::move(current->next); // Вставляємо новий вузол
            current->next = std::move(newNode);
        }
        currentSize++;
    }

    // Dequeue: Видаляє і повертає елемент з найвищим пріоритетом (який знаходиться на початку)
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Priority Queue underflow: Cannot dequeue from an empty queue.");
        }
        T val = head->data;
        head = std::move(head->next); // Видаляємо голову списку
        currentSize--;
        return val;
    }

    // Peek: Повертає елемент з найвищим пріоритетом без видалення
    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Priority Queue is empty: Cannot peek at an empty queue.");
        }
        return head->data;
    }

    // isEmpty: Перевіряє, чи черга порожня
    bool isEmpty() const {
        return head == nullptr;
    }

    // isFull: Динамічна структура, ніколи не є "повна"
    bool isFull() const {
        return false;
    }

    // Додатковий метод: повертає поточний розмір черги
    int getSize() const {
        return currentSize;
    }
};
#endif //LINKEDLISTPRIORITYQUEUE_H
