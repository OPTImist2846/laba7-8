#ifndef ARRAYPRIORITYQUEUE_H
#define ARRAYPRIORITYQUEUE_H

#include <vector>    // Використовуємо std::vector як базовий масив для динамічного розміру
#include <stdexcept> // Для std::runtime_error, std::invalid_argument
#include <algorithm> // Для std::swap

template <typename T>
class ArrayPriorityQueue {
private:
    std::vector<T> heap; // Використовуємо std::vector як основу для купи (min-heap)

    // Допоміжна функція: "просіювання вгору" (heapifyUp) - для додавання
    void heapifyUp(int index) {
        while (index > 0 && heap[index] < heap[(index - 1) / 2]) { // Поки не корінь і поточний елемент менший за батьківський
            std::swap(heap[index], heap[(index - 1) / 2]); // Міняємо місцями з батьківським
            index = (index - 1) / 2;                        // Переходимо до батьківського індексу
        }
    }

    // Допоміжна функція: "просіювання вниз" (heapifyDown) - для видалення
    void heapifyDown(int index) {
        int leftChild = 2 * index + 1;
        int rightChild = 2 * index + 2;
        int smallest = index; // Припускаємо, що поточний вузол найменший

        // Знаходимо найменший серед поточного, лівого та правого дочірніх вузлів
        if (leftChild < heap.size() && heap[leftChild] < heap[smallest]) {
            smallest = leftChild;
        }
        if (rightChild < heap.size() && heap[rightChild] < heap[smallest]) {
            smallest = rightChild;
        }

        if (smallest != index) { // Якщо найменший не є поточним вузлом
            std::swap(heap[index], heap[smallest]); // Міняємо місцями
            heapifyDown(smallest);                 // Рекурсивно викликаємо для нового місця
        }
    }

public:
    // Конструктор
    ArrayPriorityQueue() = default;

    // Enqueue: Додає елемент з відповідним пріоритетом
    void enqueue(T val) {
        heap.push_back(val); // Додаємо в кінець вектора
        heapifyUp(heap.size() - 1); // Просіюємо вгору, щоб відновити властивість купи
    }

    // Dequeue: Видаляє і повертає елемент з найвищим пріоритетом (найменший)
    T dequeue() {
        if (isEmpty()) {
            throw std::runtime_error("Priority Queue underflow: Cannot dequeue from an empty queue.");
        }
        T minVal = heap[0]; // Елемент з найвищим пріоритетом завжди знаходиться в корені (індекс 0)

        // Переміщуємо останній елемент на місце кореня
        heap[0] = heap.back();
        heap.pop_back(); // Видаляємо останній елемент

        if (!isEmpty()) {
            heapifyDown(0); // Просіюємо новий корінь вниз, щоб відновити властивість купи
        }
        return minVal;
    }

    // Peek: Повертає елемент з найвищим пріоритетом без видалення
    T peek() const {
        if (isEmpty()) {
            throw std::runtime_error("Priority Queue is empty: Cannot peek at an empty queue.");
        }
        return heap[0]; // Найвищий пріоритет (найменше значення) завжди в корені
    }

    // isEmpty: Перевіряє, чи черга порожня
    bool isEmpty() const {
        return heap.empty();
    }

    // isFull: Для векторної реалізації черга ніколи не є "повна" (обмежена лише пам'яттю системи)
    bool isFull() const {
        return false;
    }

    // Додатковий метод: повертає поточний розмір черги
    int getSize() const {
        return heap.size();
    }
};
#endif //ARRAYPRIORITYQUEUE_H
