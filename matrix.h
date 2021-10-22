//
// Created by xwellen on 22.10.2021.
//
#include <vector>

#ifndef VM1_MATRIX_H
#define VM1_MATRIX_H

typedef std::vector<std::vector<double>> matr_t;

//меняем строки местами
void swap_rows(matr_t matr, int x, int y);

//умножаем строку from на k и прибавляем к строке с номером to
void mul_sum(int n, matr_t &matr, int from, int to, double k);

//просто печатаем матрицу
void print_matr(int n, matr_t &matr);

//прямой ход метода Гаусса
void forward(int n, matr_t &matr);

//обратный ход метода Гаусса
void backward(int n, matr_t &matr);

//формирование ответа
std::vector<double> answer(int n, matr_t &matr);

//штука которая все решает и выводит ответы с невязками
void solve(int n, matr_t &matr);

#endif //VM1_MATRIX_H
