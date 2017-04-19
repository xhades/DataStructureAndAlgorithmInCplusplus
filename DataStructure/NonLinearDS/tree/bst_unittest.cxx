#include <iostream>
#include <fstream>
#include <random>
#include <string>

#include "binary_search_tree.hpp"

int main(int argc, char ** argv) {
    // std::ofstream file;
    // file.open("random number.txt");
    // if (file.is_open()) {
    //     std::random_device rd;
    //     std::uniform_int_distribution<int> dist(0, 100);
    //     std::string line;
    //     for (unsigned int i = 0; i < 20; i++) {
    //         line = std::to_string(dist(rd));
    //         line.append("\n");
    //         file << line;
    //     }
    //     file.close();
    // } else {
    //     std::cout << ">> can not open file" << std::endl;
    // }

    std::ifstream file;
    file.open("random number.txt");
    if (file.is_open()) {
        int array[20];
        char line[256];
        
        unsigned int i = 0;
        while (file.getline(line, 256)) {
            array[i] = std::stoi(line);
            i++;
        }
        file.close();

        BST<int> bst;
        bst.build(array, sizeof(array) / sizeof(int));
        bst.graph();
        bst.graphviz();
    } else {
        std::cout << ">> can not open file" << std::endl;
    }
}
