#include <iostream>
#include "linked_list.hpp"

int main(int argc, char ** argv) {
    LinkedList<unsigned int> list;

    for (unsigned int i = 0; i < 20; i++) {
        list.append(i);
    }
    
    std::cout << ">> output in sequence" << std::endl;
    list.print();
    std::cout << ">> output in inverted sequence" << std::endl;
    list.reverse();
    list.print();
}
