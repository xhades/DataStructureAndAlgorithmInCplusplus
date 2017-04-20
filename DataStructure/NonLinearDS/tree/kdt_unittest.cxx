#include <iostream>
#include <fstream>
#include <random>
#include <string>
#include <vector>
#include <time.h>

#include "string_operation.hpp"
#include "kd_tree.hpp"

int main(int argc, char ** argv) {
    /*
    std::ofstream file;
    file.open("spatial data.txt");
    if (file.is_open()) {
        std::random_device rd;
        std::uniform_int_distribution<int> dist(0, 10000);
        std::string x;
        std::string y;
        std::string z;
        for (unsigned int i = 0; i < 1000000; i++) {
            x = std::to_string(dist(rd));
            x.append(", ");
            file << x;
            y = std::to_string(dist(rd));
            y.append(", ");
            file << y;
            z = std::to_string(dist(rd));
            z.append("\n");
            file << z;
        }
        file.close();
    } else {
        std::cout << ">> can not open file" << std::endl;
    }
    */

    std::ifstream file;
    file.open("spatial data.txt");
    if (file.is_open()) {
        int ** spatial_data = new int *[1000000];
        char line[256];
        
        unsigned int i;
        unsigned int line_counter = 0;
        std::vector<std::string> spatial_data_per_line;
        while (file.getline(line, 256)) {
            std::string str(line);
            split(str, spatial_data_per_line);

            spatial_data[line_counter] = new int[3];
            for (i = 0; i < 3; i++) {
                spatial_data[line_counter][i] = std::stoi(spatial_data_per_line.at(i));
            }

            line_counter++;
            spatial_data_per_line.clear();
        }
        file.close();

        int point[] = {100, 140, 520};

        KDTree<int> kdt;
        kdt.build(spatial_data, 1000000);

        std::cout << "********** KD-Tree for find KNN ***********" << std::endl;
        clock_t start = clock();
        kdt.find_knn(point);
        clock_t end = clock();
        int used_time_1 = end - start;
        std::cout << "[+] used " << used_time_1 << " ms" << std::endl;
        std::cout << "******** Naive-Search for find KNN ********" << std::endl;
        start = clock();
        double dist = 0.0;
        double best_dist = 0.0;
        int * knn = nullptr;
        dist = sqrt((point[0] - spatial_data[0][0]) * (point[0] - spatial_data[0][0]) + (point[1] - spatial_data[0][1]) * (point[1] - spatial_data[0][1]) + (point[2] - spatial_data[0][2]) * (point[2] - spatial_data[0][2]));
        best_dist = dist;
        std::cout << "[+] search [" << point[0] << ", " << point[1] << ", " << point[2] << "]'s KNN in Naive-Search ... " << std::endl;
        for (unsigned int i = 1; i < 1000000; i++) {
            dist = sqrt((point[0] - spatial_data[i][0]) * (point[0] - spatial_data[i][0]) + (point[1] - spatial_data[i][1]) * (point[1] - spatial_data[i][1]) + (point[2] - spatial_data[i][2]) * (point[2] - spatial_data[i][2]));
            if (dist < best_dist) {
                best_dist = dist;
                knn = spatial_data[i];
            }
        }
        std::cout << "[+] KNN is (" << knn[0] << ", " << knn[1] << ", " << knn[2] << ")" << std::endl; 
        std::cout << "[+] KNN'diantance is " << best_dist << std::endl;
        end = clock();
        int used_time_2 = end - start;
        std::cout << "[+] used " << used_time_2 << " ms" << std::endl;

        std::cout << "*******************************************" << std::endl;
        std::cout << "[+] speedup is " << int(used_time_2 / used_time_1) << std::endl;

        for (unsigned int i = 0; i < 1000000; i++) {
            delete [] spatial_data[i];
        }
        delete spatial_data;
    } else {
        std::cout << ">> can not open file" << std::endl;
    }
}
