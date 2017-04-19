#ifndef __LINKED_LIST_HPP__
#define __LINKED_LIST_HPP__

#include <assert.h>
#include <iostream>
#include <stack>

template<typename T>
struct Node {
    T value;
    struct Node<T> * next;

    Node(const T &v, struct Node<T> * ptr=nullptr) : value(v), next(ptr) {}
    ~Node() {}
};

/* 单链表 */
template<typename T>
class LinkedList {
public:
    LinkedList() {
        members = 0;
        head = new struct Node<T>(0);
        cursor = head;
    }

    ~LinkedList() {
        clear();
    }

    void append(const T &value) {
        members++;
        
        struct Node<T> * node = new struct Node<T>(value);
        cursor->next = node;
        cursor = node;
    }

    void insert(const unsigned int &position, const T &value) {
        assert(position <= members);

        members++;

        struct Node<T> * temp = head;
        unsigned int counter = 0;
        while (counter != position) {
            temp = temp->next;
            counter++;
        }

        struct Node<T> * node = new struct Node<T>(value, temp->next);
        temp->next = node;
    }

    void del(const unsigned int &position) {
        assert(position < members);

        struct Node<T> * temp = head;
        unsigned int counter = 0;
        while (counter != position) {
            temp = temp->next;
            counter++;
        }

        struct Node<T> * temp_next = temp->next->next;
        delete temp->next;
        temp->next = temp_next;

        members--;
    }

    struct Node<T> * find(const T &value) {
        struct Node<T> * temp = head->next;

        while (temp) {
            if (temp->value == value) break;
            temp = temp->next;
        }

        return temp;
    }

    unsigned int size() {
        return members;
    }

    void clear() {
        struct Node<T> * temp = head->next;
        struct Node<T> * temp_backup;
        while (temp) {
            temp_backup = temp;
            temp = temp->next;
            delete temp_backup;
            members--;
        }

        if (empty()) {
            std::cout << ">> clear opration is successful." << std::endl;
        }

        head->next = nullptr;
        cursor = head;   
    }

    bool empty() {
        return members == 0 ? true : false;
    }

    void reverse() {
        std::stack<struct Node<T> *> s;

        struct Node<T> * temp = head->next;
        while (temp->next) {
            s.push(temp);
            temp = temp->next;
        }

        head->next = temp;
        while (!s.empty()) {
            temp->next = s.top();
            temp = s.top();
            s.pop();
        }
        temp->next = nullptr;
    }

    void print() {
        struct Node<T> * temp = head->next;
        while (temp) {
            std::cout << "[+] LinkedList -> " << temp->value << std::endl;
            temp = temp->next;
        }
    }

private:
    unsigned int members;
    struct Node<T> * head;
    struct Node<T> * cursor;
};

#endif /* __LINKED_LIST_HPP__ */

