#ifndef __CYCLE_LINKED_LIST_HPP__
#define __CYCLE_LINKED_LIST_HPP__

template<typename T>
struct Node {
    T value;
    struct Node<T> * next;

    Node(const T &v, struct Node<T> * ptr=nullptr) : value(v), next(ptr) {}
    ~Node() {}
};

/* 循环链表 */
template<typename T>
class CycleLinkedList {
public:
    CycleLinkedList(const T &value) {
        members = 1;
        head = new struct Node<T>(value);
        cursor = head;
    }

    ~CycleLinkedList() {
        clear();
    }

    void append(const T &value) {
        members++;
        
        struct Node<T> * node = new struct Node<T>(value, head);
        cursor->next = node;
        cursor = node;
        travel = cursor;
    }

    void del() {
        struct Node<T> * temp = travel->next;
        travel->next = temp->next;
        delete temp;

        members--;
    }

    void next() {
        travel = travel->next;
    }

    T value() {
        return travel->next->value;
    }

    unsigned int size() {
        return members;
    }

    void clear() {
        members = 0;
        delete head;
    }

    bool empty() {
        return members == 0 ? true : false;
    }

private:
    unsigned int members;
    struct Node<T> * head;
    struct Node<T> * cursor;
    struct Node<T> * travel;
};

#endif  /* __CYCLE_LINKED_LIST_HPP__ */
