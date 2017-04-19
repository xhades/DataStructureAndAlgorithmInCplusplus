#ifndef __NODE_HPP__
#define __NODE_HPP__

template<typename T>
struct Node {
    T key;
    unsigned int counter;
    struct Node<T> * parent;
    struct Node<T> * left;
    struct Node<T> * right;
    Node(const T &k, struct Node<T> * p = nullptr, struct Node<T> * l = nullptr, struct Node<T> * r = nullptr) 
        : key(k), counter(1), parent(p), left(l), right(r) {}
    ~Node() {}
    void overlay() {
        counter++;
    }
};

template<typename T>
struct Node2D {
    T point[2];
    unsigned int split;
    unsigned int counter;
    struct Node2D<T> * left;
    struct Node2D<T> * right;
    Node2D(const T &x, const T &y, const unsigned int &s, struct Node2D<T> * l = nullptr, struct Node2D<T> * r = nullptr) 
        : split(s), counter(1), left(l), right(r) {
            point[0] = x;
            point[1] = y;
        }
    ~Node2D() {}
    void overlay() {
        counter++;
    }
};

template<typename T>
struct Node3D {
    T point[3];
    unsigned int split;
    unsigned int counter;
    struct Node3D<T> * left;
    struct Node3D<T> * right;
    Node3D(const T &x, const T &y, const T &z, const unsigned int &s, struct Node3D<T> * p = nullptr, struct Node3D<T> * l = nullptr, struct Node3D<T> * r = nullptr) 
        : split(s), counter(1), left(l), right(r) {
            point[0] = x;
            point[1] = y;
            point[2] = z;
        }
    ~Node3D() {}
    void overlay() {
        counter++;
    }
};

#endif  /* __NODE_HPP__ */
