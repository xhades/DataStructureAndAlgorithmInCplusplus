#ifndef __OPEN_ADDRESSING_HASHING_HPP__
#define __OPEN_ADDRESSING_HASHING_HPP__

#include "prime.hpp"

// load factory <= 0.5 is the best
namespace open_addressing_hashing {

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

namespace linear_probing_hashing {

template<typename T>
class HashTable {
public:
    HashTable(const unsigned int &s = 20) {
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
        if (members > table_size/2) {
            std::cout << "[-] HashTable is full" << std::endl;
            return;
        }

        members++;

        unsigned int hashing_value = hashing(key);
        if (table[hashing_value]->is_occupied) {
            linear_probing(hashing_value, key, content);
        } else {
            struct HashTableElement<T> element(key, content);
            *table[hashing_value] = element;
        }
    }

    std::string find(const T &key) {
         unsigned int hashing_value = hashing(key);
         
         unsigned int i = 0;
         while (table[(hashing_value + i)%table_size]->is_occupied && i < table_size && key != table[(hashing_value + i)%table_size]->key) i++;

         if (table[(hashing_value + i)%table_size]->is_occupied) {
            if (i < table_size) {
                return table[(hashing_value + i)%table_size]->content;
            } else {
                return "[-] Can not find it in the HashTable";
            }
         } else {
            return "[-] Can not find it in the HashTable";
        }
    }

    void remove(const T &key) {
         unsigned int hashing_value = hashing(key);
         
         unsigned int i = 0;
         while (i < table_size && key != table[(hashing_value + i)%table_size]->key) i++;

         if (i < table_size) {
            table[(hashing_value + i)%table_size]->is_occupied = false;
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

    // F(i) = i
    void linear_probing(const unsigned int &hashing_value, const T &key, const std::string &content) {
        unsigned int i = 1;
        while (table[(hashing_value + i)%table_size]->is_occupied) i++;
        struct HashTableElement<T> element(key, content);
        *table[(hashing_value + i)%table_size] = element;
    }
};

}

namespace quadratic_probing_hashing {

template<typename T>
class HashTable {
public:
    HashTable(const unsigned int &s = 20) {
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
        if (members > table_size/2) {
            std::cout << "[-] HashTable is full" << std::endl;
            return;
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
};

}

namespace double_hashing {

template<typename T>
class HashTable {
public:
    HashTable(const unsigned int &s = 20) {
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
        if (members > table_size/2) {
            std::cout << "[-] HashTable is full" << std::endl;
            return;
        }

        members++;

        unsigned int hashing_value = hashing(key);
        if (table[hashing_value]->is_occupied) {
            double_hashing(hashing_value, key, content);
        } else {
            struct HashTableElement<T> element(key, content);
            *table[hashing_value] = element;
        }
    }

    std::string find(const T &key) {
         unsigned int hashing_value = hashing(key);
         
         unsigned int _R = prime::prime(table_size);
         unsigned int _Hash2 = _R - key%_R;

         unsigned int i = 0;
         while (table[(hashing_value + i * _Hash2)%table_size]->is_occupied && key != table[(hashing_value + i * _Hash2)%table_size]->key) i++;

         if (table[(hashing_value + i * _Hash2)%table_size]->is_occupied && key == table[(hashing_value + i * _Hash2)%table_size]->key) {
            return table[(hashing_value + i * _Hash2)%table_size]->content;
         } else {
            return "[-] Can not find it in the HashTable";
         }
    }

    void remove(const T &key) {
         unsigned int hashing_value = hashing(key);
         
         unsigned int _R = prime::prime(table_size);
         unsigned int _Hash2 = _R - key%_R;

         unsigned int i = 0;
         while (table[(hashing_value + i * _Hash2)%table_size]->is_occupied && key != table[(hashing_value + i * _Hash2)%table_size]->key) i++;

         if (key == table[(hashing_value + i * _Hash2)%table_size]->key) {
            table[(hashing_value + i * _Hash2)%table_size]->is_occupied = false;
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

    // F(i) = i * Hash2(X), Hash2(X) = R - (X mod R), R为小于TableSize的素数
    void double_hashing(const unsigned int &hashing_value, const T &key, const std::string &content) {
        unsigned int _R = prime::prime(table_size);
        unsigned int _Hash2 = _R - key%_R;

        unsigned int i = 1;
        while (table[(hashing_value + i * _Hash2)%table_size]->is_occupied) i++;
        struct HashTableElement<T> element(key, content);
        *table[(hashing_value + i * _Hash2)%table_size] = element;
    }
};

}

}

#endif  /* __OPEN_ADDRESSING_HASHING_HPP__ */
