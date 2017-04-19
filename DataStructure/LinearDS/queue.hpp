#ifndef __QUEUE_HPP__
#define __QUEUE_HPP__

#include <assert.h>
#include <iostream>

/* 单端队列 */
template<typename T>
class Queue {
public:
    Queue() {
        capacity = 10;
        members = 0;
        fron = 0;
        rear = capacity - 1;
        array = new T[capacity];
    }

    Queue(const Queue<T> &q) {}

    ~Queue() {
        delete array;
    }

    void operator = (const Queue<T> &q) {}

    void enqueue(const T &element) {
        assert(!full());

        rear++;
        rear %= capacity;
        array[rear] = element;

        members++;
    }

    T front() {
        assert(!empty());

        return array[fron];
    }

    void dequeue() {
        assert(!empty());

        fron++;
        fron %= capacity;
        members--;
    }

    unsigned int size() {
        return members;
    }

    bool full() {
        return members == capacity - 1 ? true : false;
    }

    bool empty() {
        return members == 0 ? true : false;
    }

private:
    unsigned int capacity;
    unsigned int members;
    unsigned int fron;
    unsigned int rear;
    T * array;
};

/* 双端队列 */
template<typename T>
class Dequeue {
public:
    Queue() {
        capacity = 10;
        members = 0;
        array = new T[capacity];
    }

    Queue(const Queue<T> &q) {}

    ~Queue() {
        delete array;
    }

    void operator = (const Queue<T> &q) {}

    void push(const T &element) {
    }

    void pop() {
    }

    void inject(const T &element) {
    }

    void eject() {
    }

    unsigned int size() {
        return members;
    }

    bool full() {
    }

    bool empty() {
        return members == 0 ? true : false;
    }

private:
    unsigned int capacity;
    unsigned int members;
    T * array;
};

#endif  /* __QUEUE_HPP__ */

