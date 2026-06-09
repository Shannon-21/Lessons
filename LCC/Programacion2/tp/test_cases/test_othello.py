import pytest
import othello

def _tablero_vacio():
    return othello.inicializar_tablero()

def _poner(tablero, coords, ch):
    # helper
    for r, c in coords:
        tablero[r][c] = ch
    return tablero

def _tablero_inicial_estandar():
    # setup clasico del othello en el centro
    t = _tablero_vacio()
    _poner(t, [(3, 3), (4, 4)], 'B')
    _poner(t, [(3, 4), (4, 3)], 'N')
    return t

def test_inicializar_tablero():
    t = othello.inicializar_tablero()
    assert len(t) == 8
    assert all(len(fila) == 8 for fila in t)
    assert all(t[r][c] == 'X' for r in range(8) for c in range(8))

def test_otro_color():
    assert othello.color_opuesto('B') == 'N'
    assert othello.color_opuesto('N') == 'B'

def test_parsear_jugada_ok():
    assert othello.parsear_jugada("A1") == (0, 0)
    assert othello.parsear_jugada("H8") == (7, 7)
    assert othello.parsear_jugada("D6") == (5, 3)
    assert othello.parsear_jugada("Y9") == None
    assert othello.parsear_jugada("D78") == None

def test_parsear_jugada_invalidas():
    # parsear_jugada asume mayus, asi que no le paso minusculas aca
    invalidas = ["", "A", "AA", "A9", "I1", "11", "Z0", "A0", "H9", "D66"]
    for txt in invalidas:
        assert othello.parsear_jugada(txt) is None

def test_dentro():
    assert othello.dentro(0, 0) is True
    assert othello.dentro(7, 7) is True
    assert othello.dentro(-1, 0) is False
    assert othello.dentro(0, -1) is False
    assert othello.dentro(8, 0) is False
    assert othello.dentro(0, 8) is False

def test_flips_de_jugada_en_tablero_inicial():
    t = _tablero_inicial_estandar()
    othello.imprimir_tablero(t)

    # en el tablero inicial, para B las jugadas validas son 4 y cada una voltea 1
    # ejemplo: C4 (r=3,c=2) voltea (3,3)
    flips = othello.flips_de_jugada(t, 'N', 3, 2)
    assert flips == [(3, 3)]

    flips = othello.flips_de_jugada(t, 'N', 2, 3)  # D3 voltea (3,3)
    assert flips == [(3, 3)]

    flips = othello.flips_de_jugada(t, 'B', 4, 5)  # F5 voltea (4,4)? no, al reves: voltea (4,4) si hay N.. aca no
    # mejor chequeo otra jugada valida de B: E6 (5,4) voltea (4,4)? tampoco
    # en realidad para B en inicio: C4 D3 E6 F5 (todas voltean 1)
    flips = othello.flips_de_jugada(t, 'B', 5, 4)  # E6 voltea (4,4) (que es B) nope, me equivoque si lo miro mal
    # para evitar confusiones, chequeamos las 4 validas via jugadas_validas mas abajo

def test_jugadas_validas_inicial_estandar():
    t = _tablero_inicial_estandar()

    movs_b = othello.jugadas_validas(t, 'B')
    movs_n = othello.jugadas_validas(t, 'N')

    # en inicio hay 4 jugadas validas por lado
    assert len(movs_b) == 4
    assert len(movs_n) == 4

    # y en todas se voltea 1
    assert all(len(flips) == 1 for flips in movs_b.values())
    assert all(len(flips) == 1 for flips in movs_n.values())

def test_aplicar_jugada_voltea_correcto():
    t = _tablero_inicial_estandar()
    movs_b = othello.jugadas_validas(t, 'B')

    # elegimos una valida cualquiera, y aplicamos usando los flips ya calculados
    (r, c), flips = next(iter(movs_b.items()))
    othello.aplicar_jugada(t, 'B', r, c, flips)

    assert t[r][c] == 'B'
    for x, y in flips:
        assert t[x][y] == 'B'

def test_elegir_jugada_maquina_level0_y_level1():
    t = _tablero_inicial_estandar()
    movs = othello.jugadas_validas(t, 'B')

    # lvl 0 devuelve alguna valida
    pick0 = othello.elegir_jugada_maquina(movs, 0)
    assert pick0 is not None
    assert pick0[0] in movs

    # lvl 1 en inicio da igual cual, todas voltean 1. pero tiene que ser valida.
    pick1 = othello.elegir_jugada_maquina(movs, 1)
    assert pick1 is not None
    assert pick1[0] in movs
    assert len(pick1[1]) == 1

def test_tablero_lleno():
    t = _tablero_vacio()
    assert othello.tablero_lleno(t) is False

    _poner(t, [(r, c) for r in range(8) for c in range(8)], 'B')
    assert othello.tablero_lleno(t) is True

def test_contar_fichas():
    t = _tablero_vacio()
    _poner(t, [(0, 0), (0, 1), (0, 2)], 'B')
    _poner(t, [(7, 7), (6, 6)], 'N')
    bc, nc = othello.contar_fichas(t)
    assert bc == 3
    assert nc == 2

def test_juego_terminado_por_tablero_lleno():
    t = _tablero_vacio()
    _poner(t, [(r, c) for r in range(8) for c in range(8)], 'B')

    # turno da igual, tablero lleno termina
    assert othello.juego_terminado(t, 'B') is True
    assert othello.juego_terminado(t, 'N') is True

def test_juego_terminado_sin_jugadas_para_ninguno():
    # armamos un tablero lleno de B con UNA X suelta, pero sin N en ningun lado
    # entonces no hay jugadas validas para nadie (pq no se puede encerrar nada)
    t = _tablero_vacio()
    _poner(t, [(r, c) for r in range(8) for c in range(8)], 'B')
    t[0][0] = 'X'

    assert othello.jugadas_validas(t, 'B') == {}
    assert othello.jugadas_validas(t, 'N') == {}
    assert othello.juego_terminado(t, 'B') is True

def test_cargar_partida_desde_archivo_ok(tmp_path):
    # uso tmp_path asi no ensuciamos el repo
    contenido = [
        "XXXXXXXX",
        "XXXXXXXX",
        "XXXXXXXX",
        "XXXBNXXX",
        "XXXNBXXX",
        "XXXXXXXX",
        "XXXXXXXX",
        "XXXXXXXX",
        "B",
    ]
    p = tmp_path / "partida.txt"
    p.write_text("\n".join(contenido), encoding="utf-8")

    tablero, turno = othello.cargar_partida_desde_archivo(str(p))
    assert turno == 'B'
    assert tablero[3][3] == 'B'
    assert tablero[3][4] == 'N'
    assert tablero[4][3] == 'N'
    assert tablero[4][4] == 'B'

def test_cargar_partida_desde_archivo_invalido_menos_lineas(tmp_path):
    p = tmp_path / "bad.txt"
    p.write_text("\n".join(["XXXXXXXX"] * 8), encoding="utf-8")
    with pytest.raises(Exception):
        othello.cargar_partida_desde_archivo(str(p))

def test_cargar_partida_desde_archivo_invalido_fila_corta(tmp_path):
    contenido = ["XXXXXXX"] + ["XXXXXXXX"] * 7 + ["B"]
    p = tmp_path / "bad.txt"
    p.write_text("\n".join(contenido), encoding="utf-8")
    with pytest.raises(Exception):
        othello.cargar_partida_desde_archivo(str(p))

def test_cargar_partida_desde_archivo_invalido_char_raro(tmp_path):
    contenido = ["XXXXXXXX"] * 3 + ["XXXQNXXX"] + ["XXXXXXXX"] * 4 + ["B"]
    p = tmp_path / "bad.txt"
    p.write_text("\n".join(contenido), encoding="utf-8")
    with pytest.raises(Exception):
        othello.cargar_partida_desde_archivo(str(p))

def test_cargar_partida_desde_archivo_invalido_turno(tmp_path):
    contenido = ["XXXXXXXX"] * 8 + ["Z"]
    p = tmp_path / "bad.txt"
    p.write_text("\n".join(contenido), encoding="utf-8")
    with pytest.raises(Exception):
        othello.cargar_partida_desde_archivo(str(p))
