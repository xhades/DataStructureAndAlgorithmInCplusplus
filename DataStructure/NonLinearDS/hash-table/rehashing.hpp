#ifndef __REHASHING_HPP__
#define __REHASHING_HPP__

#include <vector>
#include "prime.hpp"

namespace rehashing {

template<typename T>
struct HashTableElement {
    T key;
    std::string content;
    bool is_occupied;

    HashTableElement(const T &k = 0x7fffffff, const std::string &c = "")
        : key(k), content(c), is_occupied(false)
    {
        // do something
    }

    void operator = (const struct HashTableElement &e) {
        key = e.key;
        content = e.content;
        is_occupied = true;
    }
};

template<typename T>
class HashTable {
public:
    HashTable(const unsigned int &s = 100) {
        table_size = prime::prime(s);
        members = 0;
        table = new struct HashTableElement<T> * [table_size];
        for (unsigned int i = 0; i < table_size; i++) {
            table[i] = new struct HashTableElement<T>;
        }
    }

    ~HashTable() {
        table_size = 0;
        members = 0;
        for (unsigned int i = 0; i < table_size; i++) {
            delete table[i];
        }
        delete table;
    }

    void insert(const T &key, const std::string &content = "") {
        if (load_factory() >= 0.5) {
            rehashing();
        }

        members++;

        unsigned int hashing_value = hashing(key);
        if (table[hashing_value]->is_occupied) {
            quadratic_probing(hashing_value, key, content);
        } else {
            struct HashTableElement<T> element(key, content);
            *table[hashing_value] = element;
        }
    }

    std::string find(const T &key) {
         unsigned int hashing_value = hashing(key);
         
         unsigned int shift = 0;
         unsigned int i = 1;
         while (table[(hashing_value + shift)%table_size]->is_occupied && key != table[(hashing_value + shift)%table_size]->key) {
            i <<= 1;
            shift += (i - 1);
         }

         if (table[(hashing_value + shift)%table_size]->is_occupied && key == table[(hashing_value + shift)%table_size]->key) {
            return table[(hashing_value + shift)%table_size]->content;
         } else {
            return "[-] Can not find it in the HashTable";
         }
    }

    void remove(const T &key) {
         unsigned int hashing_value = hashing(key);
         
         unsigned int shift = 0;
         unsigned int i = 1;
         while (table[(hashing_value + shift)%table_size]->is_occupied && key != table[(hashing_value + shift)%table_size]->key) {
            i <<= 1;
            shift += (i - 1);
         }

         if (key == table[(hashing_value + shift)%table_size]->key) {
            table[(hashing_value + shift)%table_size]->is_occupied = false;
            members--;
         } else {
            std::cout << "[-] Can not find it in the HashTable" << std::endl;
         }
    }

    double load_factory() {
        return double(members) / table_size;
    }

    unsigned int size() {
        return members;
    }

    bool empty() {
        return members == 0 ? true : false;
    }

    void print() {
        for (unsigned int i = 0; i < table_size; i++) {
            if (table[i]->is_occupied) {
                std::cout << i << ": " << table[i]->key << std::endl;
            } else {
                std::cout << i << ": -" << std::endl;
            }
        }
    }

private:
    unsigned int table_size;
    unsigned int members;
    struct HashTableElement<T> ** table;

    unsigned int hashing(const T &key) {
        return key % table_size;
    }

    // F(i) = F(i - 1) + 2 * i - 1
    void quadratic_probing(const unsigned int &hashing_value, const T &key, const std::string &content) {
        unsigned int shift = 1;
        unsigned int i = 2;
        while (table[(hashing_value + shift)%table_size]->is_occupied) {
            i <<= 1;
            shift += (i - 1);
        }
        struct HashTableElement<T> element(key, content);
        *table[(hashing_value + shift)%table_size] = element;
    }

    unsigned int next_prime(unsigned int n) {
        unsigned int next_prime = n;

        bool is_not_find_next_prime = true;
        bool is_prime;
        unsigned int half;
        while (is_not_find_next_prime) {
            is_prime = true;

            next_prime = ++n;
            half = ceil(next_prime / 2);
            for (unsigned int i = 2; i < half; ++i) {
                if (next_prime % i == 0) {
                    is_prime = false;
                    break;
                }
            }

            if (is_prime) {
                is_not_find_next_prime = false;
            }
        }

        return next_prime;
    }

    void rehashing() {
        std::vector<struct HashTableElement<T> > elements;
        for (unsigned int i = 0; i < table_size; i++) {
            if (table[i]->is_occupied) elements.push_back(*(table[i]));
            delete table[i];
        }
        delete table;

        table_size = next_prime(table_size * 2);

        table = new struct HashTableElement<T> * [table_size];
        for (unsigned int i = 0; i < table_size; i++) {
            table[i] = new struct HashTableElement<T>;
        }

        typedef typename std::vector<struct HashTableElement<T> >::iterator iterator;
        unsigned int hashing_value;
        for (iterator it = elements.begin(); it != elements.end(); it++) {
            hashing_value = hashing(it->key);
            if (table[hashing_value]->is_occupied) {
                quadratic_probing(hashing_value, it->key, it->content);
            } else {
                *table[hashing_value] = *it;
            }
        }
    }
};

}

#endif  /* __REHASHING_HPP__ */
