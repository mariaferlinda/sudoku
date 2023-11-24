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

int RecorrerM(int sudoku, int n){
    for (int k = 0; k < n; k++){
        for (int j = 0; j < n; j++){
            if (sudoku[k][j] == '-'){
            }
        }
    }
}

int unicaC(int sudoku2){
    for (int i = 0)
        }



void print_sudoku(string sudoku[], int n) {
    int num_digits = log10(n * n) + 1;  // Dígitos para representar cada símbolo
    string empty_cell(num_digits, '-');  // Representación de una celda vacía

    for (int i = 0; i < n * n; ++i) {
        if (i % n == 0 && i != 0) {
            cout << string(n * (num_digits + 1) + n - 1, '-') << endl;
        }
        for (int j = 0; j < n * n; ++j) {
            if (j % n == 0 && j != 0) {
                cout << "| ";
            }
            char current_char = sudoku[i][j];
            if (current_char == '0') {
                cout << empty_cell << " ";
            } else {
                string cell_value(1, current_char);
                while (cell_value.length() < num_digits) {
                    cell_value = "0" + cell_value;
                }
                cout << cell_value << " ";
            }
        }
        cout << endl;
    }
}


int main() {
    int n;
    cout << "Ingrese el tamaño del subcuadrado (n): ";
    cin >> n;

    string sudoku[n * n];

    cout << "Ingrese el sudoku (separando cada fila por un salto de línea):" << endl;
    for (int i = 0; i < n * n; ++i) {
        cin >> sudoku[i];
    }

    print_sudoku(sudoku, n);
    return 0;
}