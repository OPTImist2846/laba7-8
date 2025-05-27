#include <iostream>
#include "DoublyLinkedList.h"
#include "SinglyLinkedList.h"

int main() {
    std::cout << "Singly Linked List Example:\n";
    SinglyLinkedList<int> sList;
    std::cout << "Is empty: " << sList.isEmpty() << "\n"; // 1 (true)

    sList.pushBack(4);
    sList.pushFront(4);
    sList.pushBack(6);
    std::cout << "List after pushBack/pushFront: " << sList << "\n"; // [5 -> 10 -> 20]
    std::cout << "Size: " << sList.getSize() << "\n"; // 3

    sList.insert(1, 15);
    std::cout << "List after insert(1, 15): " << sList << "\n"; // [5 -> 15 -> 10 -> 20]

    std::cout << "Element at index 2: " << sList[2] << "\n"; // 10

    try {
        sList.insert(100, 99); // This will throw an exception
    } catch (const std::out_of_range& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }
    sList.popFront();
    std::cout << "List after popFront: " << sList << "\n"; // [15 -> 10 -> 20]

    sList.popBack();
    std::cout << "List after popBack: " << sList << "\n"; // [15 -> 10]

    std::cout << "Removed element at index 0: " << sList.removeAt(0) << "\n"; // 15
    std::cout << "List after removeAt(0): " << sList << "\n"; // [10]

    std::cout << "Found 10 at index: " << sList.find(10) << "\n"; // 0
    std::cout << "Found 99 at index: " << sList.find(99) << "\n"; // -1

    std::cout << "Is empty: " << sList.isEmpty() << "\n"; // 0 (false)
    sList.popBack();
    std::cout << "Is empty: " << sList.isEmpty() << "\n"; // 1 (true)

    try {
        sList.popBack(); // This will throw an exception
    } catch (const std::runtime_error& e) {
        std::cerr << "Error: " << e.what() << "\n";
    }

    std::cout << "\n--- Doubly Linked List Example ---\n";
    DoublyLinkedList<std::string> dList;
    std::cout << "Is empty: " << dList.isEmpty();
    return 0;
}