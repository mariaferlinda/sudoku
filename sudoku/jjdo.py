import math

def print_sudoku(sudoku, n):
    num_digits = int(math.log10(n * n) + 1)  # Dígitos para representar cada símbolo
    empty_cell = '-' * num_digits  # Representación de una celda vacía

    for i in range(n * n):
        if i % n == 0 and i != 0:
            print("-" * (n * (num_digits + 1) + n - 1))
        for j in range(n * n):
            if j % n == 0 and j != 0:
                print("|", end=" ")
            if sudoku[i][j] == 0:
                print(empty_cell, end=" ")
            else:
                cell_value = str(sudoku[i][j]).zfill(num_digits)
                print(cell_value, end=" ")
        return sudoku

def leer(sudoku, n):
    lista = list(range(1, n * n + 1))
    print(lista)# Generar la lista del 1 al n^2
    for i in range(n):
        for j in range(n):
            if sudoku[i][j] == '-' and sudoku[i][j] in lista:
                lista.remove(sudoku[i][j])
    print(lista)
    return lista

sudoku = [
    [5, 3, 0, 0, 7, 8, 0, 0, 0],
    [6, 0, 0, 1, 9, 5, 0, 0, 0],
    [0, 9, 8, 0, 0, 0, 0, 6, 0],
    [8, 0, 0, 0, 6, 0, 0, 0, 3],
    [4, 0, 0, 8, 0, 3, 0, 0, 1],
    [7, 0, 0, 0, 2, 0, 0, 0, 6],
    [0, 6, 0, 0, 0, 0, 2, 8, 0],
    [0, 0, 0, 4, 1, 9, 0, 0, 5],
    [0, 0, 0, 0, 8, 0, 0, 7, 9]
]
n = 3
leer(sudoku, n)