;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-lambda-reader.ss" "lang")((modname |TP FINAL|) (read-case-sensitive #t) (teachpacks ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp"))) (htdp-settings #(#t constructor repeating-decimal #f #t none #f ((lib "image.rkt" "teachpack" "2htdp") (lib "universe.rkt" "teachpack" "2htdp")) #f)))
#| Trabajo Práctico Final - Tema 1

Integrantes:
- [Parodi Aguado, Bautista]
- [Giampaoli, Fabio]
|#


;Funciones complementarias:

;add_bool: Boolean, List (List) ---> List (List)
;Agrega el booleano como primer elemento a cada lista de la lista de listas
;Casos Prueba:
(check-expect (add_bool #t (list empty)) (list (list #t)))
(check-expect (add_bool #t (list (list #f #t))) (list (list #t #f #t)))
(check-expect (add_bool #f (list (list "a" 1) (list 23 12))) (list (list #f "a" 1) (list #f 23 12)))

;Diseño
(define (add_bool bool list_of_lists)
  (local (
          ;add_local_bool: List (Any) --> List (Any)
          ;Agrega el booleano como primer elemento de la lista 
          (define (add_local_bool list) (cons bool list))
         )
         (map add_local_bool list_of_lists)
  )
)

;concat_list: List (Any), List (Any) ---> List (Any)
;Toma dos listas de cualquier tipo y crea una unica lista con la union de sus elementos
;Casos de prueba:
(check-expect (concat_lists (list empty) (list 1)) (list empty 1))
(check-expect (concat_lists (list empty) (list empty)) (list empty empty))
(check-expect (concat_lists (list 34 20 #f) (list #t #t)) (list 34 20 #f #t #t))

;Diseño:
(define (concat_lists list1 list2)
  (cond
    [(empty? list1) list2]
    [else (cons (first list1) (concat_lists (rest list1) list2))]
  )
)


;;;;;;;; Ejercicio 1

;implica: Boolean, Boolean ---> Boolean
;La funcion se comporta como el operador lógico de implicancia
;Devolviendo true en todos los casos, excepto cuando la conclusion es falsa y la premisa verdadera
;Casos de prueba
(check-expect (implica #f #f) #t)
(check-expect (implica #f #t) #t)
(check-expect (implica #t #f) #f)
(check-expect (implica #t #t) #t)

;Diseño:
(define (implica p q)
  (or (not p) q))

;equivalente: Boolean, Boolean ---> Boolean
;La funcion se comporta como un operador lógico de equivalencia
;Devolviendo true en los casos en los que la premisa y la conclusion tengan el mismo valor de verdad
;Casos de prueba
(check-expect (equivalente #f #f) #t)
(check-expect (equivalente #f #t) #f)
(check-expect (equivalente #t #f) #f)
(check-expect (equivalente #t #t) #t)

;Diseño:
(define (equivalente p q)
  (boolean=? p q))


;;;;;;;; Ejercicio 2

;valuaciones: Natural ---> List (List (Boolean))
;Dado un numero natural n, genera una lista de 2^n sublistas,
;con cada sublista de n elementos, cada sublista representa una posible combinacion
;de valores de verdad para cada proposicion
;Casos de prueba:
(check-expect (valuaciones 0) (list empty))
(check-expect (valuaciones 1) (list
                               (list #false)
                               (list #true)))
(check-expect (valuaciones 2) (list
                               (list #false #false)
                               (list #false #true)
                               (list #true #false)
                               (list #true #true)))
(check-expect (valuaciones 3) (list
                               (list #false #false #false)
                               (list #false #false #true)
                               (list #false #true #false)
                               (list #false #true #true)
                               (list #true #false #false)
                               (list #true #false #true)
                               (list #true #true #false)
                               (list #true #true #true)))

;Diseño
(define (valuaciones n)
  (cond
    [(zero? n) (list empty)]
    [else (concat_lists
           (add_bool #f (valuaciones (sub1 n)))
           (add_bool #t (valuaciones (sub1 n)))
          )]
  )
)


;;;;;;;; Ejercicio 3

; A : List(Boolean) -> Boolean
;representa la fórmula proposicional ((p -> q) /\ (t -> q)) <-> ((p \/ t) -> q)
;Caso concreto de prueba:
(check-expect (A (list #t #f #t)) #t)

;Diseño
(define (A l)
  (let ([p1 (first l)]
        [p2 (second l)]
        [p3 (third l)])
  (equivalente (and (implica p1 p3)
                    (implica p2 p3))
               (implica (or p1 p2) p3)
               )))

;B : List (Boolean) -> Boolean
;representa la fórmula proposicional ((p /\ s) -> q) <-> ((p -> q) /\ (t -> q))
;Caso concreto de prueba:
(check-expect (B (list #t #f #t)) #t)

;Diseño
(define (B l)
  (let ([p1 (first l)]
        [p2 (second l)]
        [p3 (third l)])
    (equivalente
     (implica (and p1 p2) p3)
     (and (implica p1 p3) (implica p2 p3)
    ))))

;C: List (Boolean) -> Boolean
;representa la fórmula proposicional ~(p \/ ~t) <-> (p /\ t)
;Caso concreto de prueba:
(check-expect (C (list #t #f)) #f)

;Diseño
(define (C l)
  (let (
    [p1 (first l)]
    [p2 (second l)]
   )
   (equivalente
    (or (not p1) (not p2))
    (and p1 p2)
   )
  )
)


;;;;;;;; Ejercicio 4

;evaluar: Function, Natural -> List (Boolean)
;Evalua una formula propocional (Funcion) en cada posible combiacion de sus valores de verdad.
;es decri, devuelve una lista con la última columna de la tabla de verdad de la preposicion.
;Casos de prueba
(check-expect (evaluar C 0) empty)
(check-expect (evaluar C 2) (list #f #f #f #f))
(check-expect (evaluar A 3) (list #t #t #t #t #t #t #t #t))

;Diseño
(define (evaluar P n)
  (if (zero? n)
      empty
      (map P (valuaciones n))))

;;;;;;;; Ejercicio 5

;tautologia?: Function, Natural-> Boolean
;Dada una formula propocional, devuelve #true si evalua #true para cada combinacion de sus variables posibles
;Casos de prueba
(check-expect (tautología? A 3) #t)
(check-expect (tautología? B 3) #f)
(check-expect (tautología? C 2) #f)

;Diseño
(define (tautología? prep n)
  (empty? (filter false? (evaluar prep n))))

;contradiccion?: Function, Natural-> Boolean
;Dada una formula propocional, devuelve #true si evalua #false para cada combinacion de sus variables posibles
;Casos de prueba
(check-expect (contradicción? A 3) #f)
(check-expect (contradicción? B 3) #f)
(check-expect (contradicción? C 2) #t)

;Diseño
(define (contradicción? prep n)
  (local (
          ;true?: Boolean -> Boolean
          ;Devuelve #t si el booleano es verdadero
          ;Diseño
          (define (true? b) (and b #t))
         ) 
    (empty? (filter true? (evaluar prep n)))))

;satisfactible?: Function, Natural -> Boolean
;Dada una formula propocional, devuelve #true si evalua #true para al menos una combinacion de sus variables posibles
;Casos de prueba
(check-expect (satisfactible? A 3) #t)
(check-expect (satisfactible? B 3) #t)
(check-expect (satisfactible? C 2) #f)

;Diseño
(define (satisfactible? P n)
  (local (
          ;local-or: Boolean Boolean -> Boolean
          ;Devuelve #t si p o q es verdadera
          ;Diseño
          (define (local-or p q) (or p q))
         )
  (foldr local-or #f (evaluar P n))))


;;;;;;;; Ejercicio 6

;;;; Ejemplos de fórmulas proposicionales

; D : List(Boolean) -> Boolean
; D representa la fórmula proposicional p
(define
  (D l)
  (first l))

; E : List(Boolean) -> Boolean
; E representa la fórmula proposicional p \/ ~p 
(define
  (E l)
  (let ([p (first l)])
  (or p (not p))))

; F : List(Boolean) -> Boolean
; F representa la fórmula proposicional p /\ ~p 
(define
  (F l)
  (let ([p (first l)])
  (and p (not p))))

; MP : List(Boolean) -> Boolean
; MP representa la fórmula proposicional ((p -> q) /\ p) -> q
; conocida como modus ponens.
(define
  (MP l)
  (let ([p (first l)]
        [q (second l)])
  (implica (and (implica p q) p) q)))

; MT : List(Boolean) -> Boolean
; MT representa la fórmula proposicional ((p -> q) /\ ~q) -> ~p
; conocida como modus tollens.
(define
  (MT l)
  (let ([p (first l)]
        [q (second l)])
  (implica (and (implica p q) (not q)) (not p))))

; DM1 : List(Boolean) -> Boolean
; DM1 representa la fórmula proposicional ~(p \/ q) <-> (~p /\ ~q)
; que constituye una de las leyes de morgan.
(define
  (DM1 l)
  (let ([p (first l)]
        [q (second l)])
  (equivalente (not (or p q))
               (and (not p) (not q)))))

; G : List(Boolean) -> Boolean
; G representa la fórmula proposicional p1 /\ ~ p2 /\ (p1 -> ~p4) /\ (p2 \/ p3) /\ (p3 -> p4)
(define
  (G l)
  (let ([p1 (first l)]
        [p2 (second l)]
        [p3 (third l)]
        [p4 (fourth l)])
  (and p1
       (not p2)
       (implica p1 (not p4))
       (or p2 p3)
       (implica p3 p4))))

; H : List(Boolean) -> Boolean
; H representa la fórmula proposicional ((p1 \/ p2) -> p3) /\ (~p3 \/ ~p4)
(define
  (H l)
  (let ([p1 (first l)]
        [p2 (second l)]
        [p3 (third l)]
        [p4 (fourth l)])
  (and (implica (or p1 p2) p3)
       (or (not p3) (not p4)))))

; I : List(Boolean) -> Boolean
; I representa la fórmula proposicional
; ((p1 \/ ~p2) -> (p5 \/ (p1 /\ p3 /\ ~p4))) <-> (~(~p1 \/ ~p3 \/ p4 \/ p5) -> (~p1 \/ ~p2))
(define
  (I l)
  (let ([p1 (first l)]
        [p2 (second l)]
        [p3 (third l)]
        [p4 (fourth l)]
        [p5 (fifth l)])
  (equivalente
    (implica (or p1 (not p2))
             (or p5 (and p1 p3 (not p4))))
    (implica (not (or (not p1) (not p3) p4 p5))
             (or (not p1) (not p2))))))

;;;; Tests para ejercicio 4

; ocurrencias : List(X) X -> Natural
; Dados una lista l de elementos de tipo X y un elemento v de tipo
; X, devuelve la cantidad de veces que v aparece en l.
(define
  (ocurrencias l v)
  (length (filter (lambda (x) (equal? x v)) l)))

(check-expect (ocurrencias (evaluar A 3) #t) 8)
(check-expect (ocurrencias (evaluar A 3) #f) 0)
(check-expect (ocurrencias (evaluar B 3) #t) 6)
(check-expect (ocurrencias (evaluar B 3) #f) 2)
(check-expect (ocurrencias (evaluar C 2) #t) 0)
(check-expect (ocurrencias (evaluar C 2) #f) 4)
(check-expect (ocurrencias (evaluar D 1) #t) 1)
(check-expect (ocurrencias (evaluar D 1) #f) 1)
(check-expect (ocurrencias (evaluar E 1) #t) 2)
(check-expect (ocurrencias (evaluar E 1) #f) 0)
(check-expect (ocurrencias (evaluar F 1) #t) 0)
(check-expect (ocurrencias (evaluar F 1) #f) 2)
(check-expect (ocurrencias (evaluar MP 2) #t) 4)
(check-expect (ocurrencias (evaluar MP 2) #f) 0)
(check-expect (ocurrencias (evaluar MT 2) #t) 4)
(check-expect (ocurrencias (evaluar MT 2) #f) 0)
(check-expect (ocurrencias (evaluar DM1 2) #t) 4)
(check-expect (ocurrencias (evaluar DM1 2) #f) 0)
(check-expect (ocurrencias (evaluar G 4) #t) 0)
(check-expect (ocurrencias (evaluar G 4) #f) 16)
(check-expect (ocurrencias (evaluar H 4) #t) 6)
(check-expect (ocurrencias (evaluar H 4) #f) 10)
(check-expect (ocurrencias (evaluar I 5) #t) 21)
(check-expect (ocurrencias (evaluar I 5) #f) 11)

;;;; Tests para ejercicio 5

(check-expect (tautología? A 3) #t)
(check-expect (tautología? B 3) #f)
(check-expect (tautología? C 2) #f)
(check-expect (tautología? D 1) #f)
(check-expect (tautología? E 1) #t)
(check-expect (tautología? F 1) #f)
(check-expect (tautología? MP 2) #t)
(check-expect (tautología? MT 2) #t)
(check-expect (tautología? DM1 2) #t)
(check-expect (tautología? G 4) #f)
(check-expect (tautología? H 4) #f)
(check-expect (tautología? I 5) #f)

(check-expect (contradicción? A 3) #f)
(check-expect (contradicción? B 3) #f)
(check-expect (contradicción? C 2) #t)
(check-expect (contradicción? D 1) #f)
(check-expect (contradicción? E 1) #f)
(check-expect (contradicción? F 1) #t)
(check-expect (contradicción? MP 2) #f)
(check-expect (contradicción? MT 2) #f)
(check-expect (contradicción? DM1 2) #f)
(check-expect (contradicción? G 4) #t)
(check-expect (contradicción? H 4) #f)
(check-expect (contradicción? I 5) #f)

(check-expect (satisfactible? A 3) #t)
(check-expect (satisfactible? B 3) #t)
(check-expect (satisfactible? C 2) #f)
(check-expect (satisfactible? D 2) #t)
(check-expect (satisfactible? E 1) #t)
(check-expect (satisfactible? F 1) #f)
(check-expect (satisfactible? MP 2) #t)
(check-expect (satisfactible? MT 2) #t)
(check-expect (satisfactible? DM1 2) #t)
(check-expect (satisfactible? G 4) #f)
(check-expect (satisfactible? H 4) #t)
(check-expect (satisfactible? I 5) #t)

