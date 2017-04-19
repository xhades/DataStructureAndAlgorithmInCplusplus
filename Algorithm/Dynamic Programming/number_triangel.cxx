#include <iostream>

int main(int argc, char ** argv) {
    int M[5][5];

    M[0][0] = 7;
    M[1][0] = 3, M[1][1] = 8; 
    M[2][0] = 8, M[2][1] = 1, M[2][2] = 0;
    M[3][0] = 2, M[3][1] = 7, M[3][2] = 4, M[3][3] = 4;
    M[4][0] = 4, M[4][1] = 5, M[4][2] = 2, M[4][3] = 6, M[4][4] = 5;

    for (int i = 4; i > 0; i--) {
        for (int j = 0; j < i; j++) {
            if (M[i-1][j] + M[i][j] > M[i-1][j] + M[i][j + 1]) {
                M[i-1][j] = M[i-1][j] + M[i][j];
            } else {
                M[i-1][j] = M[i-1][j] + M[i][j + 1];
            }
        }
    }

    std::cout << M[0][0] << std::endl;
}
