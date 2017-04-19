#ifndef __REBUILD_BINARY_TREE_HPP__
#define __REBUILD_BINARY_TREE_HPP__

#include <vector>

template<typename T>
struct Node {
    T value;
    struct Node<T> * next;

    Node(const T &v, struct Node<T> * ptr=nullptr) : value(v), next(ptr) {}
    ~Node() {}
};

template<typename T>
struct Node<T> * rebuild_with_preorder_and_inorder(const std::vector<T> &pre_v, const std::vector<T> &in_v) {
    return nullptr;
}

template<typename T>
struct Node<T> * rebuild_with_inorder_and_postorder(const std::vector<T> &in_v, const std::vector<T> &post_v) {
    return nullptr;
}

template<typename T>
struct Node<T> * rebuild_with_postorder_and_preorder(const std::vector<T> &post_v, const std::vector<T> &pre_v) {
    return nullptr;
}

#endif  /* __REBUILD_BINARY_TREE_HPP__ */
