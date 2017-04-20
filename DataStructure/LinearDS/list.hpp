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

template<typename T>
struct DoubleListNode {
    T value;
    struct DoubleListNode<T> * prev;
    struct DoubleListNode<T> * next;

    DoubleListNode() : prev(nullptr) ,next(nullptr) {}
    DoubleListNode(const T &v=0, struct DoubleListNode<T> * prev_ptr=nullptr, struct DoubleListNode<T> * next_ptr=nullptr) : value(v), prev(prev_ptr) ,next(next_ptr) {}
    ~DoubleListNode() {}
};

/* 单链表 */
template<typename T>
class LinkedList {
public:
    LinkedList(const T &value) {
        members = 0;
        head = new struct ListNode<T>(value);
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

    struct ListNode<T> * get_head() {
        return head;
    }

    T get_head_value() {
        return head->value;
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

    void print() {
        struct ListNode<T> * temp = head->next;
        while (temp) {
            std::cout << "[+] LinkedList -> " << temp->value << std::endl;
            temp = temp->next;
        }
    }

    void swap(const unsigned int &position) {
        assert(position < members);
        assert(position > 0);

        struct ListNode<T> * temp = head;
        unsigned int counter = 0;
        while (counter != position - 1) {
            temp = temp->next;
            counter++;
        }

        struct ListNode<T> * temp1 = temp->next;
        struct ListNode<T> * temp2 = temp->next->next;

        temp->next = temp2;
        temp1->next = temp2->next;
        temp2->next = temp1;
    }

private:
    unsigned int members;
    struct ListNode<T> * head;
    struct ListNode<T> * cursor;
};

/* 双链表 */
template<typename T>
class DoubleLinkedList {
public:
    DoubleLinkedList() {
        members = 0;
        head = new struct DoubleListNode<T>();
        tail = new struct DoubleListNode<T>();
        head->next = tail;
        tail->prev = head;
        cursor = head;
    }

    DoubleLinkedList(const DoubleLinkedList &object) {}

    ~DoubleLinkedList() {
        clear();
    }

    void operator = (const DoubleLinkedList &object) {}

    void append(const T &value) {
        members++;
        
        struct DoubleListNode<T> * node = new struct DoubleListNode<T>(value, cursor, tail);
        cursor->next = node;
        tail->prev = node;
        cursor = node;
    }

    void insert(const unsigned int &position, const T &value) {
        assert(position <= members);

        members++;

        struct DoubleListNode<T> * temp = head;
        unsigned int counter = 0;
        while (counter != position) {
            temp = temp->next;
            counter++;
        }

        struct DoubleListNode<T> * node = new struct DoubleListNode<T>(value, temp, temp->next);
        struct DoubleListNode<T> * temp_next = temp->next;
        temp->next = node;
        temp_next->prev = node;
    }

    void del(const unsigned int &position) {
        assert(position <= members);
        assert(position > 0);

        struct DoubleListNode<T> * temp = head->next;
        unsigned int counter = 1;
        while (counter != position) {
            temp = temp->next;
            counter++;
        }

        struct DoubleListNode<T> * temp_prev = temp->prev;
        struct DoubleListNode<T> * temp_next = temp->next;
        temp_prev->next = temp_next;
        temp_next->prev = temp_prev;
        delete temp;

        members--;
    }

    struct DoubleListNode<T> * find(const T &value) {
        struct DoubleListNode<T> * temp = head->next;

        while (temp->next) {
            if (temp->value == value) break;
            temp = temp->next;
        }

        return temp->next == nullptr ? temp->next : temp;
    }

    struct DoubleListNode<T> * get_head() {
        return head;
    }

    struct DoubleListNode<T> * get_tail() {
        return tail;
    }

    unsigned int size() {
        return members;
    }

    void clear() {
        struct DoubleListNode<T> * temp = head->next;
        struct DoubleListNode<T> * temp_backup;
        while (temp->next) {
            temp_backup = temp;
            head->next = temp->next;
            delete temp_backup;
            temp = temp->next;
            members--;
        }

        if (empty()) {
            std::cout << ">> clear opration is successful." << std::endl;
        }

        head->next = tail;
        tail->prev = head;
        cursor = head;
    }

    bool empty() {
        return members == 0 ? true : false;
    }

    void print() {
        struct DoubleListNode<T> * temp = head->next;
        while (temp->next) {
            std::cout << "[+] LinkedList -> " << temp->value << std::endl;
            temp = temp->next;
        }
    }

    void reverse_print() {
        struct DoubleListNode<T> * temp = tail->prev;
        while (temp->prev) {
            std::cout << "[+] LinkedList -> " << temp->value << std::endl;
            temp = temp->prev;
        }
    }

    void swap(const unsigned int &position) {
        assert(position < members);
        assert(position > 0);

        struct DoubleListNode<T> * temp = head->next;
        unsigned int counter = 1;
        while (counter != position) {
            temp = temp->next;
            counter++;
        }

        struct DoubleListNode<T> * temp1 = temp->prev;
        struct DoubleListNode<T> * temp2 = temp->next;
        struct DoubleListNode<T> * temp3 = temp->next->next;

        temp1->next = temp2;
        temp2->prev = temp1;
        temp2->next = temp;
        temp->prev = temp2;
        temp->next = temp3;
        temp3->prev = temp;
    }

private:
    unsigned int members;
    struct DoubleListNode<T> * head;
    struct DoubleListNode<T> * tail;
    struct DoubleListNode<T> * cursor;
};

template<typename T>
struct LazyListNode {
    T value;
    bool is_delete;
    struct LazyListNode<T> * next;

    LazyListNode() : next(nullptr) {}
    LazyListNode(const T &v, struct LazyListNode<T> * ptr=nullptr) : value(v), is_delete(false), next(ptr) {}
    ~LazyListNode() {}
};

/* 带惰性删除功能的单链表 */
template<typename T>
class LazyLinkedList {
public:
    LazyLinkedList(const T &value) {
        members = 0;
        deleted_members = 0;
        head = new struct LazyListNode<T>(value);
        cursor = head;
    }

    LazyLinkedList(const LazyLinkedList &object) {}

    ~LazyLinkedList() {
        clear();
    }

    void operator = (const LazyLinkedList &object) {}

    void append(const T &value) {
        members++;
        
        struct LazyListNode<T> * node = new struct LazyListNode<T>(value);
        cursor->next = node;
        cursor = node;
    }

    void insert(const unsigned int &position, const T &value) {
        assert(position <= members);

        members++;

        struct LazyListNode<T> * temp = head;
        unsigned int counter = 0;
        while (counter != position) {
            temp = temp->next;
            counter++;
        }

        struct LazyListNode<T> * node = new struct LazyListNode<T>(value, temp->next);
        temp->next = node;
    }

    void del(const unsigned int &position) {
        assert(position < members);

        struct LazyListNode<T> * temp = head;
        unsigned int counter = 0;
        while (counter != position) {
            temp = temp->next;
            counter++;
        }

        temp->next->is_delete = true;

        deleted_members++;

        if (deleted_members == members/2 + 1) {
            temp = head;
            std::cout << ">> execute lazy deletion" << std::endl;
            while (temp->next) {
                if (temp->next->is_delete) {
                    struct LazyListNode<T> * temp_next_next = temp->next->next;
                    delete temp->next;
                    temp->next = temp_next_next;
                } else {
                    temp = temp->next;
                }
            }
            std::cout << ">> done lazy deletion" << std::endl;
            members -= deleted_members;
            deleted_members = 0;
        }
    }

    struct LazyListNode<T> * find(const T &value) {
        struct LazyListNode<T> * temp = head->next;

        while (temp) {
            if (temp->value == value) break;
            temp = temp->next;
        }

        return temp;
    }

    struct LazyListNode<T> * get_head() {
        return head;
    }

    T get_head_value() {
        return head->value;
    }

    unsigned int size() {
        return members - deleted_members;
    }

    void clear() {
        struct LazyListNode<T> * temp = head->next;
        struct LazyListNode<T> * temp_backup;
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

    void print() {
        struct LazyListNode<T> * temp = head->next;
        while (temp) {
            std::cout << "[+] LinkedList -> " << temp->value << std::endl;
            temp = temp->next;
        }
    }

private:
    unsigned int members;
    unsigned int deleted_members;
    struct LazyListNode<T> * head;
    struct LazyListNode<T> * cursor;
};

#endif  /* __LIST_HPP__ */

