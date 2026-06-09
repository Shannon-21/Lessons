def es_ganadora(tablero, fila, columna):
    """ 
    tablero es una matriz con 1, 2, o ' '
    ver si de forma diagonal, horizontal o vertical hay 4 iguales consecutivas
    """

    value = tablero[fila][columna]

    # horizontal desde fila
    counter = 0
    for ci in range(len(tablero[0])):
        if tablero[fila][ci] == value:
            counter += 1
        elif counter < 4:
            counter = 0
    if counter >= 4: return True

    # vertical desde columna
    counter = 0
    for fi in range(len(tablero)):
        if tablero[fi][columna] == value:
            counter += 1
        elif counter < 4:
            counter = 0
    if counter >= 4: return True

    # diagonal izquierda desde celda
    counter = 0
    row = len(tablero) - 1
    col = columna + (row - fila)
    for i in range(len(tablero[0])): # asume tablero con mas columnas que filas
        if (col >= 0 and row >= 0 and col < len(tablero[0]) and row < len(tablero)):
            if tablero[row][col] == value:
                counter += 1
            elif counter < 4:
                counter = 0
        col -= 1
        row -= 1
    if counter >= 4: return True

    # diagonal derecha desde celda
    counter = 0
    row = len(tablero) - 1
    col = columna - (row - fila)
    for i in range(len(tablero[0])): # asume tablero con mas columnas que filas
        if (col >= 0 and row >= 0 and col < len(tablero[0]) and row < len(tablero)):
            if tablero[row][col] == value:
                counter += 1
            elif counter < 4:
                counter = 0
        col += 1
        row -= 1
    if counter >= 4: return True

    return False

tablero = [
    [' ', ' ', ' ', ' ', ' ', ' ', ' '],
    [' ', ' ', ' ', 'A', ' ', ' ', ' '],
    [' ', 'B', ' ', 'B', 'A', ' ', ' '],
    [' ', 'A', 'B', 'A', 'B', 'B', 'B'],
    [' ', 'A', 'A', 'B', 'A', 'A', 'A'],
    [' ', 'A', 'A', 'B', 'B', 'B', 'A'],
    ['A', 'B', 'A', 'B', 'A', 'A', 'A'],
]

def print_tablero(tablero):
    for i in range(len(tablero)):
        print(tablero[i])

print_tablero(tablero)
print(es_ganadora(tablero, 3, 2))
print(es_ganadora(tablero, 2, 4))
