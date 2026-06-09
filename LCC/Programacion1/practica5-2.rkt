;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname practica5-2) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
;(define (distintos-0 lst)
;  (local (
;    (define (distinto-0? n) (not (= 0 n)))
;    )
;    (filter distinto-0? lst)
;  )
;)
;
;(define (sumacuad lst)
;  (foldr + 0 (map sqr lst))
;)
;
;(define (multPos lst)
;  (foldr * 1 (filter positive? lst))
;)

(define (algun-pos lst)
  (local (
      (define (sum lst) (foldr + 0 lst))
      (define (sumIsPos? lst) (positive? (sum lst)))
      (define (alguna-es-positiva sub a) (or (sumIsPos? sub) a))
    )
    (foldr alguna-es-positiva #false lst)
  )
)

(define (long-lists lst)
  (local (
      (define (count lst) (cond [(empty? lst) 0] [else (+ 1 (count (rest lst)))]))
      (define (long? lst) (> (count lst) 4))
      (define (some-long? lst acc) (or (long? lst) acc))
    )
    (foldr some-long? #false lst)
  )
)

(define-struct alumno [nombre nota faltas])

(define (destacados lst)
  (local (
     (define (destacado? alm) (>= (alumno-nota alm) 9))
     (define (take-name alm) (alumno-nombre alm))
   )
   (map take-name (filter destacado? lst))
  )
)

(define (condicion alm)
  (cond
    [(>= (alumno-nota alm) 8) "promovido"]
    [(< (alumno-nota alm) 6) "libre"]
    [else "regular"]
  )
)

(define (promovidos-ausentes lst)
  (local (
      (define (take-name alm) (alumno-nombre alm))
      (define (promovido? alm) (string=? "promovido" (condicion alm)))
      (define (inasistio? alm) (>= (alumno-faltas alm) 3))
    )
    (map take-name (filter promovido? (filter inasistio? lst)))
  )
)
  


   
