#ifndef __TREE_OPERATION_HPP__
#define __TREE_OPERATION_HPP__

#include <iostream>
#include <queue>
#include "node.hpp"

template<typename T>
void do_sth(const T &element, const unsigned int &counter, const unsigned int & level) {
    for (unsigned int i = 0; i < level; i++) {
        std::cout << '\t';
    }
    std::cout << "L" << level << ": " << element << "(" << counter << ")" << std::endl;
}

template<typename T>
void print(const T &element) {
    std::cout << element << std::endl;
}

template<typename T>
void preorder(struct Node<T> * root, const unsigned int & level) {
    if (root == nullptr) return;

    do_sth<T>(root->key, root->counter,level);
    preorder<T>(root->left, level + 1);
    preorder<T>(root->right, level + 1);
}

// TODO
template<typename T>
void mode_efficent_preorder(struct Node<T> * root) {
    if (root == nullptr) return;
}

template<typename T>
void inorder(struct Node<T> * root, const unsigned int & level) {
    if (root == nullptr) return;

    inorder<T>(root->left, level + 1);
    do_sth<T>(root->key, root->counter,level);
    inorder<T>(root->right, level + 1);
}

// TODO
template<typename T>
void mode_efficent_inorder(struct Node<T> * root) {
    if (root == nullptr) return;
}

template<typename T>
void postorder(struct Node<T> * root, const unsigned int & level) {
    if (root == nullptr) return;

    postorder<T>(root->left, level + 1);
    postorder<T>(root->right, level + 1);
    do_sth<T>(root->key, root->counter,level);
}

// TODO
template<typename T>
void mode_efficent_postorder(struct Node<T> * root) {
    if (root == nullptr) return;
}

template<typename T>
void levelorder(struct Node<T> * root) {
    if (root == nullptr) return;

    std::queue<struct Node<T> *> q;
    q.push(root);

    struct Node<T> * temp;
    while (!q.empty()) {
        temp = q.front();
        q.pop();
        if (temp != nullptr) {
            print<T>(temp->key);
            q.push(temp->left);
            q.push(temp->right);
        }
    }
}

// TODO
template<typename T>
void mode_efficent_levelorder(struct Node<T> * root) {

}

template<typename T>
struct Node<T> * reverse(struct Node<T> * root) {
    if (root == nullptr) return nullptr;

    std::queue<struct Node<T> *> q;
    q.push(root);

    struct Node<T> * temp1;
    struct Node<T> * temp2;
    while (!q.empty()) {
        temp1 = q.front();
        q.pop();
        if (temp1 != nullptr) {
            q.push(temp1->left);
            q.push(temp1->right);
            temp2 = temp1->left;
            temp1->left = temp1->right;
            temp1->right = temp2;
        }
    }

    return root;
}

// TODO
template<typename T>
void mode_efficent_reverse(struct Node<T> * root) {
    
}

#endif  /* __TREE_OPERATION_HPP__ */
