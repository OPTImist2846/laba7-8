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
        arr = new T[capacity]; // Виділяємо пам'ять для масиву
    }

    // Деструктор: звільняє виділену динамічну пам'ять
    ~ArrayStack() {
        delete[] arr;
    }
};



#endif //ARRAYSTACK_H
