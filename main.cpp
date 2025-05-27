#include <iostream>
#include "DoublyLinkedList.h"
#include "SinglyLinkedList.h"

int main() {
    std::cout << "Singly Linked List Example:\n";
    SinglyLinkedList<int> sList;
    std::cout << "Is empty: " << sList.isEmpty() << "\n"; // 1 (true)

    sList.pushBack(10);
    sList.pushFront(5);
    sList.pushBack(20);
    std::cout << "List after pushBack/pushFront: " << sList << "\n"; // [5 -> 10 -> 20]
    std::cout << "Size: " << sList.getSize() << "\n"; // 3

    sList.insert(1, 15);
    std::cout << "List after insert(1, 15): " << sList << "\n"; // [5 -> 15 -> 10 -> 20]

    std::cout << "Element at index 2: " << sList[2] << "\n"; // 10

    return 0;
}