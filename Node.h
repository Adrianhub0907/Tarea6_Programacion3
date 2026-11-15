#ifndef NODE_H
#define NODE_H

template <typename T>
struct Node {
    T data;
    Node* left;
    Node* right;

    explicit Node(T val) : data(val), left(nullptr), right(nullptr) {}
};

#endif // NODE_H