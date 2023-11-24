def eliminar_de_lista(lista, numeros_a_eliminar):
    return [num for num in lista if num not in numeros_a_eliminar]

def generar_posibles(sudoku, n):
    posibles_sudoku = []
    for fila in sudoku:
        nueva_fila = []
        for elemento in fila:
            if elemento == 0:
                posibles = list(range(1, n * n + 1))
                nueva_fila.append(posibles)
            else:
                nueva_fila.append([elemento])
        posibles_sudoku.append(nueva_fila)

    for i in range(n * n):
        for j in range(n * n):
            if isinstance(posibles_sudoku[i][j], list):  # Solo para casillas vacías
                fila = [posibles_sudoku[i][x] for x in range(n * n) if isinstance(posibles_sudoku[i][x], int) or (isinstance(posibles_sudoku[i][x], list) and len(posibles_sudoku[i][x]) == 1)]
                columna = [posibles_sudoku[x][j] for x in range(n * n) if isinstance(posibles_sudoku[x][j], int) or (isinstance(posibles_sudoku[x][j], list) and len(posibles_sudoku[x][j]) == 1)]
                numeros_en_fila_columna = set(sum(fila + columna, []))
                posibles_sudoku[i][j] = eliminar_de_lista(posibles_sudoku[i][j], numeros_en_fila_columna)

    return posibles_sudoku

def imprimir_posibles(posibles_sudoku, n):
    for i in range(n * n):
        if i % n == 0 and i != 0:
            print("-" * (n * (n + 1) + n - 1))
        for j in range(n * n):
            if j % n == 0 and j != 0:
                print("|", end=" ")
            celda = posibles_sudoku[i][j]
            if len(celda) > 1:
                print(" ".join(map(str, celda)).center(10), end=" ")
            else:
                print(str(celda[0]).center(10), end=" ")
        print()

# Sudoku inicial
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

posibles_sudoku = generar_posibles(sudoku, n)
imprimir_posibles(posibles_sudoku, n)
