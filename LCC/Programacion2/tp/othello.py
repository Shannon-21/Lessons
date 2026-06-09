import sys
import random

# correr:
#   python ./othello.py ./output_tests/test_1.txt N 1
# testear:
#    pytest -q

def imprimir_tablero(board):
    """imprimir en formato como el tablero de othello"""
    print("   A B C D E F G H")
    for r in range(8):
        fila = []
        for c in range(8):
            fila.append(board[r][c] if board[r][c] != 'X' else '.')
        print(f"{r+1}  " + " ".join(fila))

def inicializar_tablero():
    # inicializa con todo el tablero vacio
    return [['X' for _ in range(8)] for _ in range(8)]

def color_opuesto(color):
    return 'B' if color == 'N' else 'N'

def parsear_jugada(txt):
    # solo 2 chars tipo 'A1' a 'H8', otro formato es invalido
    if len(txt) != 2:
        return None

    col = txt[0]
    row = txt[1]

    if col not in "ABCDEFGH":
        return None
    if row not in "12345678":
        return None

    # usar el ordinal porque la resta corresponde con el indice del tablero de col
    # ej: B - A = 66 - 65 = 1 
    c = ord(col) - ord('A')
    r = ord(row) - ord('1')
    return (r, c)

def cargar_partida_desde_archivo(path):
    """
    Archivo:
        8 lineas del tablero (8 chars cada una)
        1 linea indicando el turno (B o N)
    """
    with open(path, "r", encoding="utf-8") as f:
        lineas = [line.strip() for line in f.readlines()]

    if len(lineas) != 9:
        raise Exception("Archivo invalido: deben ser 9 lineas")

    tablero = inicializar_tablero()

    for i in range(8):
        fila = lineas[i]
        if len(fila) != 8:
            raise Exception("Fila invalida en tablero")

        for ch in fila:
            if ch not in ('X', 'B', 'N'):
                raise Exception("Caracter invalido en tabelro")

        tablero[i] = list(fila)

    turno = lineas[8].strip()
    if turno not in ('B', 'N'):
        raise Exception("Color de turno invalido")

    return tablero, turno

def dentro(r, c):
    """para validar que los indices de una celda estan dentro del tablero"""
    return 0 <= r < 8 and 0 <= c < 8

def direcciones():
    # las 8 posibles direcciones para mirar desde una celda
    return [(-1, -1), (-1, 0), (-1, 1),
            (0, -1),           (0, 1),
            (1, -1),  (1, 0),  (1, 1)]

def flips_de_jugada(tablero, turno, r, c):
    """
    Devuelve una lista de posiciones a voltear si juego en (r,c).
    Si no es jugada valida => lista vacia.
    """
    if not dentro(r, c):
        return []
    if tablero[r][c] != 'X':
        return []

    opp = color_opuesto(turno)
    flips = []

    for dr, dc in direcciones():
        rr = r + dr
        cc = c + dc

        # hay que validar que moverse a cada direccin sea valido
        if not dentro(rr, cc):
            continue
        if tablero[rr][cc] != opp:
            continue

        # para ir guardando las fichas opuestas que encerramos
        camino = []
        while dentro(rr, cc) and tablero[rr][cc] == opp:
            camino.append((rr, cc))
            rr += dr
            cc += dc

        # validar que el camino termina con una ficha nuestra
        if dentro(rr, cc) and tablero[rr][cc] == turno and camino:
            flips.extend(camino)

    return flips

def jugadas_validas(tablero, turno):
    # devuelve dict {(r,c): [flips...]}
    res = {}
    for r in range(8):
        for c in range(8):
            if tablero[r][c] != 'X':
                continue
            flips = flips_de_jugada(tablero, turno, r, c)
            if flips:
                res[(r, c)] = flips
    return res

def aplicar_jugada(tablero, turno, r, c, flips):
    # aca ya viene todo validado por el caller, no re-chequeo
    tablero[r][c] = turno
    for x, y in flips:
        tablero[x][y] = turno

def tablero_lleno(tablero):
    for r in range(8):
        for c in range(8):
            if tablero[r][c] == 'X':
                return False
    return True

def contar_fichas(tablero):
    bc = 0
    nc = 0
    for r in range(8):
        for c in range(8):
            if tablero[r][c] == 'B':
                bc += 1
            elif tablero[r][c] == 'N':
                nc += 1
    return bc, nc

def juego_terminado(tablero, turno):
    # termina si el tablero esta lleno o si ninguno puede jugar
    if tablero_lleno(tablero):
        return True

    if jugadas_validas(tablero, turno):
        return False
    if jugadas_validas(tablero, color_opuesto(turno)):
        return False

    return True

def imprimir_resultado(tablero):
    bc, nc = contar_fichas(tablero)
    print(f"Resultado final: B={bc} N={nc}")
    print("El ganador es: ", end='')
    if bc > nc:
        print("B")
    elif nc > bc:
        print("N")
    else:
        print("Empate")

def pedir_jugada_humano(tablero, turno):
    """pide jugadas al humano hasta que ingrese una valida.
        cuando se valida, aplica la jugada produciendo los cambios en el tablero"""

    # se valida 1 vez, y de ahi sale todo (pos + flips)
    movs = jugadas_validas(tablero, turno)

    while True:
        txt = input(f"({turno}) Ingrese jugada (A1-H8): ").strip().upper()
        pos = parsear_jugada(txt)
        if pos is None:
            print("Jugada invalida. Intente nuevamente.")
            continue

        r, c = pos
        flips = movs.get((r, c))
        if not flips:
            print("Jugada invalida. Intente nuevamente.")
            continue

        aplicar_jugada(tablero, turno, r, c, flips)
        imprimir_tablero(tablero)
        return

def elegir_jugada_maquina(movs, level):
    # movs: dict {(r,c): flips}
    if not movs:
        return None

    items = list(movs.items())  # [((r,c), [flips...]), ...]

    # para el level 0 elije random alguna jugada valida para su turno
    if level == 0:
        return random.choice(items)

    # nivel 1 busca el que voltee mas fichas y lo pone como el mejor
    mejor_pos, mejor_flips = items[0]
    mejor_score = len(mejor_flips)

    for pos, flips in items[1:]:
        score = len(flips)
        if score > mejor_score: # igual estrcito para que se quede con el primer mayor en caso de igualdad
            mejor_pos, mejor_flips = pos, flips
            mejor_score = score

    return (mejor_pos, mejor_flips)

def pedir_jugada_maquina(tablero, turno, level):
    # de la jugada valida que elija la maquina, aplicar al tablero el resultado
    movs = jugadas_validas(tablero, turno)
    eleccion = elegir_jugada_maquina(movs, level)
    if eleccion is None:
        return False  # pass

    (r, c), flips = eleccion
    print(f"({turno}) Maquina juega: {chr(c + ord('A'))}{r + 1}")

    aplicar_jugada(tablero, turno, r, c, flips)
    imprimir_tablero(tablero)
    return True

def validar_args(argv):
    if len(argv) != 4:
        raise Exception("Debe tener tres argumentos `file_name` (str) `color` (char) `nivel` (int)")

    input_file = argv[1]
    user_color = argv[2].strip().upper()

    if user_color not in ('B', 'N'):
        raise Exception("Color debe ser 'B' o 'N'")

    try:
        machine_level = int(argv[3])
    except:
        raise Exception("Nivel de juego debe ser 0 o 1")

    if machine_level not in (0, 1):
        raise Exception("Nivel de juego debe ser 0 o 1")

    return input_file, user_color, machine_level

def main(argv):
    input_file, user_color, machine_level = validar_args(argv)

    try:
        tablero, turno = cargar_partida_desde_archivo(input_file)
    except FileNotFoundError:
        print("No se encontro el archivo")
        return
    except Exception as e:
        print(str(e))
        return

    print("Tablero inicial:")
    imprimir_tablero(tablero)
    print(f"Turno inicial: {turno}")

    while True:
        if juego_terminado(tablero, turno):
            imprimir_resultado(tablero)
            return

        movs = jugadas_validas(tablero, turno)
        if not movs:
            print(f"({turno}) PASS: no tiene jugadas validas")
            turno = color_opuesto(turno)
            continue

        if user_color == turno:
            pedir_jugada_humano(tablero, turno)
        else:
            pedir_jugada_maquina(tablero, turno, machine_level)

        turno = color_opuesto(turno)

if __name__ == '__main__':
    main(sys.argv)