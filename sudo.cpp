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
#include <set>

using namespace std;

bool analizarSubregion(vector<string>& sudoku, int fila, int columna, int n) {
    vector<vector<bool> > subCheck(n*n,vector<bool>(n*n,false));
    for (int i = fila; i < fila + n; i++) {
        for (int j = columna; j < columna + n; j++) {
            int regNum = int(sudoku[i][j]) - 1;
            if(subCheck[i][j] == true){
                return false;
            }
            subCheck[i][regNum] = true;
        }
    }
    return true;
}

bool EsValido2(vector<string>& sudoku, int n){
    vector<vector<bool> > filaCheck(n*n, vector<bool>(n*n, false));
    vector<vector<bool> > colCheck(n*n, vector<bool>(n*n,false));

    // comprobar filas y columnas
    for (int i = 0; i < (n*n); i++){
        for (int j = 0; j < (n*n); j++){
            int filaNum = int(sudoku[i][j]) - 1;
            int colNum = int(sudoku[j][i]) - 1;
            if(filaCheck[i][j] == true || colCheck[i][j] == true){
                return false;
                // encontro un numero repetido, en una fila o columna
            }
            filaCheck[i][filaNum] = colCheck[i][colNum] = true;
        }
    }

    // comprobar recuadro
    for(int i = 0; i < (n*n); i = i + n){
        for(int j = 0; j < (n*n) ; j = j + n){
            if(!analizarSubregion(sudoku, i, j, n)){
                return false;
            }

        }
    }
    return true;
}


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

// funcion para almacenar los valores del sudoku

bool esCeldaVacia(const vector<string>& sudoku, int fila, int columna) {
    return sudoku[fila][columna] == '-';
}

set<char> numerosPosibles(const vector<string>& sudoku, int fila, int columna, int n) {
    set<char> fijos, posibles;
    for (int i = 0; i < n * n; ++i) {
        if (sudoku[fila][i] != '-') {
            fijos.insert(sudoku[fila][i]);
        }

        if (sudoku[i][columna] != '-') {
            fijos.insert(sudoku[i][columna]);
        }
    }

    int filSub = (fila / n) * n;
    int colSub = (columna / n) * n;
    for (int i = filSub; i < filSub + n; ++i) {
        for (int j = colSub; j < colSub + n; ++j) {
            if (sudoku[i][j] != '-') {
                fijos.insert(sudoku[i][j]);
            }
        }
    }

    for (char i = '1'; i <= ('0' + n * n); ++i) {
        if (fijos.find(i) == fijos.end()) {
            posibles.insert(i);
        }
    }

    return posibles;
}

vector<vector<set<char>>> posibleCasilla(const vector<string>& sudoku, int n) {
    vector<vector<set<char>>> tableroPosibles(n * n, vector<set<char>>(n * n));

    for (int i = 0; i < n * n; ++i) {
        for (int j = 0; j < n * n; ++j) {
            if (esCeldaVacia(sudoku, i, j)) {
                tableroPosibles[i][j] = numerosPosibles(sudoku, i, j, n);
            } else {
                set<char> temp = { sudoku[i][j] };
                tableroPosibles[i][j] = temp;
            }
        }
    }

    return tableroPosibles;
}


void imprimirTableroPosibles(const vector<vector<set<char>>>& tableroPosibles) {
    for (const auto& fila : tableroPosibles) {
        for (const auto& conjunto : fila) {
            if (conjunto.empty()) {
                cout << "{ } ";
            } else {
                cout << "{ ";
                for (char c : conjunto) {
                    cout << c << " ";
                }
                cout << "} ";
            }
        }
        cout << endl;
    }
}

vector<vector<set<char>>> actualizarTableroPosibles(vector<vector<set<char>>>& tableroPosibles) {
    int n = tableroPosibles.size();
    int subcuadro = sqrt(n);
    int max = (n * n) + 1;

    vector<pair<int, int>> posicionesActualizadas;

    for (int i = 0; i < n; ++i) {
        for (int j = 0; j < n; ++j) {
            if (tableroPosibles[i][j].size() == 1) {
                char num = *tableroPosibles[i][j].begin();

                // Eliminar num de la fila
                for (int k = 0; k < n; ++k) {
                    if (k != j) {
                        tableroPosibles[i][k].erase(num);
                    }
                }

                // Eliminar num de la columna
                for (int k = 0; k < n; ++k) {
                    if (k != i) {
                        tableroPosibles[k][j].erase(num);
                    }
                }

                // Eliminar num del subcuadrado
                int filaSub = (i / subcuadro) * subcuadro;
                int colSub = (j / subcuadro) * subcuadro;
                for (int k = filaSub; k < filaSub + subcuadro; ++k) {
                    for (int l = colSub; l < colSub + subcuadro; ++l) {
                        if (k != i || l != j) {
                            tableroPosibles[k][l].erase(num);
                        }
                    }
                }
            }
        }
    }
    return tableroPosibles;
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
/*    if (EsValido(sudoku, n)) {
    cout << "El sudoku completado es válido." << endl;
    } else {
    cout << "El sudoku completado NO es válido." << endl;
    }*/
vector<vector<set<char> > > tableroPosibles = posibleCasilla(sudoku, n);
tableroPosibles = actualizarTableroPosibles(tableroPosibles);
imprimirTableroPosibles(tableroPosibles);
    return 0;
    //debes correr usando -std=c++11
}