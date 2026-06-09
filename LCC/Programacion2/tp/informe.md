# Trabajo practico final

## Programacion 2 - LCC - 2025

####  Detalles
- Alumno: Fabio Giampaoli
- DNI: 44733831
- Mesa: Diciembre 2025


### Uso
```c
// compilar:
gcc othello.c -o othello.out
// correr:
./othello.out ./input_tests/test_1.txt ./output_tests/test_1.txt
// testear:
gcc -g -DTESTING othello.c test_cases/test_othello.c -o test_othello.out
./test_othello.out
```

```python
# correr:
python ./othello.py ./output_tests/test_1.txt N 1
# testear:
pytest -q
```

### Programa en C

#### Objetivo
El programa debe pedir un archivo de entrada con un formato especial para cargar la configuracion inicial de un tablero del juego Othello.

Se valida tras cada jugada del archivo que cumplan con las reglas del juego. Para configuraciones invalidas, el programa indica el fallo, de lo contrario, genera un nuevo archivo con formato especial de como queda el tablero luego de procesar el archivo, a menos que el juego termine durante la misma validacion del archivo.

#### Estructuras
Al ser un tablero bidimencional de tamaños fijos, es sencillo representar la pocisicion de una celda como un par ordenado con el indice de la fila y columna bajo la estructura `Pos`

`Juego` al contener el color de cada jugador y el color del turno actual, nos permite usar y alternar la informacion del jugador actual en cada iteracion.

#### Auxiliares
Existen varias consultas comunes a lo largo del programa de verificacion para el flujo del juego.

Particularmente `obtener_direccion` fue pensada para retornar una posicion dada una direccion. La direccion (vista como un int del 0 al 7) representa mirar hacia arriba-izquierda, arriba, arriba-derecha, derecha, izquierda, abajo-izquierda, abajo, y abajo-derecha. Y la funcion retorna la posicion resultante de moverse en esa direccion desde una celda dada con un salto de uno.

#### Parseo
`parse_jugador` y `cargar_datos_iniciales` funcionan solo con un formato muy especifico de archivo de entrada ya que se asume que el formato no muta. De modo que si falla en alguna de las condiciones a la hora de inicializar la jugada, sea probablemente un archivo con un formato inesperado.

En ambos casos se pasa a `juego` por parametro como referencia, y no por valor, con el fin de poder cargarlo con valores y mutarlo en tiempo durante el juego, ya que la naturaleza de este estructura es que alterne el turno en cada iteracion de forma apropiada.

El tablero se representa como una matrix de 8x8 de strings debido a que resulta una representacion fiel a un tablero bidimencional, que nos permitiria movernos en el tablero mediante indexacion e iteracion de estos arrays.

#### Validaciones
Con cada jugada que se ingresa del tipo `CharInt`, es necesario validar que sea una jugada valida no solo segun las reglas del juego, sino para nuestro contexto. `parse_move` se encargaria de parsear dicho formato a dos indices validos de la columna y fila a los que corresponden en el tablero. Asi rechazamos jugadas que conseptualmente estarian mal como 'Y91', que es una celda que no existe en el tablero.

Notar que en C podemos directamente restar o comparar caracteres de forma "natural" en sentido de que al hacer estas operaciones, se utiliza el ordenal del caracter (un int que representa al caracter), que estan ordenados acorde a nuestro uso.
Por ejemplo, 'A' con un ordenal de 65 y 'B' un ordenal de 66, reprensenta un orden natural de que B es mayot que A, y la distancia entre ellos es de uno.
Resultando natural tambien que la distancia entre dos caracteres represente el indice en el tablero del primer caracter hasta el segundo.
Por ejemplo, la distancia entre 'H' y 'A' es 7, que 7 corresponde al indice de la ultima columna del tablero, a la columna 'H'.

En cuando a la validacion de las reglas del juego, el diseño esta pensado para ver que poner una ficha de un color en un tablero dado, produce cambios en tablero.
La intencion de `calcular_flips` es validar que para una jugada particular, cumpla con todas las reglas del juego (que encierre fichas del oponente en alguna direccion, y la ficha este contigua a una ficha del rival), retornando la cantidad de fichas que daria vuelta, y cargando en array, las fichas que tendria que dar vuelta.
Para validar esto, desde la celda en la que se quiere poner la ficha, tiene que mirar por cada direccion posible, que esa celda contigua sea valida (dentro del tablero y sea del rival). 
Si cumple esta primera condicion, podemos movernos en esa direccion, para validar que la celda siguiente en la misma direccion tambien es valida. Esto lo hacemos hasta que en esa direccion deje de haber celdas validas, guardando en cada iteracion, la celdas validas que fue encontrando en el camino de esa direccion.
Cuando deje de haber fichas rivales contiguas en esa direccion, tiene que validar que la siguiente ficha en esa direccion tambien sea valida (dentro del tablero), pero del jugador actual, para verificar que entre la celda que se quiere poner y la celda al final del camino, son propias y encierra al menos una ficha del rival.
Si al final de recorrer todo un camino se cumplen todas las reglas del juego explicadas, las posiciones que se fue encontrando en el camino que quedaron encerradas, se guardan en memoria (`flips`) para usarlas luego de la salida de la funcion.
Notar que encontrar un camino valido de fichas para voltear, no hace un retorno, sino que luego sigue mirando en las siguientes direcciones, para validar si hay que voltear fichas en mas de una direccion a la vez.

`hay_alguna_jugada_valida` sirve para ver si el color del turno, tiene algun movimiento valido en el tablero. Para validar esto, mira en cada celda vacia del tablero, y usa la funcion descrita antes (`calcular_flips`) para ver si poner una ficha en la celda actual, produce al menos un cambio en el tablero (retorna al menos una ficha para voltear).
Esto es ineficiente si el tablero llegara a ser mas grande porque tiene que hacer muchas iteraciones. Por ello tiene un early-stop, para que pare de iterar cuando encuentre una jugada.

Una funcion `validar_jugada` engloba la logica de las funciones previas.
Es decir, dada una jugada `CharInt`, valida que se pueda parsear correctamente, que cumpla con las reglas de juego para el tablero dado, y parsear tambien cuando un jugador pasa de turno.

Para verificar si hay algun jugador, independientemente del turno, preguntamos tras cada jugada, que el tablero este completo (sin celdas vacias). En el medio de esta validacion de cada celda va contanto las fichas de cada color. Si el tablero esta completo, el jugador con mas fichas sobre el tablero, resulta ganador.

### Dinamica
Al correr el programa se debe cumplir con su parametria.
Si corresponde, inicializa la partida de acuerdo al archivo de entrada,
y valida y modifica tras cada jugada el moviemente de cada turno.

Para alternar entre turnos, `procesar_jugadas` itera por cada linea del archivo de entrada desde las jugadas (luego de ya parsar jugadores y color inicial) y realiza estos pasos por cada jugada:
- Valida que la jugada sea valida (se pueda parsear y produzca cambios en el tablero). Termina el programa con error si es invalida.
- Si es valida, obtiene todas las celdas que tendria que voltear al poner la ficha en la celda dada. Tambien se considera valida pasar de turno solo si el jugador del turno no tiene jugadas validas disponibles.
- Voltea todas las fichas que correspondan con `aplicar_jugada`
- Verificar que estos cambios no hayan ocacionado el fin del juego. Si lo hace, informa el ganador
- Si el juego no termino, alterna el turno, para repetir el ciclo con la siguiente linea del archivo.

`aplicar_jugada` es una funcion que modifica el tablero, dadas las celdas que tiene que voltear y agregar.
Agrega la celda del turno a la posicion, y voltea las fichas que encierre, que se obtienen de las funciones descritas anteriormente.

cuando el archivo se quede sin lineas, el juego haya terminado, o alguna jugada invalida haya sido detectada, en el `main`, la funcion `escribir_tablero` va a procesar el tablero resultante de toda la partida, y va escribiendo en el archivo de salida indicado, celda por celda, el tablero en el formato indicado, y el turno que continua.

### Programa en Python

#### Objetivo
El programa deber pedir un archivo de entrada (resultado del programa de C) con el tablero de una jugada y el color que debe jugar.
Pedir al usuario que el archivo de la jugada, el color con el que quiere jugar, y el nivel de dificultad del rival (el progranma).

Iterar entre la jugada del usario y la maquina, pidiendo como entrada una jugada, validarla, y mutar el tablero si corresponde, hasta que el juego termine.

#### Parseos
El programa recibe parametros para iniciar a jugar. `validar_args` tomas los parametros del script, y valida uno a uno que correspondan al contexto que se requeire para cada argumento. El formato esperado es estricto, para que cualquier argumento que no corresponda al contexto del juego, retorne error.

Dada la ruta del archivo de entrada, se abre, y se valida el formato esperado (9 lineas con las primeras 8 con 8 caracteres y la ultima con un caracter). Si lo es, inicializa el tablero vacio, que se representa al igual que en C, como una array bidimencional (una lista de listas en python). Se producen errores si hay errores en el formato del archivo.
Si cada caracter del archivo es valido, los va agregando al tablero inicial con la ficha que indique el archivo en la celda del tablero, de modo que al terminar de ver cada caracter del archivo, el tablero queda cargado de acuerdo al archivo.

#### Dinamica

Luego de imprimir el tablero inicial de la jugada, se repite en ciclo hasta que se termine el juego, las siguientes llamadas:
- Verificar si el juego termino (mismo enfoque que en C, ver que el tablero no tenga X's, o ningun jugador tenga mas jugadas validas). Si termino, imprimir el resultado (mismo enfoque, contar las fichas de cada color, el que tenga mas, gana)
- Se obtiene el listado de jugadas valida para el turno dado el tablero. Tiene el mismo enfoque que el programa en C, ver que la celda esta vacia, y ponerla ahi retorna una diccionario de longitud mayor igual a 1 de fichas del rival a voltear para cada jugada valida. (utiliza la funcion `flips_de_jugada`). De no tener jugadas validas, se pasa de turno.
- Cuando el color del turno coincide con el color que escogio el usuario, se le pide al usario su jugada en forma de `CharInt`.
- Si coincide con el de la maquina, el programa genera una jugada en su turno
- Se alterna el turno

#### Validaciones y aplicacion

Para pedir una jugada al usuario, se le indica por pantalla cuando igresar su jugada, y `parsear_jugada` valida que tenga un formato valid de tipo `CharInt` dentro de los rangos del tablero, usando el mismo enfoque en C. Se le pedira una y otra vez una jugada al usuario hasta que esta sea valida, no solo en el parseo, sino tambien de acuerdo a las reglas del juego. 
Para verificar que una jugada es valida segun las reglas, se verifica que la jugada (ya parseada) pertencezca al mapeo de moviemntos validos. Es decir, si al haber obtenido las jugadas validas para esa jugada, se producen cambios validos en el tablero (se puede voltear al menos una ficha del rival).
Cuando el usario ingrese una jugada valida, `aplicar_jugada` agrega la ficha del turno actual, y voltea las fichas de `flips`, que indica las fichas del rival para voltear al poner en esa celda (mismo approach que C).

Para pedir una jugada a la maquina en su turno, se dispone de igual manera de las jugadas validas del turno.
Primero se le pide a la maquina su jugada.
- Para el nivel 0 de la maquina, escoge el elemento de forma aleatoria de las jugadas validas.
- Para el nivel 1, itera por cada jugada valida, hasta encontrar la jugada con mayor numero de volteos (se queda con la primera mas grande si hay repetidos). Esto lo hace iterando jugada a jugada comparando cual es la que tiene un diccionario de volteos con mas elementos.
Se aplica al tablero la jugada de la maquina en caso de pasar, con el mismo enfoque que antes.

`flips_de_jugada` esta diseñada con el mismo enfoque que en C.
Su proposito es verificar que la jugada sea valida implica :
- Que este dentro del tablero
- La celda este vacia
- Que al moverse hacia cualquiera de las direcciones, la celda target tambien cumpla lo anterior, y que ademas la ficha sea del rival.
- para cada direccion que cumpla esto, se desplaza en el tablero celda a celda en la direccion indicada, guardando en `flips` las fichas del oponente que estan en el camino.
- cuando deje de haber fichas del oponente, valida que la siguiente celda en la direccion sea una ficha valida y del turno actual
- si no se valida esto ultimo, no se agregan a `flips` las fichas de este camino
La unica diferencia conceptual es que no cuenta aqui dentro la cantidad de fichas a voltear como en C, ya que en python es mas facil contar desde afuera la cantidad de elementos de `flips` sin tener que acumular un contador dentro de la funcion
