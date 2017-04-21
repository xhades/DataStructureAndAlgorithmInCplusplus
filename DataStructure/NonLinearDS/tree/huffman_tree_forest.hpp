#ifndef __HUFFMAN_TREE_FOREST_HPP__
#define __HUFFMAN_TREE_FOREST_HPP__

#include "node.hpp"

class Forest {
public:
    Forest() {
        members = 0;
        head = new struct Node_Huffman_Forest(nullptr);
        cursor = head;
    }

    ~Forest() {
        clear();
        std::cout << "[+] create HuffmanTree successfully." << std::endl;
    }

    void append(struct Node_Huffman * tree) {
        members++;
        
        struct Node_Huffman_Forest * node = new struct Node_Huffman_Forest(tree);
        cursor->next = node;
        cursor = node;
    }

    struct Node_Huffman * tree(unsigned int index) {
        struct Node_Huffman_Forest * temp = head->next;
        while(index--) {
            temp = temp->next;
        }

        return temp->tree;
    }

    void insert(struct Node_Huffman * tree) {
        members++;

        struct Node_Huffman_Forest * node;
        if (head->next == nullptr) {
            node = new struct Node_Huffman_Forest(tree);
            head->next = node;
        } else {
            struct Node_Huffman_Forest * temp = head;
            while (temp->next != nullptr && tree->weight > temp->next->tree->weight) {
                temp = temp->next;
            }

            temp->next = new struct Node_Huffman_Forest(tree, temp->next);
        }
    }

    void pop() {
        struct Node_Huffman_Forest * temp = head->next;
        head->next = temp->next;
        delete temp;

        members--;
    }

    struct Node_Huffman * entry() {
        return head->next->tree;
    }

    unsigned int size() {
        return members;
    }

    bool empty() {
        return members == 0 ? true : false;
    }

private:
    unsigned int members;
    struct Node_Huffman_Forest * head;
    struct Node_Huffman_Forest * cursor;

    void clear() {
        struct Node_Huffman_Forest * temp = head->next;
        struct Node_Huffman_Forest * temp_backup = nullptr;
        while (temp) {
            temp_backup = temp;
            temp = temp->next;
            delete temp_backup;
            members--;
        }

        head->next = nullptr;
        cursor = head;   
    }
};

#endif  /* __HUFFMAN_TREE_FOREST_HPP__ */

