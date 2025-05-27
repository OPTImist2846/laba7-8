#ifndef ARRAY_STACK_H
#define ARRAY_STACK_H

#include <stdexcept> // Для std::runtime_error, std::invalid_argument

template <typename T>
class ArrayStack {
private:
    T* arr;        // Динамічний масив для зберігання елементів
    int capacity;  // Максимальна ємність стеку
    int topIndex;  // Індекс вершини стеку (-1, якщо порожній)

public:
    // Конструктор: приймає максимальний розмір стеку
    explicit ArrayStack(int size) : capacity(size), topIndex(-1) {
        if (size <= 0) {
            throw std::invalid_argument("Stack capacity must be positive.");
        }
        arr = new T[capacity];
    }

    ~ArrayStack() {
        delete[] arr;
    }
    ArrayStack(const ArrayStack&) = delete;
    ArrayStack& operator=(const ArrayStack&) = delete;

    // a. Push: Додає елемент на вершину стеку
    void push(T val) {
        if (isFull()) {
            throw std::runtime_error("Stack overflow: Cannot push to a full stack.");
        }
        arr[++topIndex] = val; // Збільшуємо індекс і додаємо елемент
    }

    // b. Pop: Видаляє і повертає елемент з вершини стеку
    T pop() {
        if (isEmpty()) {
            throw std::runtime_error("Stack underflow: Cannot pop from an empty stack.");
        }
        return arr[topIndex--]; // Повертаємо елемент і зменшуємо індекс
    }

    // c. Peek: Повертає елемент з вершини стеку без видалення
    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Stack is empty: Cannot peek at an empty stack.");
        }
        return arr[topIndex];
    }

    // d. isEmpty: Перевіряє, чи стек порожній
    bool isEmpty() const {
        return topIndex == -1;
    }

    // d. isFull: Перевіряє, чи стек повний
    bool isFull() const {
        return topIndex == capacity - 1;
    }

    int getSize() const {
        return topIndex + 1;
    }
};



#endif //ARRAYSTACK_H
