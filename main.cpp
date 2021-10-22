#include <iostream>
#include <vector>
#include <fstream>
#include <cstdio>

using namespace std;


void swap_rows(vector<vector<double>> &matr, int x, int y){
    if (x == y) return;
    vector<double> temp_row = matr[x];
    matr[x] = matr[y];
    matr[y] = temp_row;
}

void mul_sum(int n, vector<vector<double>> &matr, int from, int to, double k){
    vector<double> temp_row = matr[from];
    for (int i=0; i<n+1; i++) temp_row[i] *= k;
    for (int i=0; i<n+1; i++) matr[to][i] += temp_row[i];
}

void print_matr(int n, vector<vector<double>> &matr){
    for (int i=0; i<n; i++){
        for (int j=0; j<n+1; j++){
            printf("   %10.2f", matr[i][j]);
            //cout << setw(10) << matr[i][j];
        }
        cout << endl;
    }
}

void forward(int n, vector<vector<double>> &matr){
    for (int line=0; line<n; line++){
        int max_line = line;
        int max_el = matr[line][line];
        for (int j = line; j<n; j++){
            if (matr[j][line] > max_el){
                max_el = matr[j][line]; // columns
                max_line = j;
            }
        }

        swap_rows(matr, line, max_line);

        for (int j = line+1; j<n; j++){
            mul_sum(n, matr, line, j, -1*matr[j][line]/matr[line][line]);
        }
    }

}

void backward(int n, vector<vector<double>> &matr){
    for (int line = n-1; line >= 0; line--){
        for (int j=line-1; j >= 0; j--){
            mul_sum(n, matr, line, j, -1*matr[j][line]/matr[line][line]);
        }
    }
}

vector<double> answer(int n, vector<vector<double>> &matr){
    vector<double> ans;
    for (int i = 0; i < n; i++){
        cout << "x" << i+1 << ": " << setw(10) << matr[i][n]/matr[i][i] << endl;
        ans.push_back(matr[i][n]/matr[i][i]);
    }
    return ans;
}


void solve(int n, vector<vector<double>> &matr){
    vector<vector<double>> temp_matr = matr;
    forward(n, matr);
    cout << "треугольная:" << endl;
    print_matr(n, matr);
    double det = 1;
    for (int i=0; i<n; i++){
        det *= matr[i][i];
    }
    cout << "det=" << det << endl;
    if (det == 0){
        cout << "Определитель равен нулю! Единственное решение системы не существует" << endl;
        return;
    }

    backward(n, matr);
    vector<double> answers = answer(n,matr);


    cout << "невязка: " << endl;
    for (int i=0; i<n; i++){
        double r = 0;
        for (int j=0; j<n; j++){
            r += answers[j] * temp_matr[i][j];
        }
        cout << "r" << i+1 << ": " << setw(8) << r-temp_matr[i][n] << endl;
    }
}




int main() {
    ifstream input_file("input");
    int n;
    vector<vector<double>> matr(n, vector<double>());
    cout << "1 - ввод из файла \"input\"\n2 - ввод с клавиатуры\n";
    cout << "Выбор? ";
    int choice;
    cin >> choice;
    choice==1 ? input_file : cin >> n;
    for (int i=0; i<n; i++){
        for (int j=0; j<n+1; j++){
            double t;
            choice==1 ? input_file : cin >> t;
            matr[i].push_back(t);
        }
    }
    cout << "ваша матрица:" << endl;
    print_matr(n, matr);
    solve(n, matr);
    return 0;
}