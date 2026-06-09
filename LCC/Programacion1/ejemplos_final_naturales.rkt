;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname ejemplos_final_naturales) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
;// 1
(define (f n)
  (cond
    [(zero? n) 0]
    [(zero? (sub1 n)) 2]
    [(zero? (sub1 (sub1 n))) 5]
    [else (+ (f (sub1 n)) (* 2 (f (sub1 (sub1 (sub1 n))))))]
  )
)

(define (intervalo n)
  (cond
    [(zero? n) (list 0)]
    [else (append (intervalo (sub1 n)) (list n))]
  )
)

(define (Fs n)
  (map f (intervalo n))
)

(check-expect (Fs 5) (list 0 2 5 5 9 19))
(check-expect (Fs 0) (list 0))

;// 2
(require 2htdp/image)

(define (dibujar-elipses-aux n c-n)
  (cond
    [(zero? c-n) (square 300 "solid" "white")]
    [else (place-image/align
           (rotate (* 2 c-n) (ellipse (* 10 c-n) (* 5 c-n) "outline" "blue"))
           150 150 "center" "center"
           (dibujar-elipses-aux n (sub1 c-n))
          )]
  )
)

(define (dibujar-elipses n)
  (cond
    [(zero? n) (square 300 "solid" "white")]
    [else (dibujar-elipses-aux n n)]
  )
)

;// 3
(define (p-a n c)
  (cond [(< n (* c c)) #t]
        [(zero? (modulo n c)) #f]
        [else (p-a n (add1 c))]))
 
(define (prime? n) (p-a n 2))

(define (g-a x y n)
  (cond
    [(and (prime? x) (prime? y) (= (+ x y) n)) (make-posn x y)]
    [(and (not (prime? x)) (not (prime? y))) (g-a (sub1 x) (sub1 y) n)]
    [else (g-a (sub1 x) y n)]
  )
)

(define (goldbach n)
  (cond
    [(or (<= n 4) (odd? n)) (error "Expected n >= 4")]
    [else (g-a (sub1 n) (sub1 (sub1 n)) n)]
  )
)

;// 4
(define (aprox-pi-aux n)
  (cond
    [(zero? n) 0]
    [else (+ (/ 1 (sqr n)) (aprox-pi-aux (sub1 n)))]
  )
)
  
(define (aprox-pi n)
  (cond
    [(zero? n) (sqrt 6)]
    [else (sqrt (* 6 (aprox-pi-aux n)))]
  )
)



         