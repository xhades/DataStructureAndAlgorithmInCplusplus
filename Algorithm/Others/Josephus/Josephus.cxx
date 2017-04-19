#include <iostream>
#include <string>
#include <queue>
#include "cycle_linked_list.hpp"

// 时间复杂度 O(N*M)
unsigned Josephus_by_queue(unsigned int n, unsigned int m) {
    std::queue<unsigned int> q;
    for (unsigned int i = 0; i < n; i++) {
        q.push(i);
    }

    unsigned int member;
    unsigned int j;
    while(q.size() != 1) {
        for (j = 1; j < m; j++) {
            member = q.front();
            q.pop();
            q.push(member);
        }
        std::cout << q.front() << " is out" << std::endl;
        q.pop();
    }

    unsigned int winner = q.front();
    q.pop();

    return winner;
}

// 时间复杂度 O(N*M)
unsigned Josephus_by_cycle_linkedlist(unsigned int n, unsigned int m) {
    CycleLinkedList<unsigned int> list(0);
    for (unsigned int i = 1; i < n; i++) {
        list.append(i);
    }

    unsigned int j;
    while (list.size() != 1) {
        for (j = 1; j < m; j++) {
            list.next();
        }
        std::cout << list.value() << " is out" << std::endl;
        list.del();
    }

    unsigned int winner = list.value();

    return winner;
}

// 时间复杂度 O(N)
unsigned Josephus_by_math(unsigned int n, unsigned int m) {
    unsigned int winner = 0;
    for (unsigned int i = 2; i <= n; i++) {
        winner = (winner + m) % i;
    }

    return winner;
}

int main(int argc, char ** argv) {
    if (argc == 3) {
        unsigned int N = std::stoi(std::string(argv[1]));
        unsigned int M = std::stoi(std::string(argv[2]));

        unsigned int winner = Josephus_by_cycle_linkedlist(N, M);
        std::cout << "The winner is " << winner << std::endl;
    } else {
        std::cout << ">> Input Invalid!" << std::endl;
    }
}
