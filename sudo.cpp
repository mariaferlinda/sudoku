//leer matriz, sacar los posibles numeros que pueden ir en una casilla y agg en lista
//Evaluar las listas aplicando las reglas
//1. si en una casilla solo hay una posibilidad y hay otra f, col, cua con la misma
//2. si en una casilla de f, col, cua hay un num q no se repite
//3. trios obvios
//4. pares obvios
#include <iostream>
#include <vector>
#include <algorithm>
#include <string>
#include <cmath>

using namespace std;


bool EsValido(vector<string>& sudoku, int n) {
    vector<vector<bool> > fila_check(n * n, vector<bool>(n * n + 1, false)); //arreglo de booleanos estaticos
    vector<vector<bool> > col_check(n * n, vector<bool>(n * n + 1, false));
    vector<vector<bool> > sub_check(n * n, vector<bool>(n * n + 1, false));

    for (int i = 0; i < n * n; ++i) {
        for (int j = 0; j < n * n; ++j) {
            if (sudoku[i][j] != '-') {
                int num = sudoku[i][j] - '0';
                if (fila_check[i][num] || col_check[j][num] || sub_check[(i / n) * n + j / n][num]) {
                    return false; // Número repetido
                }
                fila_check[i][num] = col_check[j][num] = sub_check[(i / n) * n + j / n][num] = true;
            }
        }
    }

    return true; // Sudoku válido
}



vector<string> modificarSudoku(vector<string>& sudoku, int n) {
    int num_digits = log10(n * n) + 1;
    string empty_cell(num_digits, '-');

    vector<string> sudoku_modificado; // Nuevo sudoku modificado

    for (int i = 0; i < n * n; ++i) {
        if (i % n == 0 && i != 0) {
            sudoku_modificado.push_back(string(n * (num_digits + 1) + n - 1, '-'));
        }
        string row = "";
        for (int j = 0; j < n * n; ++j) {
            if (j % n == 0 && j != 0) {
                row += "| ";
            }
            char current_char = sudoku[i][j];
            if (current_char == '0') {
                row += empty_cell + " ";
            } else {
                string cell_value(1, current_char);
                while (cell_value.length() < num_digits) {
                    cell_value = "0" + cell_value;
                }
                row += cell_value + " ";
            }
        }
        sudoku_modificado.push_back(row);
    }

    return sudoku_modificado;
}



int main() {
    int n;
    cout << "Ingrese el tamaño del subcuadrado (n): ";
    cin >> n;

    vector<string> sudoku(n * n);

    cout << "Ingrese el sudoku (separando cada fila por un salto de línea):" << endl;
    for (int i = 0; i < n * n; ++i) {
        cin >> sudoku[i];
    }
/* "muestra el sudoku modificado, es decir si nos pasan un sudoku con 0 los cambia a '-' "
    vector<string> sudoku_modificado = modificarSudoku(sudoku, n);
    cout << "Sudoku modificado:" << endl;
    for (const string& row : sudoku_modificado) {
        cout << row << endl;
    }*/
    if (EsValido(sudoku, n)) {
    cout << "El sudoku completado es válido." << endl;
    } else {
    cout << "El sudoku completado NO es válido." << endl;
    }
    return 0;
    //debes correr usando -std=c++11
}