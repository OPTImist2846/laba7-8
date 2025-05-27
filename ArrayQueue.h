
#ifndef ARRAYQUEUE_H
#define ARRAYQUEUE_H
#include <stdexcept> // Для std::runtime_error, std::invalid_argument

template <typename T>
class ArrayQueue {
private:
    T* arr;           // Динамічний масив
    int capacity;     // Максимальна ємність черги
    int frontIndex;   // Індекс першого елементу (голова черги)
    int rearIndex;    // Індекс останнього елементу (хвіст черги)
    int currentSize;  // Поточна кількість елементів у черзі

public:
    // Конструктор: приймає максимальний розмір черги
    explicit ArrayQueue(int size) : capacity(size), frontIndex(0), rearIndex(-1), currentSize(0) {
        if (size <= 0) {
            throw std::invalid_argument("Queue capacity must be positive.");
        }
        arr = new T[capacity];
    }

    // Деструктор
    ~ArrayQueue() {
        delete[] arr;
    }

    // Запобігаємо копіюванню та присвоєнню
    ArrayQueue(const ArrayQueue&) = delete;
    ArrayQueue& operator=(const ArrayQueue&) = delete;

    // a. Enqueue: Додає елемент в кінець черги
    void enqueue(T val) {
        if (isFull()) {
            throw std::runtime_error("Queue overflow: Cannot enqueue to a full queue.");
        }
        rearIndex = (rearIndex + 1) % capacity; // Переміщуємо rear по колу
        arr[rearIndex] = val;
        currentSize++;
    }

    // b. Dequeue: Видаляє і повертає елемент з початку черги
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Queue underflow: Cannot dequeue from an empty queue.");
        }
        T val = arr[frontIndex];
        frontIndex = (frontIndex + 1) % capacity; // Переміщуємо front по колу
        currentSize--;
        return val;
    }

    // c. Peek: Повертає елемент з початку черги без видалення
    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Queue is empty: Cannot peek at an empty queue.");
        }
        return arr[frontIndex];
    }

    // d. isEmpty: Перевіряє, чи черга порожня
    bool isEmpty() const {
        return currentSize == 0;
    }

    // d. isFull: Перевіряє, чи черга повна
    bool isFull() const {
        return currentSize == capacity;
    }

    // Додатковий метод: повертає поточний розмір черги
    int getSize() const {
        return currentSize;
    }
};

#endif //ARRAYQUEUE_H
