;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname tp_tema1) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
;// 1
(define (implica p q)
  (or (not p) q))

(define (equivalente p q)
  (and (implica p q) (implica q p)))

;// 2
(define (add_bool bool list_of_lists)
  (local (
          (define (add_local_bool list) (cons bool list))
         )
         (map add_local_bool list_of_lists)
  )
)

(define (concat_lists list1 list2)
  (cond
    [(empty? list1) list2]
    [else (cons (first list1) (concat_lists (rest list1) list2))]
  )
)

(define (valuaciones n)
  (cond
    [(zero? n) (list empty)]
    [else (concat_lists
           (add_bool #t (valuaciones (sub1 n)))
           (add_bool #f (valuaciones (sub1 n)))
          )]
  )
)

;// 3
(define (A l)
  (let (
    [p1 (first l)]
    [p2 (second l)]
    [p3 (third l)]
   )
   (equivalente
    (and (implica p1 p3)
         (implica p2 p3))
    (implica (or p1 p2) p3)
   )
  )
)

(define (B l)
  (let (
    [p1 (first l)]
    [p2 (second l)]
    [p3 (third l)]
   )
   (equivalente
    (implica (or p1 p2) p3)
    (or
     (implica p1 p3)
     (implica p2 p3)
    )
   )
  )
)

(define (C l)
  (let (
    [p1 (first l)]
    [p2 (second l)]
   )
   (equivalente
    (or (not p1) (not p2))
    (or p1 p2)
   )
  )
)

;// 4
(define (evaluar P n)
  (map P (valuaciones n))
)

;// 5
(define (all_equals list result_bool)
  (local (
           (define (bool_func p q)
             (cond
               [result_bool (and p q)]
               [(not result_bool) (and (not p) (not q))]
             )
           )
          )
          (cond
            [(empty? list) result_bool]
            [else (bool_func (first list) (all_equals (rest list) result_bool))]
          )
  )
)

(define (satisfacible? P n)
  (local ((define (local-or p q) (or p q)))
  (foldr local-or #f (evaluar P n)))
)
  
;(define (toutología? P)
  
  


