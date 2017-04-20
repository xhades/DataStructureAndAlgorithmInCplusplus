#ifndef __TREE_OPERATION_HPP__
#define __TREE_OPERATION_HPP__

#include <iostream>
#include <stack>
#include <queue>

#include "node.hpp"

template<typename T>
void print(const T &element, unsigned int repeat) {
    while (repeat--) {
        std::cout << "[+] Element: " << element << std::endl;
    }
}

template<typename T>
void preorder_print(struct Node<T> * root) {
    if (root == nullptr) return;

    print<T>(root->key, root->repeat);
    preorder_print<T>(root->left);
    preorder_print<T>(root->right);
}

template<typename T>
std::vector<T> mode_efficent_preorder(struct Node<T> * root) {
    std::vector<T> vec;

    if (root == nullptr) return vec;

    std::stack<struct Node<T> *> s;
    unsigned int i;
    while(root || !s.empty()) {  
        while (root) {  // 关键代码，没右子树则输出根部
            s.push(root);
            i = root->repeat;
            while (i--) {
                vec.push_back(root->key);
            }
            root = root->left;
        }
        root = s.top();
        s.pop();
        root = root->right;
    }

    return vec;
}

template<typename T>
void inorder_print(struct Node<T> * root) {
    if (root == nullptr) return;

    inorder_print<T>(root->left);
    print<T>(root->key, root->repeat);
    inorder_print<T>(root->right);
}

template<typename T>
std::vector<T> mode_efficent_inorder(struct Node<T> * root) {
    std::vector<T> vec;

    if (root == nullptr) return vec;

    std::stack<struct Node<T> *> s;
    unsigned int i;
    while(root || !s.empty()) {  
        while (root) {  // 关键代码，没右子树则输出根部
            s.push(root);
            root = root->left;
        }
        root = s.top();
        s.pop();
        i = root->repeat;
        while (i--) {
            vec.push_back(root->key);
        }
        root = root->right;
    }  

    return vec;
}

template<typename T>
void postorder_print(struct Node<T> * root) {
    if (root == nullptr) return;

    postorder_print<T>(root->left);
    postorder_print<T>(root->right);
    print<T>(root->key, root->repeat);
}

// TODO
template<typename T>
std::vector<T> mode_efficent_postorder(struct Node<T> * root) {
    std::vector<T> vec;

    if (root == nullptr) return vec;

    return vec;
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
            print<T>(temp->key, root->repeat);
            q.push(temp->left);
            q.push(temp->right);
        }
    }
}

// TODO
template<typename T>
std::vector<T> mode_efficent_levelorder(struct Node<T> * root) {
    std::vector<T> vec;

    if (root == nullptr) return vec;

    return vec;
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
