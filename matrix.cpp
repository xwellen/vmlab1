//
// Created by xwellen on 22.10.2021.
//
#include "matrix.h"

void swap_rows(matr_t matr, int x, int y) {
    if (x == y) return;
    std::vector<double> temp_row = matr[x];
    matr[x] = matr[y];
    matr[y] = temp_row;
}

void mul_sum(int n, matr_t &matr, int from, int to, double k) {
    std::vector<double> temp_row = matr[from];
    for (int i = 0; i < n + 1; i++) temp_row[i] *= k;
    for (int i = 0; i < n + 1; i++) matr[to][i] += temp_row[i];
}

void print_matr(int n, matr_t &matr) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            printf("   %10.2f", matr[i][j]);
        }
        printf("\n");
    }
}

void forward(int n, matr_t &matr) {
    for (int line = 0; line < n; line++) {
        int max_line = line;
        int max_el = matr[line][line];
        for (int j = line; j < n; j++) {
            if (matr[j][line] > max_el) {
                max_el = matr[j][line]; // columns
                max_line = j;
            }
        }

        swap_rows(matr, line, max_line);

        for (int j = line + 1; j < n; j++) {
            mul_sum(n, matr, line, j, -1 * matr[j][line] / matr[line][line]);
        }
    }

}

void backward(int n, matr_t &matr) {
    for (int line = n - 1; line >= 0; line--) {
        for (int j = line - 1; j >= 0; j--) {
            mul_sum(n, matr, line, j, -1 * matr[j][line] / matr[line][line]);
        }
    }
}

std::vector<double> answer(int n, matr_t &matr) {
    std::vector<double> ans;
    for (int i = 0; i < n; i++) {
        printf("x%d: % f10.2", i + 1, matr[i][n] / matr[i][i]);
        ans.push_back(matr[i][n] / matr[i][i]);
    }
    return ans;
}


void solve(int n, matr_t &matr) {
    matr_t temp_matr = matr;
    forward(n, matr);
    printf("треугольная:\n");
    print_matr(n, matr);
    double det = 1;
    for (int i = 0; i < n; i++) {
        det *= matr[i][i];
    }
    printf("det=%f\n", det);
    if (det == 0) {
        printf("Определитель равен нулю! Единственное решение системы не существует\n");
        return;
    }

    backward(n, matr);
    std::vector<double> answers = answer(n, matr);


    printf("невязка: \n");
    for (int i = 0; i < n; i++) {
        double r = 0;
        for (int j = 0; j < n; j++) {
            r += answers[j] * temp_matr[i][j];
        }
        printf("r%d: % 8.2f\n", i + 1, r - temp_matr[i][n]);
    }
}