#include <iostream>
#include <string>

#include "Node.h"
#include "ArrayStack.h"
#include "LinkedListStack.h"
#include "ArrayQueue.h"
#include "LinkedListQueue.h"
#include "ArrayPriorityQueue.h"
#include "LinkedListPriorityQueue.h"

// Допоміжна функція для виведення результатів тесту
template <typename T>
void testStructure(T& structure, const std::string& name) {
    std::cout << "\n--- Testing " << name << " ---\n";
    std::cout << "Is empty: " << (structure.isEmpty() ? "true" : "false") << "\n";

    // Test push/enqueue
    if (name.find("Stack") != std::string::npos) { // For Stacks
        std::cout << "Pushing 10, 20, 30...\n";
        structure.push(10);
        structure.push(20);
        structure.push(30);
    } else { // For Queues and Priority Queues
        std::cout << "Enqueuing 10, 20, 30...\n";
        structure.enqueue(10);
        structure.enqueue(20);
        structure.enqueue(30);
    }
    std::cout << "Current size: " << structure.getSize() << "\n";
    std::cout << "Is empty: " << (structure.isEmpty() ? "true" : "false") << "\n";
    std::cout << "Peek: " << structure.peek() << "\n"; // Peek at top/front

    // Test pop/dequeue
    if (name.find("Stack") != std::string::npos) {
        std::cout << "Popping: " << structure.pop() << "\n";
        std::cout << "Popping: " << structure.pop() << "\n";
    } else {
        std::cout << "Dequeuing: " << structure.dequeue() << "\n";
        std::cout << "Dequeuing: " << structure.dequeue() << "\n";
    }
    std::cout << "Current size: " << structure.getSize() << "\n";
    std::cout << "Peek: " << structure.peek() << "\n"; // Peek again

    // Test remaining element
    std::cout << "Dequeuing/Popping last element: " << structure.pop() << "\n"; // Assumes only one left
    std::cout << "Is empty: " << (structure.isEmpty() ? "true" : "false") << "\n";

    // Test underflow exception
    try {
        if (name.find("Stack") != std::string::npos) {
            structure.pop();
        } else {
            structure.dequeue();
        }
    } catch (const std::runtime_error& e) {
        std::cerr << "Caught expected exception: " << e.what() << "\n";
    }

    // Test isFull for Array-based structures (only if they have fixed capacity)
    if (name.find("Array") != std::string::npos) {
        std::cout << "Is full: " << (structure.isFull() ? "true" : "false") << "\n";
        // Fill up to test isFull
        if (name.find("Stack") != std::string::npos) {
             std::cout << "Filling stack to test isFull (capacity 3)...\n";
             try {
                structure.push(1);
                structure.push(2);
                structure.push(3);
                std::cout << "Current size: " << structure.getSize() << "\n";
                std::cout << "Is full: " << (structure.isFull() ? "true" : "false") << "\n";
                structure.push(4); // Should throw
             } catch (const std::runtime_error& e) {
                 std::cerr << "Caught expected exception: " << e.what() << "\n";
             }
        } else if (name.find("Queue") != std::string::npos && name.find("Priority") == std::string::npos) { // Regular ArrayQueue
            std::cout << "Filling queue to test isFull (capacity 3)...\n";
            try {
                structure.enqueue(1);
                structure.enqueue(2);
                structure.enqueue(3);
                std::cout << "Current size: " << structure.getSize() << "\n";
                std::cout << "Is full: " << (structure.isFull() ? "true" : "false") << "\n";
                structure.enqueue(4); // Should throw
            } catch (const std::runtime_error& e) {
                std::cerr << "Caught expected exception: " << e.what() << "\n";
            }
        }
    }
    std::cout << "--- End of " << name << " Test ---\n\n";
}

int main() {
    // Тестування ArrayStack (розмір 3 для демонстрації isFull)
    ArrayStack<int> arrayStack(3);
    testStructure(arrayStack, "Array Stack (int)");

    // Тестування LinkedListStack
    LinkedListStack<std::string> linkedListStack;
    linkedListStack.push("First");
    linkedListStack.push("Second");
    linkedListStack.push("Third");
    std::cout << "\n--- Testing Linked List Stack (string) ---\n";
    std::cout << "Is empty: " << (linkedListStack.isEmpty() ? "true" : "false") << "\n";
    std::cout << "Current size: " << linkedListStack.getSize() << "\n";
    std::cout << "Peek: " << linkedListStack.peek() << "\n";
    std::cout << "Popping: " << linkedListStack.pop() << "\n";
    std::cout << "Popping: " << linkedListStack.pop() << "\n";
    std::cout << "Peek: " << linkedListStack.peek() << "\n";
    std::cout << "Popping: " << linkedListStack.pop() << "\n";
    std::cout << "Is empty: " << (linkedListStack.isEmpty() ? "true" : "false") << "\n";
    try {
        linkedListStack.pop();
    } catch (const std::runtime_error& e) {
        std::cerr << "Caught expected exception: " << e.what() << "\n";
    }
    std::cout << "--- End of Linked List Stack Test ---\n\n";


    // Тестування ArrayQueue (розмір 3)
    ArrayQueue<double> arrayQueue(3);
    testStructure(arrayQueue, "Array Queue (double)");

    // Тестування LinkedListQueue
    LinkedListQueue<char> linkedListQueue;
    linkedListQueue.enqueue('A');
    linkedListQueue.enqueue('B');
    linkedListQueue.enqueue('C');
    std::cout << "\n--- Testing Linked List Queue (char) ---\n";
    std::cout << "Is empty: " << (linkedListQueue.isEmpty() ? "true" : "false") << "\n";
    std::cout << "Current size: " << linkedListQueue.getSize() << "\n";
    std::cout << "Peek: " << linkedListQueue.peek() << "\n";
    std::cout << "Dequeuing: " << linkedListQueue.dequeue() << "\n";
    std::cout << "Dequeuing: " << linkedListQueue.dequeue() << "\n";
    std::cout << "Peek: " << linkedListQueue.peek() << "\n";
    linkedListQueue.enqueue('D'); // Add another element
    std::cout << "Enqueued 'D'. Current size: " << linkedListQueue.getSize() << ". Peek: " << linkedListQueue.peek() << "\n";
    std::cout << "Dequeuing: " << linkedListQueue.dequeue() << "\n";
    std::cout << "Dequeuing: " << linkedListQueue.dequeue() << "\n";
    std::cout << "Is empty: " << (linkedListQueue.isEmpty() ? "true" : "false") << "\n";
    try {
        linkedListQueue.dequeue();
    } catch (const std::runtime_error& e) {
        std::cerr << "Caught expected exception: " << e.what() << "\n";
    }
    std::cout << "--- End of Linked List Queue Test ---\n\n";


    // Тестування ArrayPriorityQueue (min-heap)
    ArrayPriorityQueue<int> arrayPQ;
    std::cout << "\n--- Testing Array Priority Queue (int) ---\n";
    std::cout << "Is empty: " << (arrayPQ.isEmpty() ? "true" : "false") << "\n";
    std::cout << "Enqueuing: 30, 10, 50, 20, 5\n";
    arrayPQ.enqueue(30);
    arrayPQ.enqueue(10);
    arrayPQ.enqueue(50);
    arrayPQ.enqueue(20);
    arrayPQ.enqueue(5);
    std::cout << "Current size: " << arrayPQ.getSize() << "\n";
    std::cout << "Peek (highest priority/min value): " << arrayPQ.peek() << "\n"; // Should be 5
    std::cout << "Dequeuing: " << arrayPQ.dequeue() << "\n"; // Should be 5
    std::cout << "Peek: " << arrayPQ.peek() << "\n";         // Should be 10
    std::cout << "Dequeuing: " << arrayPQ.dequeue() << "\n"; // Should be 10
    std::cout << "Current size: " << arrayPQ.getSize() << "\n";
    while(!arrayPQ.isEmpty()) {
        std::cout << "Dequeuing: " << arrayPQ.dequeue() << "\n";
    }
    std::cout << "Is empty: " << (arrayPQ.isEmpty() ? "true" : "false") << "\n";
    try {
        arrayPQ.dequeue();
    } catch (const std::runtime_error& e) {
        std::cerr << "Caught expected exception: " << e.what() << "\n";
    }
    std::cout << "--- End of Array Priority Queue Test ---\n\n";


    // Тестування LinkedListPriorityQueue (sorted list)
    LinkedListPriorityQueue<std::string> linkedListPQ;
    std::cout << "\n--- Testing Linked List Priority Queue (string) ---\n";
    std::cout << "Is empty: " << (linkedListPQ.isEmpty() ? "true" : "false") << "\n";
    std::cout << "Enqueuing: 'zebra', 'apple', 'orange', 'banana'\n";
    linkedListPQ.enqueue("zebra");
    linkedListPQ.enqueue("apple");
    linkedListPQ.enqueue("orange");
    linkedListPQ.enqueue("banana");
    std::cout << "Current size: " << linkedListPQ.getSize() << "\n";
    std::cout << "Peek (highest priority/alphabetical): " << linkedListPQ.peek() << "\n"; // Should be 'apple'
    std::cout << "Dequeuing: " << linkedListPQ.dequeue() << "\n"; // Should be 'apple'
    std::cout << "Peek: " << linkedListPQ.peek() << "\n";         // Should be 'banana'
    std::cout << "Dequeuing: " << linkedListPQ.dequeue() << "\n"; // Should be 'banana'
    std::cout << "Current size: " << linkedListPQ.getSize() << "\n";
    while(!linkedListPQ.isEmpty()) {
        std::cout << "Dequeuing: " << linkedListPQ.dequeue() << "\n";
    }
    std::cout << "Is empty: " << (linkedListPQ.isEmpty() ? "true" : "false") << "\n";
    try {
        linkedListPQ.dequeue();
    } catch (const std::runtime_error& e) {
        std::cerr << "Caught expected exception: " << e.what() << "\n";
    }
    std::cout << "--- End of Linked List Priority Queue Test ---\n\n";

    return 0;
}