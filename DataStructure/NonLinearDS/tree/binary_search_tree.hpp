#ifndef __BINARY_SEARCH_TREE_HPP__
#define __BINARY_SEARCH_TREE_HPP__

#include <assert.h>
#include <cstdio>
#include <algorithm>
#include "node.hpp"
#include "tree_operation.hpp"

template<typename T>
class BST {
public:
    BST() {
        nodes = 0;
        root = nullptr;
    }
    BST(const BST<T> &tree) {}
    ~BST() {
        clear();
    }
    void operator = (const BST<T> &tree) {}

    struct Node<T> * build(T * group, unsigned int counter) {
        for (unsigned int i = 0; i < counter; i++) {
            add(group[i]);
            nodes++;
        }

        return root;
    }

    void add(const T &element) {
        root = insert(element, root, nullptr);
    }  

    void remove(const T &element, struct Node<T> * node = nullptr) {
        struct Node<T> * temp;
        if (node == nullptr) {
            temp = root;
        } else {
            temp = node;
        }

        while (temp != nullptr && element != temp->key) {
            if (element < temp->key) {
                temp = temp->left;
            }
            else if (element > temp->key) {
                temp = temp->right;
            }
        }

        if (temp == nullptr) {
            std::cout << ">> " << element << " is not inside the tree" << std::endl;
            return;
        } else {
            if (temp->counter > 1) {
                temp->counter--;
            } else {
                if (temp->left == nullptr && temp->right == nullptr) {
                    if (temp->parent->left == temp) {
                        temp->parent->left = nullptr;
                    } else {
                        temp->parent->right = nullptr;
                    }
                    delete temp;
                }
                else if (temp->left != nullptr && temp->right == nullptr) {
                    if (temp->parent->left == temp) {
                        temp->parent->left = temp->left;
                    } else {
                        temp->parent->right = temp->left;
                    }
                    delete temp;
                }
                else if (temp->left == nullptr && temp->right != nullptr) {
                    if (temp->parent->left == temp) {
                        temp->parent->left = temp->right;
                    } else {
                        temp->parent->right = temp->right;
                    }
                    delete temp;
                }
                else if (temp->left != nullptr && temp->right != nullptr) {
                    struct Node<T> * temp_temp = temp->left;
                    while(temp_temp->right) {
                        temp_temp = temp_temp->right;
                    }
                    temp->key = temp_temp->key;
                    remove(temp_temp->key, temp->left);
                }
            }
        }
    }

    bool find(const T &element) {
        struct Node<T> * temp = root;

        bool is_find = false;
        while (temp) {
            if (element == temp->key) {
                is_find = true;
                break;
            }
            else if (element < temp->key) {
                temp = temp->left;
            }
            else if (element > temp->key) {
                temp = temp->right;
            }
        }

        return is_find;
    }

    T min() {
        struct Node<T> * temp = root;

        while (temp->left) {
            temp = temp->left;
        }

        return temp->key;
    }

    T max() {
        struct Node<T> * temp = root;

        while (temp->right) {
            temp = temp->right;
        }

        return temp->key;
    }

    unsigned int height(struct Node<T> * node = nullptr, unsigned int h = 0) {
        struct Node<T> * temp;
        if (node == nullptr && h == 0) {
            temp = root;
            if (temp == nullptr) return 0;
        } 
        else if (node == nullptr && h != 0) {
            return h;
        }
        else {
            temp = node;
        }

        h++;
        return std::max(height(temp->left, h), height(temp->right, h));
    }

    unsigned int distance() {
        struct Node<T> * temp;
        unsigned int distance;

        temp = root;
        while (temp->left) {
            distance++;
            temp = temp->left;
        }

        temp = root;
        while (temp->right) {
            distance++;
            temp = temp->right;
        }

        return distance;
    }

    void print() {
        inorder<T>(root, 0);
    }

    void reverse_print() {
        inorder<T>(reverse<T>(root), 0);
        root = reverse<T>(root);
    }

    void graph() {
        if (root->right) {
            output(root->right, false, "");
        }
        std::cout << root->key << "(" << root->counter << ")"<< std::endl;
        if (root->left) {
            output(root->left, true, "");
        }
    }

    void graphviz() {
        FILE * fp;
        fp = fopen("graph.dot", "w+");
        if (fp != nullptr) {
            fprintf(fp, "digraph G {\n");
            fprintf(fp, "    label = \"Binary Search Tree\";\n");
            fprintf(fp, "    node [shape = record, color = black];\n");
            fprintf(fp, "    %d[label = \"<f0> | <f1> %d(%d) | <f2> \"];\n", root->key, root->key, root->counter);
            fprint_tree(root, fp);
            fprintf(fp, "}\n");
            fclose(fp);
        } else {
            std::cout << ">> can not open file" << std::endl;
        }
    }

    void clear() {
        delete_nodes(root);
        std::cout << "[+] delete BS-Tree object from the memory page." << std::endl;
    }

    unsigned int size() {
        return nodes;
    }

    bool empty() {  
        return nodes == 0 ? true : false;
    }

private:
    unsigned int nodes;
    struct Node<T> * root;

    struct Node<T> * insert(const T &element, struct Node<T> * ptr, struct Node<T> * ptr_p) {
        if (ptr == nullptr) {
            ptr = new struct Node<T>(element, ptr_p);
        } else {
            if (element < ptr->key) {
                ptr->left = insert(element, ptr->left, ptr);
            }
            else if (element > ptr->key) {
                ptr->right = insert(element, ptr->right, ptr);
            }
            else if (element == ptr->key) {
                ptr->overlay();
            }
        }

        return ptr;
    }

    void output(struct Node<T> * node, bool left, const std::string &indent) {
        if (node->right) {
            output(node->right, false, indent + (left ? "|     " : "      "));
        }
        std::cout << indent;
        std::cout << (left ? '\\' : '/');
        std::cout << "-----";
        std::cout << node->key << "(" << node->counter << ")"<< std::endl;
        if (node->left) {
            output(node->left, true, indent + (left ? "      " : "|     "));
        }
    }

    void fprint_tree(struct Node<T> * node, FILE * fp) {
        if (node == nullptr) return;

        if (node->left != nullptr) {
            fprintf(fp, "    %d[label = \"<f0> | <f1> %d(%d) | <f2> \"];\n", node->left->key, node->left->key, node->left->counter);
            fprintf(fp, "    %d:f0 -> %d:f1;\n", node->key, node->left->key);
        }
        if (node->right != nullptr) {
            fprintf(fp, "    %d[label = \"<f0> | <f1> %d(%d) | <f2> \"];\n", node->right->key, node->right->key, node->right->counter);
            fprintf(fp, "    %d:f2 -> %d:f1;\n", node->key, node->right->key);
        }   
        fprint_tree(node->left, fp);
        fprint_tree(node->right, fp);
    }

    void delete_nodes(struct Node<T> * node) {
        if (node == nullptr) return;

        delete_nodes(node->left);
        delete_nodes(node->right);
        delete node;
        nodes--;
    }
};

#endif  /* __BINARY_SEARCH_TREE_HPP__ */
