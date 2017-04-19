#ifndef __CURRICULA_VARIABLE_SYSTEM_HPP__
#define __CURRICULA_VARIABLE_SYSTEM_HPP__

#include <assert.h>
#include <iostream>
#include <string>
#include <vector>

struct Node {
    std::string header;
    std::string student;
    std::string curriculum;
    struct Node * next;

    Node(const std::string &h="", const std::string &s="", const std::string &c="", struct Node * ptr=nullptr) {
        header = h;
        student = s;
        curriculum = c;
        next = ptr;
    }
    ~Node() {}
};

class LinkedList {
public:
    LinkedList(const std::string &header) {
        members = 0;
        head = new struct Node(header);
        cursor = head;
    }

    ~LinkedList() {
        clear();
    }

    void append(const std::string &student, const std::string &curriculum) {
        members++;
        
        struct Node * node = new struct Node("", student, curriculum);
        cursor->next = node;
        cursor = node;
    }

    void del(const std::string &value, const bool &is_delete_student) {
        struct Node * temp = head;
        if (!is_delete_student) {
            while (temp->next->curriculum != value) {
                temp = temp->next;
            }
        } else {
            while (temp->next->student != value) {
                temp = temp->next;
            }
        }

        struct Node * temp_next_next = temp->next->next;
        delete temp->next;
        temp->next = temp_next_next;

        members--;
    }

    void find(const std::string &student, const std::string &curriculum) {
        struct Node * temp = head->next;

        while (temp) {
            if (temp->student == student) break;
            temp = temp->next;
        }

        if (temp) {
            std::cout << student << " is in " << curriculum << std::endl;
        } else {
            std::cout << student << " is not in " << curriculum << std::endl;
        }
    }

    struct Node * get_head() {
        return head;
    }

    std::string get_head_value() {
        return head->header;
    }

    unsigned int size() {
        return members;
    }

    void clear() {
        struct Node * temp = head->next;
        struct Node * temp_backup;
        while (temp) {
            temp_backup = temp;
            temp = temp->next;
            delete temp_backup;
            members--;
        }

        if (empty()) {
            std::cout << ">> clear opration is successful." << std::endl;
        }

        head->next = nullptr;
        cursor = head;   
    }

    bool empty() {
        return members == 0 ? true : false;
    }

    void print(const std::string &info) {
        struct Node * temp = head->next;
        if (info.compare("student")) {
            while (temp) {
                std::cout << "[+] " << temp->curriculum << std::endl;
                temp = temp->next;
            }
        } 
        else if (info.compare("curriculum")) {
            while (temp) {
                std::cout << "[+] " << temp->student << std::endl;
                temp = temp->next;
            }
        }
    }

private:
    unsigned int members;
    struct Node * head;
    struct Node * cursor;
};

class curriculum_system {
public:
    curriculum_system() {
        init();
    }
    ~curriculum_system() {}

    void register_curriculum(const std::string &curriculum) {
        curriculum_container.push_back(new LinkedList(curriculum));
    }

    void register_student(const std::string &student) {
        student_container.push_back(new LinkedList(student));
    }

    void print_curriculums() {
        std::cout << "********** curricula-variable system **********" << std::endl;
        for (std::vector<LinkedList *>::iterator it = curriculum_container.begin();
            it != curriculum_container.end(); it++) {
            std::cout << "[+] curriculum: " << (*it)->get_head_value() << std::endl;
        }
        std::cout << "[+] End" << std::endl;
    }

    void print_students() {
        std::cout << "********** curricula-variable system **********" << std::endl;
        for (std::vector<LinkedList *>::iterator it = student_container.begin();
            it != student_container.end(); it++) {
            std::cout << "[+] student: " << (*it)->get_head_value() << std::endl;
        }
        std::cout << "[+] End" << std::endl;
    }

    void query_curriculums(const std::string &student) {
        LinkedList * student_ptr;

        for (std::vector<LinkedList *>::iterator it = student_container.begin();
            it != student_container.end(); it++) {
            if ((*it)->get_head_value() == student) {
                student_ptr = *it;
            }
        }

        std::cout << "[+] student: " << student << std::endl;
        student_ptr->print("curriculum");
    }

    void query_students(const std::string &curriculum) {
        LinkedList * curriculum_ptr;

        for (std::vector<LinkedList *>::iterator it = curriculum_container.begin();
            it != curriculum_container.end(); it++) {
            if ((*it)->get_head_value() == curriculum) {
                curriculum_ptr = *it;
            }
        }

        std::cout << "[+] curriculum: " << curriculum << std::endl;
        curriculum_ptr->print("student");
    }

    void select_curriculum(const std::string &student, const std::string &curriculum) {
        LinkedList * student_ptr;
        LinkedList * curriculum_ptr;

        for (std::vector<LinkedList *>::iterator it = student_container.begin();
            it != student_container.end(); it++) {
            if ((*it)->get_head_value() == student) {
                student_ptr = *it;
            }
        }

        for (std::vector<LinkedList *>::iterator it = curriculum_container.begin();
            it != curriculum_container.end(); it++) {
            if ((*it)->get_head_value() == curriculum) {
                curriculum_ptr = *it;
            }
        }

        student_ptr->append(student, curriculum);
        curriculum_ptr->append(student, curriculum);
    }

    void find(const std::string &student, const std::string &curriculum) {
        LinkedList * curriculum_ptr;

        for (std::vector<LinkedList *>::iterator it = curriculum_container.begin();
            it != curriculum_container.end(); it++) {
            if ((*it)->get_head_value() == curriculum) {
                curriculum_ptr = *it;
            }
        }

        curriculum_ptr->find(student, curriculum);
    }

    void withdrawal(const std::string &student, const std::string &curriculum) {
        LinkedList * student_ptr;

        for (std::vector<LinkedList *>::iterator it = student_container.begin();
            it != student_container.end(); it++) {
            if ((*it)->get_head_value() == student) {
                student_ptr = *it;
            }
        }

        student_ptr->del(curriculum, false);

        LinkedList * curriculum_ptr;

        for (std::vector<LinkedList *>::iterator it = curriculum_container.begin();
            it != curriculum_container.end(); it++) {
            if ((*it)->get_head_value() == curriculum) {
                curriculum_ptr = *it;
            }
        }

        curriculum_ptr->del(student, true);
    }

private:
    std::vector<LinkedList *> curriculum_container;
    std::vector<LinkedList *> student_container;

    void init() {}
};

#endif  /* __CURRICULA_VARIABLE_SYSTEM_HPP__ */
