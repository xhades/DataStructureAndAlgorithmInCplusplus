/*************************************************************************
	> File Name: sort_algorithm.hpp
	> Author: summy
	> Mail: summychou@gmail.com 
 ************************************************************************/

#ifndef SORT_ALGORITHM_HPP
#define SORT_ALGORITHM_HPP

#include <iostream>
#include <typeinfo>
#include <vector>

#include "custom_data_structure.hpp"

template <typename T>
void print_item(const T& item) {
	std::cout << "[+] >> " << item << std::endl;
}

template <typename T>
void in_place_swap(T& a, T& b) {
	a = a ^ b;
	b = a ^ b;
	a = a ^ b;
}

template<typename T>
void insertion_sort(std::vector<T>& unsorted_vector) {
	if (typeid(int) == typeid(T) || typeid(float) == typeid(T) || typeid(double) == typeid(T)) {
		for (typename std::vector<T>::iterator it_outer = unsorted_vector.begin() + 1; it_outer != unsorted_vector.end(); ++it_outer) {
			typename std::vector<T>::iterator it_temp = it_outer;
			for (typename std::vector<T>::reverse_iterator it_inner(it_outer); it_inner != unsorted_vector.rend(); ++it_inner) {
				if (*it_temp < *it_inner) {
					in_place_swap(*it_temp, *it_inner);
					it_temp--;
				} else {
					break;
				}
			}
		}
	} else {
		std::cout << "[-] given unsupported type..." << std::endl;
	}
}

template<typename T>
void insertion_sort(LinkListNode<T> *unsorted_link_list_head) {
	if (typeid(int) == typeid(T) || typeid(float) == typeid(T) || typeid(double) == typeid(T)) {
		LinkListNode<T> *it = unsorted_link_list_head -> next;
		LinkListNode<T> *ptr_prev = NULL;
		LinkListNode<T> *ptr_temp = NULL;
		while (--(unsorted_link_list_head -> val) > 1) {
			ptr_prev = unsorted_link_list_head;
			ptr_temp = unsorted_link_list_head;

			while (ptr_temp -> next != it -> next) {
				if ((it -> next -> val) < (ptr_temp -> next -> val)) {
					ptr_prev = ptr_temp;
					ptr_temp = ptr_temp -> next;
				}
				else {
					break;
				}
			}

			if (ptr_prev != unsorted_link_list_head) {
				ptr_temp = it -> next;
				it -> next = it -> next -> next;
				ptr_temp -> next = ptr_prev -> next -> next;
				ptr_prev -> next = ptr_temp;
			}

			it = it -> next;
		}
	} else {
		std::cout << "[-] given unsupported type..." << std::endl;
	}
}

#endif  // SORT_ALGORITHM_H 
