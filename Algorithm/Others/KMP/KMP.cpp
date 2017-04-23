#include "KMP.hpp"

extern "C" {
    KMP kmp;

    void match(char * str_1, char * str_2) {
        std::string patterm(str_1);
        std::string document(str_2);
        kmp.match(patterm, document);
    }
}
