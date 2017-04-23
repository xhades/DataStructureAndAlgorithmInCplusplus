#ifndef __SEPARATE_CHAINING_HASHING_HPP__
#define __SEPARATE_CHAINING_HASHING_HPP__

#include "prime.hpp"

namespace separate_chaining {

template<typename T>
struct ListNode {
    T key;
    std::string content;
    struct ListNode<T> * next;

    ListNode(const T &k = 0x7fffffff, const std::string &c = "", struct ListNode<T> * ptr = nullptr)
        : key(k), content(c), next(ptr) 
    {
        // do something
    }
};

template<typename T>
class LinkedList {
public:
    LinkedList() {
        members = 0;
        head = new struct ListNode<T>;
    }

    ~LinkedList() {
        struct ListNode<T> * cur = head->next;
        struct ListNode<T> * cur_backup = nullptr;
        while (cur) {
            cur_backup = cur;
            cur = cur->next;
            delete cur_backup;
            members--;
        }

        head->next = nullptr;
    }

    void insert(const T &key, const std::string &content) {
        members++;

        struct ListNode<T> * node = new struct ListNode<T>(key, content, head->next);
        head->next = node;
    }

    std::string find(const T &key) {
        struct ListNode<T> * cur = head->next;

        while (cur) {
            if (cur->key == key) break;
            cur = cur->next;
        }

        if (cur != nullptr) {
            return cur->content;
        } else {
            return "[-] Can not find it in the HashTable";
        }
    }

    bool remove(const T &key) {
        bool is_remove = false;

        struct ListNode<T> * cur = head;
        while (cur->next) {
            if (cur->next->key == key) break;
            cur = cur->next;
        }
        struct ListNode<T> * cur_next = cur->next;
        cur->next = cur_next->next;
        delete cur_next;

        members--;

        return is_remove;
    }

    unsigned int size() {
        return members;
    }

    bool empty() {
        return members == 0 ? true : false;
    }

    void print(const unsigned int &index) {
        struct ListNode<T> * cur = head->next;
        std::cout << "< List " << index << std::endl;
        while (cur) {
            std::cout << "    " << cur->key << std::endl;
            cur = cur->next;
        }
        std::cout << ">" << std::endl;
    }

private:
    unsigned int members;
    struct ListNode<T> * head;
};

// load factory = 1 is the best
template<typename T>
class HashTable {
public:
    HashTable(const unsigned int &s = 100) {
        table_size = prime::prime(s);
        members = 0;
        table = new LinkedList<T> * [table_size];
        for (unsigned int i = 0; i < table_size; i++) {
            table[i] = new LinkedList<T>;
        }
    }

    ~HashTable() {
        for (unsigned int i = 0; i < table_size; i++) {
            delete table[i];
        }
        delete table;

        table_size = 0;
        members = 0;
    }

    void insert(const T &key, const std::string &content = "") {
        members++;

        table[hashing(key)]->insert(key, content);
    }

    void find(const T &key) {
        std::cout << table[hashing(key)]->find(key) << std::endl;
    }

    void remove(const T &key) {
        if (table[hashing(key)]->remove(key)) {
            members--;
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
            table[i]->print(i+1);
        }
    }

private:
    unsigned int table_size;
    unsigned int members;
    LinkedList<T> ** table;

    unsigned int hashing(const T &key) {
        return key % table_size;
    }
};

}

#endif  /* __SEPARATE_CHAINING_HASHING_HPP__ */
