#include <memory>

template <typename T>



struct Node {
    T data;
    std::unique_ptr<Node<T>> next;

    Node(T val) : data(val), next(nullptr), prev(nullptr) {}
};

