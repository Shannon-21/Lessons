;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname theory6) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
;// 1
(define (intervaloAsc n)
  (cond
    [(zero? n) (list 0)]
    [else (append (intervaloAsc (sub1 n)) (list n))]
  )
)

;// 2
(define (igualNat? n1 n2)
  (cond
    [(and (zero? n1) (zero? n2)) #t]
    [(or (zero? n1) (zero? n2)) #f]
    [else (igualNat? (sub1 n1) (sub1 n2))]
  )
)

;// 3
(define (mayorNat? n1 n2)
  (cond
    [(and (zero? n1) (zero? n2)) #f]
    [(and (positive? n1) (zero? n2)) #t]
    [(and (zero? n1) (positive? n2)) #f]
    [else (mayorNat? (sub1 n1) (sub1 n2))]
  )
)

;// 4
(define (difNat n1 n2)
  (cond
    [(igualNat? n1 n2) 0]
    [(zero? n1) n2]
    [(zero? n2) n1]
    [else (difNat (sub1 n1) (sub1 n2))]
  )
)

;// 5
(define (contarElem lst)
  (cond
    [(empty? lst) 0]
    [else (add1 (contarElem (rest lst)))]
  )
)

;// 6
(define (contarElem-f lst)
  (local (
          (define (local-add1 n m) (add1 m))
         )
    (foldr local-add1 0 lst)
  )
)

;// 7
(define (nElementos? n lst)
  (igualNat? n (contarElem lst))
)

;// 8
(define (transformaN n f l)
  (cond
    [(empty? l) empty]
    [(zero? n) l]
    [else (cons (f (first l)) (transformaN (sub1 n) f (rest l)))]
  )
)

