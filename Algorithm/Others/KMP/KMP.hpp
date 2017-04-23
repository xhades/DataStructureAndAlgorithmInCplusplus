#ifndef __KMP_HPP__
#define __KMP_HPP__

#include <iostream>

#include <string>
#include <vector>

#include <cstdio>

class KMP {
public:
    KMP() {}
    ~KMP() {}

    // 移动位数 = 已匹配的字符数 - 对应的部分匹配值
    void match(const std::string &pattern, const std::string &document) {
        generate_partial_match_table(pattern);

        std::vector<unsigned int> match_index;

        unsigned int shift;
        unsigned int match_length;
        for (unsigned int i = 0; i < document.size(); i += shift) {
            if (document.size() - (i + 1) < pattern.size()) break;

            match_length = 0;
            for (unsigned int j = 0; j < pattern.size(); j++) {
                if (pattern[j] == document[i + j]) {
                    match_length++;
                } else {
                    if (match_length == 0) {
                        shift = 1;
                    } else {
                        shift = match_length - partial_match_table[j - 1];
                    }
                    break;
                } 
            }

            if (match_length == pattern.size()) {
                match_index.push_back(i);
            }
        }

        for (unsigned int i = 0; i < match_index.size(); i++) {
            std::cout << "[+] match " << pattern << " pattern at document'index of " << match_index.at(i) << std::endl;
        }

        unsigned int k;
        std::cout << "------------------------------------------------------------------------" << std::endl;
        std::cout << "[+] print match result ..." << std::endl;
        for (unsigned int j = 0, index = 0; j < document.size();) {
            if (index < match_index.size() && j == match_index.at(index)) {
                k = pattern.size();
                while (k--) {
                    printf("\x1b[40;31m%c\x1b[0m", document[j]);
                    j++;
                }
                index++;
            } else {
                printf("\x1b[40;37m%c\x1b[0m", document[j]);
                j++;
            }
        }
        std::cout << std::endl << "------------------------------------------------------------------------" << std::endl;

        delete partial_match_table;
    }

private:
    unsigned int * partial_match_table;

    void generate_partial_match_table(const std::string &pattern) {
        partial_match_table = new unsigned int[pattern.size()];
        // first character's partial match table is 0
        partial_match_table[0] = 0;

        for (unsigned int i = 1, k = 0; i < pattern.size(); i++) {
            while (k > 0 && pattern.at(i) != pattern.at(k)) {
                k = partial_match_table[k - 1];
            }
            if (pattern.at(i) == pattern.at(k)) {
                k++;
            }
            partial_match_table[i] = k;
        }

        std::cout << "[+] generate partial match table ..." << std::endl;
        // for (unsigned int i = 0; i < pattern.size(); i++) {
        //     std::cout << ">> " << pattern.at(i) << ": " << partial_match_table[i] << std::endl;
        // }
        std::cout << "------------------------------------------------------------------------" << std::endl;
    }
};

#endif  /* __KMP_HPP__ */
