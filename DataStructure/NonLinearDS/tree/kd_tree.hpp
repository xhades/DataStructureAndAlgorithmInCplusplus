#ifndef __KD_TREE_HPP__
#define __KD_TREE_HPP__

#include <algorithm>
#include <sstream>
#include <vector>
#include <stack>

#include <cstdio>
#include <cmath>

#include "node.hpp"

template<typename T>
class KDTree {
public:
    KDTree(unsigned int d=3) {
        nodes = 0;
        dim = d;
        init_split = 0;
        root = nullptr;
    }
    KDTree(const KDTree<T> &tree) {}
    ~KDTree() {
        clear();
    }
    void operator = (const KDTree<T> &tree) {}

    struct Node_3D<T> * build(T * spatial_data[], const unsigned int &points) {
        init(spatial_data, points);

        for (unsigned int i = 0; i < points; i++) {
            add(spatial_data[i]);
            nodes++;
        }

        return root;
    }

    void add(T point[]) {
        root = insert(point, root, init_split);
    }

    void remove() {

    }

    bool find(T point[]) {
        struct Node_3D<T> * temp = root;

        std::cout << "[+] search [" << point[0] << ", " << point[1] << ", " << point[2] << "] in the KD-Tree ... " << std::endl;

        bool is_find = false;
        while (temp) {
            if (point[0] == temp->point[0] && point[1] == temp->point[1] && point[2] == temp->point[2]) {
                is_find = true;
                break;
            } else {
                if (point[temp->split] <= temp->point[temp->split]) {
                    temp = temp->left;
                } 
                else if (point[temp->split] > temp->point[temp->split]) {
                    temp = temp->right;
                }
            }
        }

        if (is_find) {
            std::cout << "[+] [" << point[0] << ", " << point[1] << ", " << point[2] << "] is inside the KD-Tree." << std::endl;
        } else {
            std::cout << "[-] [" << point[0] << ", " << point[1] << ", " << point[2] << "] is not inside the KD-Tree." << std::endl;
        }

        return is_find;
    }

    void find_knn(T point[], const unsigned int &k = 1) {
        struct Node_3D<T> * knn;

        std::cout << "[+] search [" << point[0] << ", " << point[1] << ", " << point[2] << "]'s KNN in the KD-Tree ... " << std::endl;

        if (root != nullptr) {
            std::stack<std::pair<struct Node_3D<T> *, char> > s;
            
            struct Node_3D<T> * temp = root;
            std::pair<struct Node_3D<T> *, char> p;
            while (temp) {
                if (point[temp->split] <= temp->point[temp->split]) {
                    p = std::make_pair(temp, 'l');
                    temp = temp->left;
                } 
                else if (point[temp->split] > temp->point[temp->split]) {
                    p = std::make_pair(temp, 'r');
                    temp = temp->right;
                }
                s.push(p);
            }

            double dist = 0.0;
            double best_dist = 0.0;
            double axis_dist = 0.0;
            std::pair<struct Node_3D<T> *, char> p_temp;

            p_temp = s.top();
            s.pop();
            dist = sqrt((point[0] - p_temp.first->point[0]) * (point[0] - p_temp.first->point[0]) + \
            (point[1] - p_temp.first->point[1]) * (point[1] - p_temp.first->point[1]) + \
            (point[2] - p_temp.first->point[2]) * (point[2] - p_temp.first->point[2]));
            knn = p_temp.first;
            best_dist = dist;
            while (!s.empty()) {
                p_temp = s.top();
                s.pop();

                axis_dist = abs(p_temp.first->point[p_temp.first->split] - point[p_temp.first->split]);
                if (axis_dist < dist) {
                    if (p_temp.second == 'l') {
                        temp = p_temp.first->right;
                    } 
                    else if (p_temp.second == 'r') {
                        temp = p_temp.first->left;
                    }

                    while (temp) {
                        if (point[temp->split] <= temp->point[temp->split]) {
                            p = std::make_pair(temp, 'l');
                            temp = temp->left;
                        } 
                        else if (point[temp->split] > temp->point[temp->split]) {
                            p = std::make_pair(temp, 'r');
                            temp = temp->right;
                        }
                        s.push(p);
                    }

                    dist = sqrt((point[0] - p_temp.first->point[0]) * (point[0] - p_temp.first->point[0]) + \
                    (point[1] - p_temp.first->point[1]) * (point[1] - p_temp.first->point[1]) + \
                    (point[2] - p_temp.first->point[2]) * (point[2] - p_temp.first->point[2]));
                    if (dist < best_dist) {
                        best_dist = dist;
                        knn = p_temp.first;
                    }
                }
            }

            std::cout << "[+] KNN is (" << knn->point[0] << ", " << knn->point[1] << ", " << knn->point[2] << ")" << std::endl; 
            std::cout << "[+] KNN'diantance is " << best_dist << std::endl;
        }
    }

    bool is_empty() {
        return nodes == 0 ? true : false;
    }

    unsigned int size() {
        return nodes;
    }

    void graphviz() {
        FILE * fp;
        fp = fopen("kdtree.dot", "w+");
        if (fp != nullptr) {
            fprintf(fp, "digraph G {\n");
            fprintf(fp, "    label = \"KD Tree\";\n");
            fprintf(fp, "    node [shape = record, color = black];\n");
            std::stringstream ss;
            ss << root->point[0] << ", " << root->point[1] << ", " << root->point[2] << " (" << root->split << ", " << root->repeat << ")";
            fprintf(fp, "    <%d, %d, %d>[label = \"<f0> | <f1> %s | <f2> \"];\n", root->point[0], root->point[1], root->point[2], ss.str().c_str());
            fprint_tree(root, fp);
            fprintf(fp, "}\n");
            fclose(fp);
        } else {
            std::cout << "[-] can not open file!" << std::endl;
        }
    }

    void clear() {
        delete_nodes(root);
        std::cout << "[+] delete KD-Tree object from the memory page." << std::endl;
    }

private:
    unsigned int nodes;
    unsigned int dim;
    unsigned int init_split;
    struct Node_3D<T> * root;

    void init(T * spatial_data[], const unsigned int &points) {
        double sumX = 0.0, sumY = 0.0, sumZ = 0.0;
        double meanX, meanY, meanZ;
        double stdevX, stdevY, stdevZ;
        double stdevMax;

        for (unsigned int i = 0; i < points; i++) {
            sumX += spatial_data[i][0], sumY += spatial_data[i][1], sumZ += spatial_data[i][2];
        }

        meanX = sumX / points, meanY = sumY / points, meanZ = sumZ / points;

        for (unsigned int i = 0; i < points; i++) {
            sumX += (spatial_data[i][0] - meanX) * (spatial_data[i][0] - meanX);
            sumY += (spatial_data[i][1] - meanY) * (spatial_data[i][1] - meanY);
            sumZ += (spatial_data[i][2] - meanZ) * (spatial_data[i][2] - meanZ);
        }

        stdevX = sqrt(sumX / (points - 1)), stdevY = sqrt(sumY / (points - 1)), stdevZ = sqrt(sumZ / (points - 1));
        
        if (stdevX > stdevY) {
            init_split = 0;
            stdevMax = stdevX;
        } else {
            init_split = 1;
            stdevMax = stdevY;
        }
        if (stdevMax < stdevZ) {
            init_split = 2;
        }
    }

    struct Node_3D<T> * insert(T point[], struct Node_3D<T> * ptr, unsigned int level) {
        if (ptr == nullptr) {
            ptr = new struct Node_3D<T>(point[0], point[1], point[2], level%3);
        } else {
            if (point[0] == ptr->point[0] && point[1] == ptr->point[1] && point[2] == ptr->point[2]) {
                ptr->add();
            } else {
                unsigned int which_level = level % 3;

                if (point[which_level] <= ptr->point[which_level]) {
                    ptr->left = insert(point, ptr->left, level + 1);
                }
                else if (point[which_level] > ptr->point[which_level]) {
                    ptr->right = insert(point, ptr->right, level + 1);
                }
            }
        }

        return ptr;
    }

    void fprint_tree(struct Node_3D<T> * node, FILE * fp) {
        if (node == nullptr) return;

        if (node->left != nullptr) {
            std::stringstream ss;
            ss << node->left->point[0] << ", " << node->left->point[1] << ", " << node->left->point[2] << " (" << node->left->split << ", " << node->left->repeat << ")";
            fprintf(fp, "    <%d, %d, %d>[label = \"<f0> | <f1> %s | <f2> \"];\n", node->left->point[0], node->left->point[1], node->left->point[2], ss.str().c_str());
            fprintf(fp, "    <%d, %d, %d>:f0 -> <%d, %d, %d>:f1;\n", node->point[0], node->point[1], node->point[2], node->left->point[0], node->left->point[1], node->left->point[2]);
        }
        if (node->right != nullptr) {
            std::stringstream ss;
            ss << node->right->point[0] << ", " << node->right->point[1] << ", " << node->right->point[2] << " (" << node->right->split << ", " << node->right->repeat << ")";
            fprintf(fp, "    <%d, %d, %d>[label = \"<f0> | <f1> %s | <f2> \"];\n", node->right->point[0], node->right->point[1], node->right->point[2], ss.str().c_str());
            fprintf(fp, "    <%d, %d, %d>:f2 -> <%d, %d, %d>:f1;\n", node->point[0], node->point[1], node->point[2], node->right->point[0], node->right->point[1], node->right->point[2]);
        }   
        fprint_tree(node->left, fp);
        fprint_tree(node->right, fp);
    }

    void delete_nodes(struct Node_3D<T> * node) {
        if (node == nullptr) return;
        delete_nodes(node->left);
        delete_nodes(node->right);
        delete node;
        nodes--;
    }
};

#endif  /* __KD_TREE_HPP__ */
