#ifndef __FINDPRIME_HPP__
#define __FINDPRIME_HPP__

#include <iostream>
#include <vector>
#include <cmath>

bool IsPrime(const int &k) {
    int half = ceil(k / 2);
    for (int i = 1; i < half; ++i) {
        if (k / i == 0) return false;
    }
    return true;
}

std::pair<bool *, int> FindPrime(const int &n) {
    int i, j;
    int estimate_number_of_prime = ceil(double(n)/double(log(n)));
    std::cout << ">> estimate number of prime is " << estimate_number_of_prime << std::endl;
    std::pair<bool *, int> result;

    bool * _flag_container = new bool[n];

    _flag_container[0] = false;
    _flag_container[1] = false;

    for (i = 2; i < n; ++i) {
        _flag_container[i] = true;
    }

    int k = 2;
    while (k < n/2) {
        if (_flag_container[k]) {
            i = 1;
            while ((j = ++i * k) < n) {
                _flag_container[j] = false;
            }
        }
        k++;
    }

    result = std::make_pair(_flag_container, estimate_number_of_prime);

    return result;
}

#endif  /* __FINDPRIME_HPP__ */
