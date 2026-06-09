;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname practica5a) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
;//////// ejercicio 5

; contiene? : Contactos, Contacto -> Booleano
; dada una lista de Contactos, determina si el contacto es un elemento de la misma
 
;(check-expect (contiene? '() "Marcos") #false)
;(check-expect (contiene? (cons "Sara" (cons "Pedro"  (cons "Esteban" '()))) "Marcos") #false)
;(check-expect (contiene? (cons "A" (cons "Marcos" (cons "C" '()))) "Marcos") #true)
;(check-expect (contiene? (cons "Juan" '()) "Marcos") #false)
;(check-expect (contiene? (cons "Marcos" '()) "Marcos") #true)
 
;(define (contiene? l contacto)
;  (cond
;    [(empty? l) #false]
;    [(cons? l) (if (string=? (first l) contacto)
;                   #true
;                   (contiene? (rest l) contacto))]
;    )
;)
;
;(define contacts (cons "Eugenia"
;  (cons "Lucía"
;    (cons "Dante"
;      (cons "Federico"
;        (cons "Marcos"
;          (cons "Gabina"
;            (cons "Laura"
;              (cons "Pamela" '())))))))))
;
;(contiene? contacts "Marcos")

;//// ejercicion 6

;(define (suma l)
;  (cond
;    [(empty? l) 0]
;    [else (+ (first l) (suma (rest l)))]
;  )
;)
;
;(define (pos? l)
;  (cond
;    [(empty? l) #f]
;    [(empty? (rest l)) (> (first l) 0)]
;    [else (and (> (first l) 0) (pos? (rest l)))]
;  )
;)
;
;(define (check-suma l)
;  (if (pos? l)
;      (suma l)
;      (error "the list is not composed of positive numbers")
;  )
;)
;
;(define (pares l)
;  (cond
;    [(empty? l) empty]
;    [else (if (even? (first l))
;              (cons (first l) (pares (rest l)))
;              (pares (rest l)))]
;  )
;)
;
;(define (eliminar l n)
;  (cond
;    [(empty? l) empty]
;    [else (if (= (first l) n)
;              (eliminar (rest l) n)
;              (cons (first l) (eliminar (rest l) n)))]
;  )
;)
;
;(define (raices l)
;  (cond
;    [(empty? l) empty]
;    [else (cons (sqr (first l)) (raices (rest l)))]
;  )
;)
;
;(define (distancias l)
;  (cond
;    [(empty? l) empty]
;    [else (cons (sqrt (+ (sqr (posn-x (first l))) (sqr (posn-y (first l))))) (distancias (rest l)))]
;  )
;)
;
;(define (prod l)
;  (cond
;    [(empty? l) 1]
;    [else (* (first l) (prod (rest l)))]
;  )
;)
;
;(define (maximo l)
;  (cond
;    [(empty? l) 0]
;    [else (if (< (first l) (maximo (rest l))) (maximo (rest l)) (first l))]
;  )
;)

;//// 30

(require 2htdp/image)
(require 2htdp/universe)

(define HIGH 500)
(define WIDHT 500)
(define SCENE (empty-scene HIGH WIDHT))

(define INIT empty)

(define (draw-points l)
   (cond
     [(empty? l) SCENE]
     [else
      (place-image
         (circle 20 "solid" "cyan")
         (posn-x (first l)) (posn-y (first l))
         (draw-points (rest l))
      )]
   )
)

(define (add-position l x y event)
  (cond
    [(string=? event "button-down") (cons (make-posn x y) l)]
    [else l]
  )
)

(define (key-handler l event)
  (cond
    [(string=? event "\b") (remove-first l)]
    [(string=? event "backspace") (remove-first l)]
    [else l]
  )
)

(define (remove-first l)
  (cond
    [(empty? l) empty]
    [else (rest l)]
  )
)

(big-bang INIT
  [to-draw draw-points]
  [on-mouse add-position]
  [on-key key-handler]
)

;//// 31

(define-struct Turno [anterior actual])
(define INIT-TURNO (make-Turno empty empty))

(define (count l)
  ; returns the number of elements of a list
  (local (
          (define (add e ac) (+ 1 ac))
         )
         (foldr add 0 l)
  )
)

(define (equal-list? l1 l2)
  ; true if two list has the same strings
  (cond
    [(not (= (count l1) (count l2))) #f]
    [(and (empty? l1) (empty? l2)) #t]
    [(and (string=? (first l1) (first l2)) (equal-list? (rest l1) (rest l2))) #t]
    [else #f]
  )
)

(define (take-n l n)
  (cond
    [(or (empty? l) (zero? n)) empty]
    [else (cons (first l) (take-n (rest l) (- n 1)))]
  )
)
    
(define (draw-turno turno)
  ; define what to show in the screen to the players
  (local (
          (define ANTERIOR (Turno-anterior turno))
          (define ACTUAL (Turno-actual turno))
          (define TURNO (string-append "Turno: Jugador " (if (even? (count ANTERIOR)) "1" "2")))
          (define TEXT (text (string-append
                              TURNO
                              ", Ultima: "
                              (if (cons? ANTERIOR) (first ANTERIOR) "-")
                             )
                             20
                             (if (even? (count ANTERIOR)) "red" "blue")))
          )
          (place-image/align
            TEXT
            (/ WIDHT 4) (/ HIGH 4)
            "center" "middle"
            SCENE
          )
  )
)

(define (memory-key turno event)
  (local (
          (define ANTERIOR (Turno-anterior turno))
          (define ACTUAL (Turno-actual turno))
         )
         (cond
           [(empty? ANTERIOR)
              (make-Turno (cons event ANTERIOR) empty)]
           [(= (count ACTUAL) (count ANTERIOR))
              (make-Turno (cons event ANTERIOR) empty)]
           [else
            (make-Turno ANTERIOR (cons event ACTUAL))]
         )
  )
)

(define (loose-game turno)
  (local (
          (define ANTERIOR (Turno-anterior turno))
          (define ACTUAL (Turno-actual turno))
         )
    (and
     (cons? ACTUAL)
     (cons? ANTERIOR)
     (= (count ACTUAL) (count ANTERIOR))
     (not (equal-list? ANTERIOR ACTUAL))
    )
  )
)

(define (final-scene turno)
  (local (
          (define ANTERIOR (Turno-anterior turno))
          (define ACTUAL (Turno-actual turno))
          (define perdedor (if (odd? (count ACTUAL)) "Jugador 2" "Jugador 1"))
          (define mensaje (text (string-append "¡Perdió " perdedor "!") 30 "black"))
         )
    (place-image/align
      mensaje
      (/ WIDHT 2) (/ HIGH 2)
      "center" "middle"
      SCENE)
  )
)

(big-bang INIT-TURNO
  [to-draw draw-turno]
  [on-key memory-key]
  [stop-when loose-game final-scene]
)




