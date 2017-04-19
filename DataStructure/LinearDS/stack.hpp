#ifndef __STACK_HPP__
#define __STACK_HPP__

#include <assert.h>
#include <iostream>

template<typename T>
class Stack {
public:
    Stack(unsigned int c = 1000) {
        capacity = c;
        members = 0;
        array = new T[capacity];
    }

    Stack(const Stack &s) {}

    ~Stack() {
        delete [] array;
    }

    void operator = (const Stack &s) {}

    void push(const T& element) {
        assert(!full());

        array[members] = element;
        members++;
    }

    T top() {
        assert(!empty());

        return array[members - 1];
    }

    void pop() {
        assert(!empty());

        members--;
    }

    unsigned int size() {
        return members;
    }

    bool empty() {
        return members == 0 ? true : false;
    }

    bool full() {
        return members == capacity ? true : false;
    }

private:
    unsigned int capacity;
    unsigned int members;
    T * array;
};

/****************************************/
template<typename T>
class DeStack {
public:
    DeStack(unsigned int c = 1000) {
        capacity = c;
        lmembers = 0;
        rmembers = 0;
        members = 0;
        array = new T[capacity];
    }

    DeStack(const DeStack &s) {}

    ~DeStack() {
        delete [] array;
    }

    void operator = (const DeStack &s) {}

    void lpush(const T& element) {
        assert(!full());

        array[lmembers] = element;
        lmembers++;
        members++;
    }

    T ltop() {
        assert(!lempty());

        return array[lmembers - 1];
    }

    void lpop() {
        assert(!lempty());

        lmembers--;
    }

    void rpush(const T& element) {
        assert(!full());

        array[capacity - 1 - rmembers] = element;
        rmembers++;
        members++;
    }

    T rtop() {
        assert(!rempty());

        return array[capacity - rmembers];
    }

    void rpop() {
        assert(!rempty());

        rmembers--;
    }

    unsigned int lsize() {
        return lmembers;
    }

    unsigned int rsize() {
        return rmembers;
    }

    unsigned int size() {
        return members;
    }

    bool lempty() {
        return lmembers == 0 ? true : false;
    }

    bool rempty() {
        return rmembers == 0 ? true : false;
    }

    bool full() {
        return members == capacity ? true : false;
    }

private:
    unsigned int capacity;
    unsigned int lmembers;
    unsigned int rmembers;
    unsigned int members;
    T * array;
};

/****************************************/
template<typename T>
class TeStack {
public:
    TeStack(unsigned int c = 1000) {
        capacity = c;
        members_1st = 0;
        members_2nd = 0;
        members_3rd = 0;
        members = 0;
        array = new T[capacity];
    }

    TeStack(const TeStack &s) {}

    ~TeStack() {
        delete [] array;
    }

    void operator = (const TeStack &s) {}

private:
    unsigned int capacity;
    unsigned int members_1st;
    unsigned int members_2nd;
    unsigned int members_3rd;
    unsigned int members;
    T * array;
};

/****************************************/
template<typename T>
struct StackNode {
    T element;
    struct StackNode<T> * next;

    StackNode() : next(nullptr) {}
    StackNode(const T &e, struct StackNode<T> * ptr=nullptr) : element(e), next(ptr) {}
    ~StackNode() {}
};

template<typename T>
class ElasticStack {
public:
    ElasticStack () {
        members = 0;
        head = new StackNode<T>;
    }

    ElasticStack (const ElasticStack  &s) {}

    ~ElasticStack () {
        delete head;
    }

    void operator = (const ElasticStack  &s) {}

    void push(const T& element) {
        struct StackNode<T> * node = new StackNode<T>(element, head->next);
        head->next = node;

        members++;
    }

    T top() {
        assert(!empty());

        return head->next->element;
    }

    void pop() {
        assert(!empty());

        struct StackNode<T> * temp = head->next;
        head->next = temp->next;
        delete temp;

        members--;
    }

    unsigned int size() {
        return members;
    }

    bool empty() {
        return members == 0 ? true : false;
    }

private:
    unsigned int members;
    struct StackNode<T> * head;
};

/****************************************/
template<typename T>
class MinStack {
public:
    MinStack(unsigned int c = 1000) {
        main_stack = new Stack<T>(c);
        auxiliary_stack = new Stack<T>(c);
    }

    MinStack(const MinStack &s) {}

    ~MinStack() {
    }

    void operator = (const MinStack &s) {}

    void push(const T &element) {
        assert(!main_stack->full());

        if (main_stack->empty()) {
            main_stack->push(element);
            auxiliary_stack->push(element);
        } else {
            if (element <= auxiliary_stack->top()) {
                auxiliary_stack->push(element);
            }
            main_stack->push(element);
        }
    }

    T top() {
        assert(!main_stack->empty());

        return main_stack->top();
    }

    void pop() {
        assert(!main_stack->empty());

        if (main_stack->top() == auxiliary_stack->top()) {
            auxiliary_stack->pop();
        }
        main_stack->pop();
    }

    T min() {
        assert(!auxiliary_stack->empty());

        return auxiliary_stack->top();
    }

    void delete_min() {
        ElasticStack<T> * temp_stack = new ElasticStack<T>;

        while (main_stack->top() != auxiliary_stack->top()) {
            temp_stack->push(main_stack->top());
            main_stack->pop();
        }
        main_stack->pop();
        auxiliary_stack->pop();

        while (!temp_stack->empty()) {
            main_stack->push(temp_stack->top());
            if (temp_stack->top() <= auxiliary_stack->top()) {
                auxiliary_stack->push(temp_stack->top());
            }
            temp_stack->pop();
        }

        delete temp_stack;
    }

    unsigned int size() {
        return main_stack->size();
    }

    bool empty() {
        return main_stack->empty() ? true : false;
    }

    bool full() {
        return main_stack->full() ? true : false;
    }

private:
    Stack<T> * main_stack;
    Stack<T> * auxiliary_stack;
};

/****************************************/
template<typename T>
class MaxStack {
public:
    MaxStack(unsigned int c = 1000) {
        main_stack = new Stack<T>(c);
        auxiliary_stack = new Stack<T>(c);
    }

    MaxStack(const MaxStack &s) {}

    ~MaxStack() {
    }

    void operator = (const MaxStack &s) {}

    void push(const T &element) {
        assert(!main_stack->full());

        if (main_stack->empty()) {
            main_stack->push(element);
            auxiliary_stack->push(element);
        } else {
            if (element >= auxiliary_stack->top()) {
                auxiliary_stack->push(element);
            }
            main_stack->push(element);
        }
    }

    T top() {
        assert(!main_stack->empty());

        return main_stack->top();
    }

    void pop() {
        assert(!main_stack->empty());

        if (main_stack->top() == auxiliary_stack->top()) {
            auxiliary_stack->pop();
        }
        main_stack->pop();
    }

    T max() {
        assert(!auxiliary_stack->empty());

        return auxiliary_stack->top();
    }

    void delete_max() {
        ElasticStack<T> * temp_stack = new ElasticStack<T>;

        while (main_stack->top() != auxiliary_stack->top()) {
            temp_stack->push(main_stack->top());
            main_stack->pop();
        }
        main_stack->pop();
        auxiliary_stack->pop();

        while (!temp_stack->empty()) {
            main_stack->push(temp_stack->top());
            if (temp_stack->top() >= auxiliary_stack->top()) {
                auxiliary_stack->push(temp_stack->top());
            }
            temp_stack->pop();
        }

        delete temp_stack;
    }

    unsigned int size() {
        return main_stack->size();
    }

    bool empty() {
        return main_stack->empty() ? true : false;
    }

    bool full() {
        return main_stack->full() ? true : false;
    }

private:
    Stack<T> * main_stack;
    Stack<T> * auxiliary_stack;
};

#endif /* __STACK_HPP__ */

