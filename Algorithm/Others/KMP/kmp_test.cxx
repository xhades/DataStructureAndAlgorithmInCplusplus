#include <iostream>

#include "KMP.hpp"

int main (int argc, char ** argv) {
    KMP kmp;
    kmp.match("ABCDABD", "BBC ABCDAB ABCDABCDABDE FFAAABCDABDAADDAAABCDABDH SGAGASHJAABCDABDH JAHAHJAH");
}
