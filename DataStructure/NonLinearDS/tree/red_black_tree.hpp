#ifndef __RED_BLACK_TREE_HPP__
#define __RED_BLACK_TREE_HPP__

enum Color {RED, BLACK};

template<typename T>
struct RedBlackTreeNode {
    Color color;
    T key;
    RedBlackTreeNode *left;
    RedBlackTreeNode *right;
    RedBlackTreeNode *parent;
    RedBlackTreeNode(Color c, T k) : color(c), key(k), left(NULL), right(NULL), parent(NULL) {};
};

#endif  /* __RED_BLACK_TREE_HPP__ */
