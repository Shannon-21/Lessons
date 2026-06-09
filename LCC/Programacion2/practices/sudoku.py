def esta_vertical(tablero, ri, ci, num):
    for i in range(len(tablero)):
        if (ri == i):
            continue
        elif tablero[i][ci] == num:
            return True
    return False

def esta_horizantal(tablero, ri, ci, num):
    for i in range(len(tablero[0])):
        if (ci == i):
            continue
        elif tablero[ri][i] == num:
            return True
    return False

def es_valido(tablero):

    # control vertical
    for ci in range(len(tablero[0])):
        for ri in range(len(tablero)):
            num = tablero[ri][ci]
            if num == 0: 
                continue
            elif esta_vertical(tablero, ri, ci, num):
                return False
    
    # control horizontal
    for ri in range(len(tablero)):
        for ci in range(len(tablero[ri])):
            num = tablero[ri][ci]
            if num == 0: 
                continue
            elif esta_horizantal(tablero, ri, ci, num):
                return False
            
    # control diagonal derecha
    ri = len(tablero)
    ci = 0
    for ci in range(len(tablero[0])):
        for ri in range(len(tablero), -1, -1):
            num = tablero[ri][ci]
            if num == 0: 
                continue
            elif esta_vertical(tablero, ri, ci, num):
                return False
            
    

    return True

def print_tablero(tablero):
    for ri in range(len(tablero)):
        if (ri == 3 or ri == 6):
            print('-' * 9)
        row = ""
        for ci in range(len(tablero[ri])):
            if (ci == 3 or ci == 6):
                row += "|"
            row += str(tablero[ri][ci])
        print(row)

tablero = [[0 for _ in range(9)] for _ in range(9)]
tablero[0][4] = 3
tablero[5][4] = 1
tablero[6][4] = 4
tablero[5][7] = 1
tablero[5][6] = 9

print_tablero(tablero)
print(es_valido(tablero))

# 000|030|000
# 000|000|000
# 000|000|000
# ---------
# 000|000|000
# 000|000|000
# 000|010|000
# ---------
# 000|040|000
# 000|000|000
# 000|000|000
