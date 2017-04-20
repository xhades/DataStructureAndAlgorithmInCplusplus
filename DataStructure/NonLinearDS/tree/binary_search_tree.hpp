#ifndef __BINARY_SEARCH_TREE_HPP__
#define __BINARY_SEARCH_TREE_HPP__

#include <fstream>
#include <algorithm>
#include <string>
#include <vector>

#include <cassert>
#include <cstdio>

#include <json/json.h>

#include "node.hpp"
#include "tree_operation.hpp"
#include "rebuild_list.hpp"

template<typename T>
class BST {
public:
    BST() {
        nodes = 0;
        root = nullptr;
    }
    BST(const BST<T> &tree) {

    }
    ~BST() {
        clear();
    }
    void operator = (const BST<T> &tree) {
        
    }

    struct Node<T> * build(T group[], unsigned int elements) {
        for (unsigned int i = 0; i < elements; i++) {
            add(group[i]);
            nodes++;
        }

        return root;
    }

    struct Node<T> * add(const T &element) {
        root = insert(element, root, nullptr);

        return root;
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
            if (temp->repeat > 1) {
                temp->repeat--;
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

    void serialize() {
        // typedef typename std::vector<T>::iterator iterator;

        std::vector<T> vec_preorder = mode_efficent_preorder<T>(root);
        std::vector<T> vec_inorder = mode_efficent_inorder<T>(root);
        // std::vector<T> vec = mode_efficent_postorder<T>(root);

        Json::Value root;
        Json::Value Preorder;
        Json::Value Inorder;

        for (unsigned int i = 0; i < size(); i++) {
            Preorder[i] = vec_preorder.at(i);
            Inorder[i] = vec_inorder.at(i);
        }
  
        root["Preorder"] = Preorder;
        root["Inorder"] = Inorder;

        Json::FastWriter writer;
        std::string json_file = writer.write(root);

        std::ofstream file;
        file.open("BSTreeSerialization.json");
        if (file.is_open()) {
            file << json_file;
            file.close();
        } else {
            std::cout << "[-] can not open file!" << std::endl;
        }
    }

    /* print the BS-Tree on the command line */
    void print() {
        if (root->right) {
            output(root->right, false, "");
        }
        std::cout << root->key << "(" << root->repeat << ")"<< std::endl;
        if (root->left) {
            output(root->left, true, "");
        }
    }

    /* output the BS-Tree into dot file */
    void graph_visualize() {
        FILE * fp;
        fp = fopen("graph.dot", "w+");
        if (fp != nullptr) {
            fprintf(fp, "digraph G {\n");
            fprintf(fp, "    label = \"Binary Search Tree\";\n");
            fprintf(fp, "    node [shape = record, color = black];\n");
            fprintf(fp, "    %d[label = \"<f0> | <f1> %d(%d) | <f2> \"];\n", root->key, root->key, root->repeat);
            fprint_tree(root, fp);
            fprintf(fp, "}\n");
            fclose(fp);
        } else {
            std::cout << "[-] can not open file!" << std::endl;
        }
    }

    void clear() {
        std::cout << "[+] delete BS-Tree object from the memory page." << std::endl;
        delete_nodes(root);
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

    struct Node<T> * insert(const T &element, struct Node<T> * ptr, struct Node<T> * ptr_parent) {
        if (ptr == nullptr) {
            ptr = new struct Node<T>(element, ptr_parent);
        } else {
            if (element < ptr->key) {
                ptr->left = insert(element, ptr->left, ptr);
            }
            else if (element > ptr->key) {
                ptr->right = insert(element, ptr->right, ptr);
            }
            else if (element == ptr->key) {
                ptr->add();
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
        std::cout << node->key << "(" << node->repeat << ")"<< std::endl;
        if (node->left) {
            output(node->left, true, indent + (left ? "      " : "|     "));
        }
    }

    void fprint_tree(struct Node<T> * node, FILE * fp) {
        if (node == nullptr) return;

        if (node->left != nullptr) {
            fprintf(fp, "    %d[label = \"<f0> | <f1> %d(%d) | <f2> \"];\n", node->left->key, node->left->key, node->left->repeat);
            fprintf(fp, "    %d:f0 -> %d:f1;\n", node->key, node->left->key);
        }
        if (node->right != nullptr) {
            fprintf(fp, "    %d[label = \"<f0> | <f1> %d(%d) | <f2> \"];\n", node->right->key, node->right->key, node->right->repeat);
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

template<typename T>
BST<T> * rebuild(const std::string &json_file) {
    BST<T> * bst_ptr = nullptr;

    std::ifstream file;
    file.open(json_file);
    if (file.is_open()) {
        std::string json_object("");

        char buffer[1024];     
        while (!file.eof()) {
            file.getline(buffer, 1024);
            json_object.append(buffer);
        }   
        file.close();

        Json::Reader reader;
        Json::Value root;
        if (reader.parse(json_object.c_str(), root)) {
            std::cout << "[+] read json object" << std::endl;
            Json::Value Preorder = root["Preorder"];
            Json::Value Inorder = root["Inorder"];

            LinkedList<T> Preorder_list(0x7fffffff);
            LinkedList<T> Inorder_list(0x7fffffff);
            for (unsigned int i = 0; i < Preorder.size(); i++) {
                Preorder_list.append(std::stoi(Preorder[i].asString()));
            }
            for (unsigned int i = 0; i < Inorder.size(); i++) {
                Inorder_list.append(std::stoi(Inorder[i].asString()));
            }

            LinkedList<T> Preorder_list_left(0x7fffffff);
            LinkedList<T> Preorder_list_right(0x7fffffff);
            LinkedList<T> Inorder_list_left(0x7fffffff);
            LinkedList<T> Inorder_list_right(0x7fffffff);

            
        } else {
            std::cout << "[-] can not parse json file!" << std::endl;
        }
    } else {
        std::cout << "[-] can not open file!" << std::endl;
    }

    return bst_ptr;
}

#endif  /* __BINARY_SEARCH_TREE_HPP__ */
