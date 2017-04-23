#ifndef __HORNER_HASHING_HPP__
#define __HORNER_HASHING_HPP__

namespace HornerHashing{
    int accelerated_add(const int &a, const int &b) {
        return (a^b) + ((a&b) << 1);
    }

    unsigned int hash(const char * element, unsigned int table_size) {
        unsigned int hash_value = 0;

        while (*element != '\0') {
            hash_value = (hash_value << 5) + *element++;
        }

        return hash_value % table_size;
    }
}

#endif  /* __HORNER_HASHING_HPP__ */
