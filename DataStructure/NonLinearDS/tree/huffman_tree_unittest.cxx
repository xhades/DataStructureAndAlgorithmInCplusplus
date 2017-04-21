#include <iostream>
#include <fstream>

#include <vector>

#include "huffman_tree.hpp"

int main(int argc, char ** argv) {
    std::ifstream file;
    file.open("word frequency.txt");

    if (file.is_open()) {
        std::vector<std::pair<unsigned int, std::string> > words;

        char buffer[256];
        std::string::size_type pos;
        while (!file.eof()) {
            file.getline(buffer, 256);

            std::string str(buffer);
            pos = str.find(" : ");
            if (pos != std::string::npos) {
                std::string word = str.substr(0, 1);
                std::string count = str.substr(pos + 3, str.size() - (pos + 3));
                words.push_back(std::make_pair(std::stoi(count), word));
            }
        }

        HuffmanTree tree;
        tree.build(words);
        tree.graph_visualize();
    }
}
