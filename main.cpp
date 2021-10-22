#include <iostream>
#include <fstream>
#include "matrix.h"

using namespace std;

int main() {
    ifstream input_file("input");
    int n;
    matr_t matr(n, vector<double>());
    cout << "1 - ввод из файла \"input\"\n2 - ввод с клавиатуры\n";
    cout << "Выбор? ";
    int choice;
    cin >> choice;
    choice == 1 ? input_file : cin >> n;
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n + 1; j++) {
            double t;
            choice == 1 ? input_file : cin >> t;
            matr[i].push_back(t);
        }
    }
    cout << "ваша матрица:" << endl;
    print_matr(n, matr);
    solve(n, matr);
    return 0;
}