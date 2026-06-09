;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname practica5-2-paper) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
(define-struct Usr [login pass level])
(define ADMIN 0)
(define USER 1)

(define ANA (make-Usr "ana" "12345678" ADMIN))
(define LUIS (make-Usr "luis" "12345678" USER))
(define MARTA (make-Usr "marta" "R34dlsoA" ADMIN))
(define L1 (list ANA LUIS))
(define L2 (list ANA LUIS MARTA))

(check-expect (cambioClave ANA "aaa") ANA)
(check-expect (cambioClave ANA "12345678") ANA)
(check-expect (cambioClave ANA "abcdefghi") (make-Usr "ana""abcdefghi" ADMIN))

(define (cambioClave usr newPass)
  (if (and
       (>= (string-length newPass) 8)
       (not (string=? newPass (Usr-pass usr)))
      )
      (make-Usr (Usr-login usr) newPass (Usr-level usr))
      usr
  )
)

(check-expect (agregarUsr "marta" "R34dlsoA" ADMIN L1) L2)
(check-expect (agregarUsr "luis" "R34dlsoA" ADMIN L1) L1)
(check-expect (agregarUsr "marta" "R34dlsoA" ADMIN empty) (list MARTA))

(define (agregarUsr login pass level lst)
  (cond
    [(empty? lst) (list (make-Usr login pass level))]
    [else (if (string=? login (Usr-login (first lst)))
              lst
              (cons (first lst) (agregarUsr login pass level (rest lst))))]
  )
)

(check-expect (esAdmin? ANA) #t)
(check-expect (esAdmin? LUIS) #f)

(define (esAdmin? usr)
  (= ADMIN (Usr-level usr))
)

(check-expect (cantAdmin L2) 2)
(check-expect (cantAdmin (list LUIS)) 0)
(check-expect (cantAdmin empty) 0)

(define (count lst)
    (local (
         (define (element? lst acc) (+ 1 acc))
       )
       (foldr element? 0 lst)
     )
 )

(define (cantAdmin lst)
  ;(cond
  ;  [(empty? lst) 0]
  ;  [else (if (esAdmin? (first lst))
  ;            (+ 1 (cantAdmin (rest lst)))
  ;            (cantAdmin (rest lst))
  ;        )]
  ;)
  (count (filter esAdmin? lst))
)

(check-expect (eliminaUsr "marta" L2) L1)
(check-expect (eliminaUsr "daniel" L2) L2)
(check-expect (eliminaUsr "marta" empty) empty)

(define (eliminaUsr login lst)
  (cond
    [(empty? lst) empty]
    [else (if (not (string=? (Usr-login (first lst)) login))
              (cons (first lst) (eliminaUsr login (rest lst)))
              (eliminaUsr login (rest lst))
           )]
  )
)

(check-expect (bloquearClaves L1) (list
                                   (make-Usr "ana" "nula" ADMIN)
                                   (make-Usr "luis" "nula" USER)))
(check-expect (bloquearClaves empty) empty)

(define (bloquearClaves lst)
  ;(cond
  ;  [(empty? lst) empty]
  ;  [else (cons (make-Usr (Usr-login (first lst)) "nula" (Usr-level (first lst)))
  ;              (bloquearClaves (rest lst)))]
  ;)
  (local (
       (define (bloquear-clave usr) (make-Usr (Usr-login usr) "nula" (Usr-level usr)))
     )
     (map bloquear-clave lst)
  )
)

(check-expect (idLargos (list ANA LUIS MARTA)) (list "luis" "marta"))
(check-expect (idLargos (list ANA)) empty)

(define (idLargos lst)
  (local (
      (define (take-login usr) (Usr-login usr))
      (define (mayor-3? usr) (> (string-length (take-login usr)) 3))
    )
    (map take-login (filter mayor-3? lst))
  )
)

(check-expect (minimo (list -1.6 5 3 -80 6 57.9 0)) -80)

(define (minimo lst)
  (foldr min (first lst) (rest lst))
)

(check-expect (primeroPares (list 9 -5 6 3 -2 8 0 12 100 7))
(list 6 -2 8 0 12 100 9 -5 3 7))

(define (primeroPares lst)
  (local (
      (define impares (filter odd? lst))
      (define pares (filter even? lst))
    )
    (foldr cons impares pares)
  )
)
      
  

