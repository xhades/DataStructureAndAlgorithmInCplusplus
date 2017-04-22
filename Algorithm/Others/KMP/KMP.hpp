#ifndef __KMP_HPP__
#define __KMP_HPP__

#include <string>
#include <vector>

#include <cstdio>

class KMP {
public:
    KMP() {}
    ~KMP() {}

    // 移动位数 = 已匹配的字符数 - 对应的部分匹配值
    std::vector<unsigned int> match(const std::string &pattern, const std::string &object) {
        generate_partial_match_table(pattern);

        std::vector<unsigned int> match_index;

        unsigned int shift;
        unsigned int match_length;
        for (unsigned int i = 0; i < object.size(); i += shift) {
            if (object.size() - (i + 1) < pattern.size()) break;

            match_length = 0;
            for (unsigned int j = 0; j < pattern.size(); j++) {
                if (pattern[j] == object[i + j]) {
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
            std::cout << "[+] match " << pattern << " pattern at object'index of " << match_index.at(i) << std::endl;
            for (unsigned int j = 0; j < object.size();) {
                if (j == match_index.at(i)) {
                    unsigned int k = pattern.size();
                    while (k--) {
                        printf("\x1b[40;31m%c\x1b[4m", object[j]);
                        j++;
                    }
                } else {
                    printf("\x1b[40;37m%c\x1b[0m", object[j]);
                    j++;
                }
            }
            std::cout << std::endl;
        }

        delete partial_match_table;

        return match_index;
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
        for (unsigned int i = 0; i < pattern.size(); i++) {
            std::cout << ">> " << pattern.at(i) << ": " << partial_match_table[i] << std::endl;
        }
        std::cout << "------------------------------------" << std::endl;
    }
};

#endif  /* __KMP_HPP__ */
