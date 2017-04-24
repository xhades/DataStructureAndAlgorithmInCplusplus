#ifndef __PRIME_HPP__
#define __PRIME_HPP__

#include <cmath>

namespace prime {

bool is_prime(const unsigned int &k) {
    unsigned int half = ceil(k / 2);
    for (unsigned int i = 2; i < half; ++i) {
        if (k % i == 0) return false;
    }
    return true;
}

unsigned int prime(const unsigned int &n) {
    bool * flag_container = new bool[n];

    flag_container[0] = false;
    flag_container[1] = false;

    for (unsigned int i = 2; i < n; ++i) {
        flag_container[i] = true;
    }

    unsigned int i, j;
    unsigned int k = 2;
    while (k < n/2) {
        if (flag_container[k]) {
            i = 1;
            while ((j = ++i * k) < n) {
                flag_container[j] = false;
            }
        }
        k++;
    }

    unsigned int prime = 0;

    for (unsigned int i = 2; i < n; ++i) {
        if (flag_container[i]) {
            prime = i;
        }
    }

    return prime;
}

}

#endif  /* __PRIME_HPP__ */
