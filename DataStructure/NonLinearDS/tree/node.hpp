#ifndef __NODE_HPP__
#define __NODE_HPP__

#include <vector>

#include <cassert>

/* node data structure for general tree */
template<typename T>
struct Node {
    T key;
    unsigned int repeat;
    struct Node<T> * parent;
    struct Node<T> * left;
    struct Node<T> * right;

    Node(
        const T &k, 
        struct Node<T> * p = nullptr, 
        struct Node<T> * l = nullptr, 
        struct Node<T> * r = nullptr) 
        : key(k), repeat(1), parent(p), left(l), right(r) {
        // do sth during initialization
    }
    ~Node() {
        // do sth during deletion
    }
    Node (const struct Node &n) {
        key = n.key;
        repeat = n.repreat;
    }
    void operator = (const struct Node &n) {
        key = n.key;
        repeat = n.repreat;
    }

    void add() {
        repeat++;
    }
};

/* node data structure for 2D-tree */
template<typename T>
struct Node_2D {
    T point[2];
    unsigned int split;  // 分割超平面序号
    unsigned int repeat;
    struct Node_2D<T> * left;
    struct Node_2D<T> * right;

    Node_2D(
        const T &x, 
        const T &y, 
        const unsigned int &s, 
        struct Node_2D<T> * l = nullptr, 
        struct Node_2D<T> * r = nullptr) 
        : split(s), repeat(1), left(l), right(r) {
        // do sth during initialization
        point[0] = x, point[1] = y;
    }
    ~Node_2D() {
        // do sth during deletion
    }
    Node_2D (const struct Node_2D &n) {
        point[0] = n.point[0], point[1] = n.point[1];
        split = n.split;
        repeat = n.repreat;
    }
    void operator = (const struct Node_2D &n) {
        point[0] = n.point[0], point[1] = n.point[1];
        split = n.split;
        repeat = n.repreat;
    }

    void add() {
        repeat++;
    }
};

/* node data structure for 3D-tree */
template<typename T>
struct Node_3D {
    T point[3];
    unsigned int split;  // 分割超平面序号
    unsigned int repeat;
    struct Node_3D<T> * left;
    struct Node_3D<T> * right;

    Node_3D(
        const T &x, 
        const T &y, 
        const T &z, 
        const unsigned int &s, 
        struct Node_3D<T> * p = nullptr, 
        struct Node_3D<T> * l = nullptr, 
        struct Node_3D<T> * r = nullptr) 
        : split(s), repeat(1), left(l), right(r) {
        // do sth during initialization
        point[0] = x, point[1] = y, point[2] = z;
    }
    ~Node_3D() {
        // do sth during deletion
    }
    Node_3D (const struct Node_3D &n) {
        point[0] = n.point[0], point[1] = n.point[1], point[2] = n.point[2];
        split = n.split;
        repeat = n.repreat;
    }
    void operator = (const struct Node_3D &n) {
        point[0] = n.point[0], point[1] = n.point[1], point[2] = n.point[2];
        split = n.split;
        repeat = n.repreat;
    }    

    void add() {
        repeat++;
    }
};

/* node data structure for KD-tree */
template<typename T>
struct Node_KD {
    T * point;
    unsigned int dim;
    unsigned int split;  // 分割超平面序号
    unsigned int repeat;
    struct Node_KD<T> * left;
    struct Node_KD<T> * right;

    Node_KD(
        const std::vector<T> vec,
        const unsigned int &d, 
        const unsigned int &s, 
        struct Node_KD<T> * p = nullptr, 
        struct Node_KD<T> * l = nullptr, 
        struct Node_KD<T> * r = nullptr) 
        : split(s), repeat(1), left(l), right(r) {
        // do sth during initialization
        assert(dim == vec.size());
        
        point = new T[dim];
        for (unsigned int i = 0; i < dim; i++) {
            point[i] = vec.at(i);
        }
    }
    ~Node_KD() {
        // do sth during deletion
        delete point;
    }
    Node_KD (const struct Node_KD &n) {
        assert(dim == n.dim);

        for (unsigned int i = 0; i < dim; i++) {
            point[i] = n.point[i];
        }
        split = n.split;
        repeat = n.repreat;
    }
    void operator = (const struct Node_KD &n) {
        assert(dim == n.dim);

        for (unsigned int i = 0; i < dim; i++) {
            point[i] = n.point[i];
        }
        split = n.split;
        repeat = n.repreat;
    }    

    void add() {
        repeat++;
    }
};

/* node data structure for red-black tree */
enum COLOR{RED, BLACK};

template<typename T>
struct Node_R_B {
    T key;
    COLOR color;
    unsigned int repeat;
    struct Node_R_B<T> * parent;
    struct Node_R_B<T> * left;
    struct Node_R_B<T> * right;

    Node_R_B(
        const T &k,
        const COLOR &c,
        struct Node_R_B<T> * p = nullptr, 
        struct Node_R_B<T> * l = nullptr, 
        struct Node_R_B<T> * r = nullptr) 
        : key(k), color(c), repeat(1), parent(p), left(l), right(r) {
        // do sth during initialization
    }
    ~Node_R_B() {
        // do sth during deletion
    }
    Node_R_B (const struct Node_R_B &n) {
        key = n.key;
        color = n.color;
        repeat = n.repreat;
    }
    void operator = (const struct Node_R_B &n) {
        key = n.key;
        color = n.color;
        repeat = n.repreat;
    }

    void add() {
        repeat++;
    }
};

#endif  /* __NODE_HPP__ */
