;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname practica6) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
;// 1
(define (suma n1 n2)
  (cond
    [(zero? n2) n1]
    [(zero? n1) n2]
    [else (suma (add1 n1) (sub1 n2))]
  )
)

;// 2
(define (mult n1 n2)
  (cond
    [(or (zero? n1) (zero? n2)) 0]
    [(zero? (sub1 n2)) n1]
    [else (suma n1 (mult n1 (sub1 n2)))]
  )
)

;// 3
(define (expo n1 n2)
  (cond
    [(zero? n1) 0]
    [(zero? n2) 1]
    [(zero? (sub1 n2)) n1]
    [else (mult n1 (expo n1 (sub1 n2)))]
  )
)

;// 4
(define (fact n)
  (cond
    [(zero? n) 0]
    [(zero? (sub1 n)) 1]
    [else (mult n (fact (sub1 n)))]
  )
)

;// 5
(define (fib n)
  (cond
    [(zero? n) 1]
    [(zero? (sub1 n)) 1]
    [else (suma (fib (sub1 (sub1 n))) (fib (sub1 n)))]
  )
)

;// 6
(define (sigma n f)
  (cond
    [(zero? n) (f n)]
    [else (suma (f n) (sigma (sub1 n) f))]
  )
)

;// 8
(define (componer f n x)
  (cond
    [(zero? n) x]
    [else (componer f (sub1 n) (f x))]
  )
)

;// 9
(define (intervalo n)
  (cond
    [(zero? n) (list 0)]
    [else (cons n (intervalo (sub1 n)))]
  )
)

;// 10
(define (multiplos n m)
  (cond
    [(zero? n) empty]
    [else (cons (mult m n) (multiplos (sub1 n) m))]
  )
)

;// 11
(define (list-fibonacci-map n)
  (map fib (intervalo n))
)

(define (list-fibonacci-rec n)
  (cond
    [(zero? n) (list 1)]
    [(zero? (sub1 n)) (list 1 1)]
    [else (cons
           (suma
            (first (list-fibonacci-rec (sub1 n)))
            (first (list-fibonacci-rec (sub1 (sub1 n))))
           )
           (list-fibonacci-rec (sub1 n))
          )]
  )
)

;// 12
(define (aux t n c i)
  (cond
    [(> c n) empty]
    [else (cons
           (+ (/ t n) (* (/ t n) (/ i (* 100  12)) c))
           (aux t n (add1 c) i)
          )]
  )
)

(define (cuotas total n i)
  (aux total n 1 i)
)

;// 13
(require 2htdp/image)

(define (circles-aux m c-m)
  (cond
    [(zero? c-m) (place-image
                  (square (* 2 (sqr m)) "outline" "black")
                  (/ (* 2 (sqr m)) 2) (/ (* 2 (sqr m)) 2)
                  (square (* 2 (sqr m)) "solid" "white")
                 )]
    [else (place-image/align
           (circle (sqr c-m) "outline" "blue")
           (sqr m) (sqr m) "center" "center"
           (circles-aux m (sub1 c-m))
          )]
  )
)

(define (circulos m)
  (circles-aux m m)
)

;// 14
(define (cuadrados-aux m c-m ang c-ang)
  (cond
    [(zero? c-m) (place-image
                  (square 200 "outline" "black")
                  (/ 200 2) (/ 200 2)
                  (square 200 "solid" "white")
                 )]
    [else (place-image/align
           (rotate c-ang (square (sqr c-m) "outline" "blue"))
           (sqr m) (sqr m) "center" "center"
           (cuadrados-aux m (sub1 c-m) ang (+ c-ang 20))
          )]
  )
)

(define (cuadrados m ang)
  (cuadrados-aux m m ang ang)
)

;////////
(define (list-ith l i)
  (cond
    [(empty? l) "indice inválido"]
    [(zero? i) (first l)]
    [else (list-ith (rest l) (sub1 i))]
  )
)

;// 15
(define (list-insert-aux f-l c-l x i)
  (cond
    [(empty? c-l) (append f-l (list x))]
    [(zero? i) (append f-l (cons x c-l))]
    [else (list-insert-aux (append f-l (list (first c-l))) (rest c-l) x (sub1 i))]
  )
)

(define (list-insert l x i)
  (cond
    [(zero? i) (cons x l)]
    [(empty? l) (list x)]
    [else (list-insert-aux (list (first l)) (rest l) x (sub1 i))]
  )
)

;// 16
(define (tomar-aux r-list c-list n)
  (cond
    [(zero? n) c-list]
    [(empty? r-list) (append c-list r-list)]
    [else (tomar-aux (rest r-list) (append c-list (list (first r-list))) (sub1 n))]
  )
)

(define (tomar list n)
  (cond
    [(or (zero? n) (empty? list)) empty]
    [else (tomar-aux list empty n)]
  )
)

;// 17
(define (eliminar-n-aux f-list r-list e n)
  (cond
    [(zero? n) (append r-list f-list)]
    [(empty? f-list) r-list]
    [else (eliminar-n-aux
           (rest f-list)
           (if (= (first f-list) e) r-list (cons (first f-list) r-list))
           e
           (if (= (first f-list) e) (sub1 n) n)
          )]
  )
)

(define (eliminar-n list e n)
  (cond
    [(empty? list) empty]
    [(zero? n) list]
    [else (eliminar-n-aux list empty e n)]
  )
)

;// 18
(define (member-n list x n)
  (cond
    [(and (empty? list) (zero? n)) #t]
    [(and (empty? list) (positive? n)) #f]
    [(zero? n) #f]
    [else (member-n (rest list) x (if (= (first list) x) (sub1 n) n))]
  )
)
