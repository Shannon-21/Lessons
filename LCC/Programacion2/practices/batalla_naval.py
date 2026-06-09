
import os

map_x = {}
map_y = {}

def ask_table_size():
    w = int(input("width: "))
    h = int(input("height: "))

    # user x = 1..w   →  internal x = 0..w-1
    for x in range(1, w+1):
        map_x[x] = x - 1

    # user y = 1..h   →  internal y = h-y
    for y in range(1, h+1):
        map_y[y] = h - y

    return w, h
    
def ask_ships_configuration():
    ships = {}

    more = True
    while (more):
        id = int(input("ship number: "))
        ships[id] = int(input("ship length: "))
        more = bool(input("more ships?: "))

    return ships

def ask_ship_positions(dict_ship_sizes):
    ships = {}

    for ship_id, ship_size in dict_ship_sizes.items():
        print("ship: ", ship_id)
        x = map_x[int(input("x: "))]
        y = map_y[int(input("y: "))]
        ships[ship_id] = (x, y, ship_size, input("dir: "))

    return ships    
    
def put_ships_on_table(ships, table):
    # ships = {ships_id: (x, y, size, dir)}
    table_c = [r[:] for r in table]

    for num, pos in ships.items():
        x, y, size, dir = pos

        for i in range(size):
            table_c[y][x] = int(num)
            if dir == "V":
                y += 1
            if dir == "H":
                x += 1

    return table_c

def jugar(table_1, table_2, ships_1, ships_2, mx, my):
    turn = 0
    while True:
        print(f"Turn: {turn}")

        t = table_1 if turn == 0 else table_2
        o_t = table_2 if turn == 0 else table_1
        o_s = ships_2 if turn == 0 else ships_1
        
        print_table_players(t, o_t)
        
        x = mx[int(input("x: "))]
        y = my[int(input("y: "))]

        os.system('clear')

        if o_t[y][x] == 0:
            print("Water")
            o_t[y][x] = -.1
        elif o_t[y][x] != 0:
            o_ship = o_t[y][x]
            if (o_ship < 0): continue
            o_t[y][x] = o_ship * -1
            if (is_killed(abs(o_ship), o_t, o_s)):
                print("Killed!")
            else:
                print("Hit!")
        
        turn = 0 if turn == 1 else 1
        
        if bool(input(f"Continue player {turn}. Ready?: ")):
            os.system('clear')

def is_killed(ship, tablero, ships):
    x, y, size, dir = ships[ship]
        
    for i in range(size):
        if tablero[y][x] > 0:
            return False   
        
        if dir == "V":
            y += 1
        if dir == "H":
            x += 1
    
    return True

def print_table_players(table, o_table):
    table_c = [r[:] for r in o_table]
    for y in range(len(table_c)):
        for x in range(len(table_c[y])):
            if table_c[y][x] > 0:
                table_c[y][x] = 0
    
    width = 6
    for i in range(len(table)):
        left = " ".join(f"{v:{width}}" for v in table[i])
        right = " ".join(f"{v:{width}}" for v in table_c[i])
        print(f"{left}   |   {right}")

def print_table_player(table):
    for i in range(len(table)):
        print(table[i])

if __name__ == "__main__":

    (width, height) = ask_table_size()
    table = [[0 for _ in range(width)] for _ in range(height)]
    os.system('clear')

    dict_ship_sizes = ask_ships_configuration()
    os.system('clear')

    accept = False
    while (not accept):
        print("ships player 1:")
        ships_player_1 = ask_ship_positions(dict_ship_sizes)
        table_1 = put_ships_on_table(ships_player_1, table)
        print_table_player(table_1)
        accept = bool(input("Accept?: "))
    os.system('clear')
    
    accept = False
    while (not accept):
        print("ships player 2:")
        ships_player_2 = ask_ship_positions(dict_ship_sizes)
        table_2 = put_ships_on_table(ships_player_2, table)
        print_table_player(table_2)
        accept = bool(input("Accept?: "))
    os.system('clear')

    if bool(input("Start player 0. Ready?: ")):
        os.system('clear')

    jugar(table_1, table_2, ships_player_1, ships_player_2, map_x, map_y)