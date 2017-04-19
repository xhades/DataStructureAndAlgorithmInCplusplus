#ifndef __STRING_OPERATION_HPP__
#define __STRING_OPERATION_HPP__

#include <string>
#include <vector>

void split(const std::string &str, std::vector<std::string> &str_vector, std::string sep = ", ") {
    if (str.empty()) return;

    std::string temp_str;
    std::string::size_type pos_begin = str.find_first_not_of(sep);
    std::string::size_type comma_pos = 0;

    while (pos_begin != std::string::npos) {
        comma_pos = str.find(sep, pos_begin);
        if (comma_pos != std::string::npos) {
            temp_str = str.substr(pos_begin, comma_pos - pos_begin);
            pos_begin = comma_pos + sep.length();
        }
        else {
            temp_str = str.substr(pos_begin);
            pos_begin = comma_pos;
        }

        if (!temp_str.empty()) {
            str_vector.push_back(temp_str);
            temp_str.clear();
        }
    }
}

#endif  /* __STRING_OPERATION_HPP__ */
