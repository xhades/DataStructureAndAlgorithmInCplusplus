#ifndef __HUFFMAN_TREE_HPP__
#define __HUFFMAN_TREE_HPP__

#include <algorithm>
#include <vector>
#include <map>

#include "huffman_tree_forest.hpp"

bool comp(const std::pair<unsigned int, std::string> &a, const std::pair<unsigned int, std::string> &b) {
    return a.first < b.first;
}

class HuffmanTree {
public:
    HuffmanTree() {
        nodes = 0;
        root = nullptr;
    }
    HuffmanTree(const HuffmanTree &tree) {}
    ~HuffmanTree() {
        clear();
    }
    void operator = (const HuffmanTree &tree) {}

    void build(std::vector<std::pair<unsigned int, std::string> > words) {
        std::sort(words.begin(), words.end(), comp);

        Forest forest;
        for(std::vector<std::pair<unsigned int, std::string> >::iterator it = words.begin(); it != words.end(); it++) {
            forest.append(new struct Node_Huffman(it->first, it->second));
        }
        
        struct Node_Huffman * tree;
        while (forest.size() != 1) {
            tree = new struct Node_Huffman(forest.tree(0)->weight + forest.tree(1)->weight, forest.tree(0)->word + forest.tree(1)->word, forest.tree(0), forest.tree(1));
            forest.pop();
            forest.pop();
            forest.insert(tree);
        }

        root = forest.entry();

        generate_encoder();
    }

    /* output the BS-Tree into dot file */
    void graph_visualize() {
        FILE * fp;
        fp = fopen("HuffmanTree.dot", "w+");
        if (fp != nullptr) {
            fprintf(fp, "digraph G {\n");
            fprintf(fp, "    label = \"Huffman Tree\";\n");
            fprintf(fp, "    node [shape = record, color = black];\n");
            fprintf(fp, "    <%d, %s>[label = \"<f0> | <f1> %d | <f2> \"];\n", root->weight, root->word.c_str(), root->weight);
            fprint_tree(root, fp);
            fprintf(fp, "}\n");
            fclose(fp);
        } else {
            std::cout << "[-] can not open file!" << std::endl;
        }
    }

    void huffman_encode() {
        FILE * fp;
        fp = fopen("HuffmanTreeCharacterEncoding.txt", "w+");
        if (fp != nullptr) {
            for(std::map<char, std::string>::iterator it = encoder.begin(); it != encoder.end(); it++) {
                fprintf(fp, "%c: %s\n", it->first, it->second.c_str());
            }
        } else {
            std::cout << "[-] can not open file!" << std::endl;
        }
    }

    void clear() {
        std::cout << "[+] delete HuffmanTree object from the memory page." << std::endl;
        delete_nodes(root);
    }

private:
    unsigned int nodes;
    struct Node_Huffman * root;
    std::map<char, std::string> encoder;

    void generate_encoder() {
        encode(root, "");
    }

    void encode(struct Node_Huffman * node, std::string prefix) {
        if (node == nullptr) return;

        if (node->left == nullptr && node->right == nullptr) {
            encoder.insert(std::make_pair(node->word.c_str()[0], prefix));
        }

        std::string str = prefix;
        encode(node->left, str.append("0"));
        encode(node->right, prefix.append("1"));
    }

    void fprint_tree(struct Node_Huffman * node, FILE * fp) {
        if (node == nullptr) return;

        if (node->left != nullptr) {
            if (node->left->word.size() > 1) {
                fprintf(fp, "    <%d, %s>[label = \"<f0> | <f1> %d | <f2> \"];\n", node->left->weight, node->left->word.c_str(), node->left->weight);
            } else {
                fprintf(fp, "    <%d, %s>[label = \"<f0> | <f1> (%s, %d) | <f2> \"];\n", node->left->weight, node->left->word.c_str(), node->left->word.c_str(), node->left->weight);
            }
            fprintf(fp, "    <%d, %s>:f0 -> <%d, %s>:f1;\n", node->weight, node->word.c_str(), node->left->weight, node->left->word.c_str());
        }
        if (node->right != nullptr) {
            if (node->right->word.size() > 1) {
                fprintf(fp, "    <%d, %s>[label = \"<f0> | <f1> %d | <f2> \"];\n", node->right->weight, node->right->word.c_str(), node->right->weight);
            } else {
                fprintf(fp, "    <%d, %s>[label = \"<f0> | <f1> (%s, %d) | <f2> \"];\n", node->right->weight, node->right->word.c_str(), node->right->word.c_str(), node->right->weight);
            }
            fprintf(fp, "    <%d, %s>:f2 -> <%d, %s>:f1;\n", node->weight, node->word.c_str(), node->right->weight, node->right->word.c_str());
        }

        fprint_tree(node->left, fp);
        fprint_tree(node->right, fp);
    }

    void delete_nodes(struct Node_Huffman * node) {
        if (node == nullptr) return;

        delete_nodes(node->left);
        delete_nodes(node->right);
        delete node;
        nodes--;
    }
};

#endif  /* __HUFFMAN_TREE_HPP__ */

