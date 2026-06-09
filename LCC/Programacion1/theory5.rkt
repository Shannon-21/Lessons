;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname theory5) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(require test-engine/racket-tests)

(check-expect (sum `()) 0)
(check-expect (sum (list 1 2 3 4 5)) 15)

(define (sum list_of_numbers)
  (cond
    [(empty? list_of_numbers) 0]
    [(cons? list_of_numbers) (+ (first list_of_numbers)
                                (sum (rest list_of_numbers))
                             )]
   )
)

(check-expect (longitud empty) 0)
(check-expect (longitud (list 2 3 "hola")) 3)

(define (longitud l)
  (cond
    [(empty? l) 0]
    [(cons? l) (+  1 (longitud (rest l)))]
  )
)

(check-expect (positivos (list 1 2 -3)) 2)
(check-expect (positivos (list -1 -2)) 0)

(define (positivos l)
  (cond
    [(empty? l) 0]
    [(cons? l) (if (> (first l) 0)
                   (+ 1 (positivos (rest l)))
                   (+ 0 (positivos (rest l)))
    )])
)

(check-expect (coordenadas-x (list (make-posn 1 2))) (list 1))
(check-expect (coordenadas-x (list (make-posn 1 2) (make-posn -4 1))) (list 1 -4))

(define (coordenadas-x l)
  (cond
    [(empty? l) empty]
    [(cons? l) (cons (posn-x (first l)) (coordenadas-x (rest l)))]
  )
)