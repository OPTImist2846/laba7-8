#ifndef NODE_H
#define NODE_H
#include <memory>

template <typename T>



struct Node {
    T data;
    std::unique_ptr<Node<T>> next;
    Node<T>* prev;

    Node(T val) : data(val), next(nullptr), prev(nullptr) {}
    Node(T val, Node<T>* p) : data(val), next(nullptr), prev(p) {}
};

#endif