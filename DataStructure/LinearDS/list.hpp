#ifndef __LIST_HPP__
#define __LIST_HPP__

#include <assert.h>
#include <iostream>

template<typename T>
struct Node {
    T value;
    struct Node<T> * next;

    Node() : next(nullptr) {}
    Node(const T &v, struct Node<T> * ptr=nullptr) : value(v), next(ptr) {}
    ~Node() {}
};

template<typename T>
struct DoubleNode {
    T value;
    struct DoubleNode<T> * prev;
    struct DoubleNode<T> * next;

    DoubleNode() : prev(nullptr) ,next(nullptr) {}
    DoubleNode(const T &v=0, struct DoubleNode<T> * prev_ptr=nullptr, struct DoubleNode<T> * next_ptr=nullptr) : value(v), prev(prev_ptr) ,next(next_ptr) {}
    ~DoubleNode() {}
};

/* 单链表 */
template<typename T>
class LinkedList {
public:
    LinkedList(const T &value) {
        members = 0;
        head = new struct Node<T>(value);
        cursor = head;
    }

    LinkedList(const LinkedList &object) {}

    ~LinkedList() {
        clear();
    }

    void operator = (const LinkedList &object) {}

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

        struct Node<T> * temp_next_next = temp->next->next;
        delete temp->next;
        temp->next = temp_next_next;

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

    struct Node<T> * get_head() {
        return head;
    }

    T get_head_value() {
        return head->value;
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

    void print() {
        struct Node<T> * temp = head->next;
        while (temp) {
            std::cout << "[+] LinkedList -> " << temp->value << std::endl;
            temp = temp->next;
        }
    }

    void swap(const unsigned int &position) {
        assert(position < members);
        assert(position > 0);

        struct Node<T> * temp = head;
        unsigned int counter = 0;
        while (counter != position - 1) {
            temp = temp->next;
            counter++;
        }

        struct Node<T> * temp1 = temp->next;
        struct Node<T> * temp2 = temp->next->next;

        temp->next = temp2;
        temp1->next = temp2->next;
        temp2->next = temp1;
    }

private:
    unsigned int members;
    struct Node<T> * head;
    struct Node<T> * cursor;
};

/* 双链表 */
template<typename T>
class DoubleLinkedList {
public:
    DoubleLinkedList() {
        members = 0;
        head = new struct DoubleNode<T>();
        tail = new struct DoubleNode<T>();
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
        
        struct DoubleNode<T> * node = new struct DoubleNode<T>(value, cursor, tail);
        cursor->next = node;
        tail->prev = node;
        cursor = node;
    }

    void insert(const unsigned int &position, const T &value) {
        assert(position <= members);

        members++;

        struct DoubleNode<T> * temp = head;
        unsigned int counter = 0;
        while (counter != position) {
            temp = temp->next;
            counter++;
        }

        struct DoubleNode<T> * node = new struct DoubleNode<T>(value, temp, temp->next);
        struct DoubleNode<T> * temp_next = temp->next;
        temp->next = node;
        temp_next->prev = node;
    }

    void del(const unsigned int &position) {
        assert(position <= members);
        assert(position > 0);

        struct DoubleNode<T> * temp = head->next;
        unsigned int counter = 1;
        while (counter != position) {
            temp = temp->next;
            counter++;
        }

        struct DoubleNode<T> * temp_prev = temp->prev;
        struct DoubleNode<T> * temp_next = temp->next;
        temp_prev->next = temp_next;
        temp_next->prev = temp_prev;
        delete temp;

        members--;
    }

    struct DoubleNode<T> * find(const T &value) {
        struct DoubleNode<T> * temp = head->next;

        while (temp->next) {
            if (temp->value == value) break;
            temp = temp->next;
        }

        return temp->next == nullptr ? temp->next : temp;
    }

    struct DoubleNode<T> * get_head() {
        return head;
    }

    struct DoubleNode<T> * get_tail() {
        return tail;
    }

    unsigned int size() {
        return members;
    }

    void clear() {
        struct DoubleNode<T> * temp = head->next;
        struct DoubleNode<T> * temp_backup;
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
        struct DoubleNode<T> * temp = head->next;
        while (temp->next) {
            std::cout << "[+] LinkedList -> " << temp->value << std::endl;
            temp = temp->next;
        }
    }

    void reverse_print() {
        struct DoubleNode<T> * temp = tail->prev;
        while (temp->prev) {
            std::cout << "[+] LinkedList -> " << temp->value << std::endl;
            temp = temp->prev;
        }
    }

    void swap(const unsigned int &position) {
        assert(position < members);
        assert(position > 0);

        struct DoubleNode<T> * temp = head->next;
        unsigned int counter = 1;
        while (counter != position) {
            temp = temp->next;
            counter++;
        }

        struct DoubleNode<T> * temp1 = temp->prev;
        struct DoubleNode<T> * temp2 = temp->next;
        struct DoubleNode<T> * temp3 = temp->next->next;

        temp1->next = temp2;
        temp2->prev = temp1;
        temp2->next = temp;
        temp->prev = temp2;
        temp->next = temp3;
        temp3->prev = temp;
    }

private:
    unsigned int members;
    struct DoubleNode<T> * head;
    struct DoubleNode<T> * tail;
    struct DoubleNode<T> * cursor;
};

template<typename T>
struct LazyNode {
    T value;
    bool is_delete;
    struct LazyNode<T> * next;

    LazyNode() : next(nullptr) {}
    LazyNode(const T &v, struct LazyNode<T> * ptr=nullptr) : value(v), is_delete(false), next(ptr) {}
    ~LazyNode() {}
};

/* 带惰性删除功能的单链表 */
template<typename T>
class LazyLinkedList {
public:
    LazyLinkedList(const T &value) {
        members = 0;
        deleted_members = 0;
        head = new struct LazyNode<T>(value);
        cursor = head;
    }

    LazyLinkedList(const LazyLinkedList &object) {}

    ~LazyLinkedList() {
        clear();
    }

    void operator = (const LazyLinkedList &object) {}

    void append(const T &value) {
        members++;
        
        struct LazyNode<T> * node = new struct LazyNode<T>(value);
        cursor->next = node;
        cursor = node;
    }

    void insert(const unsigned int &position, const T &value) {
        assert(position <= members);

        members++;

        struct LazyNode<T> * temp = head;
        unsigned int counter = 0;
        while (counter != position) {
            temp = temp->next;
            counter++;
        }

        struct LazyNode<T> * node = new struct LazyNode<T>(value, temp->next);
        temp->next = node;
    }

    void del(const unsigned int &position) {
        assert(position < members);

        struct LazyNode<T> * temp = head;
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
                    struct LazyNode<T> * temp_next_next = temp->next->next;
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

    struct LazyNode<T> * find(const T &value) {
        struct LazyNode<T> * temp = head->next;

        while (temp) {
            if (temp->value == value) break;
            temp = temp->next;
        }

        return temp;
    }

    struct LazyNode<T> * get_head() {
        return head;
    }

    T get_head_value() {
        return head->value;
    }

    unsigned int size() {
        return members - deleted_members;
    }

    void clear() {
        struct LazyNode<T> * temp = head->next;
        struct LazyNode<T> * temp_backup;
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
        struct LazyNode<T> * temp = head->next;
        while (temp) {
            std::cout << "[+] LinkedList -> " << temp->value << std::endl;
            temp = temp->next;
        }
    }

private:
    unsigned int members;
    unsigned int deleted_members;
    struct LazyNode<T> * head;
    struct LazyNode<T> * cursor;
};

#endif  /* __LIST_HPP__ */

