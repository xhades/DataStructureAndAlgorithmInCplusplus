#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <assert.h>
#include <iostream>

template<typename T>
struct ListNode {
    T value;
    struct ListNode<T> * next;

    ListNode() : next(nullptr) {}
    ListNode(const T &v, struct ListNode<T> * ptr=nullptr) : value(v), next(ptr) {}
    ~ListNode() {}
};

/* 单链表 */
template<typename T>
class LinkedList {
public:
    LinkedList() {
        members = 0;
        head = new struct ListNode<T>(0x7fffffff);
        cursor = head;
    }

    LinkedList(const LinkedList &object) {}

    ~LinkedList() {
        clear();
    }

    void operator = (const LinkedList &object) {}

    void append(const T &value) {
        members++;
        
        struct ListNode<T> * node = new struct ListNode<T>(value);
        cursor->next = node;
        cursor = node;
    }

    void insert(const unsigned int &position, const T &value) {
        assert(position <= members);

        members++;

        struct ListNode<T> * temp = head;
        unsigned int counter = 0;
        while (counter != position) {
            temp = temp->next;
            counter++;
        }

        struct ListNode<T> * node = new struct ListNode<T>(value, temp->next);
        temp->next = node;
    }

    void del(const unsigned int &position) {
        assert(position < members);

        struct ListNode<T> * temp = head;
        unsigned int counter = 0;
        while (counter != position) {
            temp = temp->next;
            counter++;
        }

        struct ListNode<T> * temp_next_next = temp->next->next;
        delete temp->next;
        temp->next = temp_next_next;

        members--;
    }

    struct ListNode<T> * find(const T &value) {
        struct ListNode<T> * temp = head->next;

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
        struct ListNode<T> * temp = head->next;
        struct ListNode<T> * temp_backup;
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

private:
    unsigned int members;
    struct ListNode<T> * head;
    struct ListNode<T> * cursor;
};
