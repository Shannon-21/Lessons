;; The first three lines of this file were inserted by DrRacket. They record metadata
;; about the language level of this file in a form that our tools can easily process.
#reader(lib "htdp-intermediate-reader.ss" "lang")((modname practica5p) (read-case-sensitive #t) (teachpacks ()) (htdp-settings #(#t constructor repeating-decimal #f #t none #f () #f)))
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

(define (cantAdmin lst)
  (cond
    [(empty? lst) 0]
    [else (if (esAdmin? (first lst))
              (+ 1 (cantAdmin (rest lst)))
              (cantAdmin (rest lst))
          )]
  )
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
  (cond
    [(empty? lst) empty]
    [else (cons (make-Usr (Usr-login (first lst)) "nula" (Usr-level (first lst)))
                (bloquearClaves (rest lst)))]
  )
)

(check-expect (intercala (list 1 2 3) (list "A" "B")) (list 1 "A" 2 "B" 3))
(check-expect (intercala (list "A" "B") (list 1 2 3) ) (list "A" 1 "B" 2 3))

(define (intercala lst1 lst2)
  (cond
    [(and (empty? lst1) (cons? lst2)) (cons (first lst2) (intercala (rest lst2) lst1))]
    [(empty? lst1) empty]
    [else (cons (first lst1) (intercala lst2 (rest lst1)))]
  )
)

(check-expect (ultimo (list 1 2 3)) 3)
(check-expect (ultimo (list 1 2)) 2)
(check-expect (ultimo (list 1)) 1)

(define (ultimo lst)
  (cond
    [(empty? lst) empty]
    [(empty? (rest lst)) (first lst)]
    [else (ultimo (rest lst))]
  )
)

(check-expect (listaCapicua (list 1)) #t)
(check-expect (listaCapicua (list 1 1)) #t)
(check-expect (listaCapicua (list 1 2 3 2 1)) #t)
(check-expect (listaCapicua (list 1 2)) #f)
(check-expect (listaCapicua (list 1 2 3)) #f)
(check-expect (listaCapicua (list 1 2 3 4 1)) #f)
(check-expect (listaCapicua (list 1 2 3 4 5 6 7 8)) #f)

(define (pop lst)
  (cond
    [(empty? lst) empty]
    [else (reverse (rest (reverse lst)))]
  )
)

(define (listaCapicua lst)
  (cond
    [(empty? lst) #t]
    [else (and
              (= (first lst) (ultimo lst))
              (listaCapicua (pop (rest lst)))
          )]
  )
)

    

      