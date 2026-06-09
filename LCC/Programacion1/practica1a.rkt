#lang racket
(require 2htdp/image)

; // 1.0

(define (fizz-buzz-game n)
  #| Returns "Fizz" if n / 3 = 0, "Buzz" if n / 5 = 0, "FizBuzz" if n / 15 = 0, otherwise, returns n
     fizz-buzz-game : Number -> Number/String |#

  (cond
    [(= (modulo n 15) 0) "FizzBuzz"]
    [(= (modulo n 3) 0) "Fizz"]
    [(= (modulo n 5) 0) "Buzz"]
    [else n]
  )
 )

;// 1.1

(define (notebook-discount qty)
  #| Returns the total amount in notebooks with the promotion of 10% off when qty > 4
     notebook-discount : Number -> Number |#

  (define NOTEBOOK-PRICE 60)
  (define NOTEBOOK-DISCOUNT-PERCENTAGE 0.10)
  (if (< qty 4)
      (* NOTEBOOK-PRICE qty)
      (* (* NOTEBOOK-PRICE (- 1 NOTEBOOK-DISCOUNT-PERCENTAGE)) qty)
  )
)

;// 1.3

(define (exercise-1 hight widht)
  #| Returns "Angosta" if hight >= width, otherwise, "Ancha"
     exercise-1 : Number, Number - > String |#

  (if (>= hight widht) "Angosta" "Ancha")
)

(define (exercise-2 hight widht)
  #| Returns "Angosta" if hight >= width, otherwise, "Ancha"
     exercise-1 : Number, Number - > String |#

  (cond
    [(> hight widht) "Angosta"]
    [(< hight widht) "Ancha"]
    [else "Cuadrada"]
  )
)

(define (exercise-3 a b c)
  #| Returns the classification of the triangle given the three intern angles
     exercise-3 : Number, Number, Number -> String |#
  
  (cond
    [(and (= a b) (= b c)) "Equilatero"]
    [(and (not (= a b)) (not (= b c)) (not (= a c))) "Escaleno"]
    [else "Isoceles"]
  )
)

(define (exercise-4 a b c)
  #| Returns the classification of the triangle given the three intern angles
     exercise-3 : Number, Number, Number -> String |#
      
  (cond
    [(not(= (+ a b c) 180)) "It is not a triangle"]
    [(and (= a b) (= b c)) "Equilatero"]
    [(and (not (= a b)) (not (= b c)) (not (= a c))) "Escaleno"]
    [else "Isoceles"]
  )
)

(define NOTEBOOK-PRICE 60)
(define PENCIL-PRICE 8)

(define NOTEBOOK-QTY-THRESHOLD 4)
(define PENCIL-QTY-THRESHOLD 5)
(define TOTAL-QTY-THRESHOLD 10)

(define NOTEBOOK-DISCOUNT-PERCENTAGE 0.10)
(define PENCIL-DISCOUNT-PERCENTAGE 0.15)
(define TOTAL-DISCOUNT-PERCENTAGE 0.18)

(define (apply-discount price discount)
  #| Returns the price with the discount applied
     apply-discount : Number, Number -> Number |#

  (* price (- 1 discount))
)

(define (calculate-amount price qty [discount 0] [qty-threshold 0])
  #| Returns the amount of the purchase applyng the discount when threshold is reached
     calculate-amount : Number, Number, Number, Number -> Number |#

  (if (< qty qty-threshold)
      (* qty price)
      (* qty (apply-discount price discount))
  )
)

(define (exercise-5 notebook-qty pencil-qty)
  #| Returns the total amount of the buy of notebooks and pencils
     applyng the offers of 10% on NOTEBOOK-PRICE when notebook-qty >= 4
     and 15% on PENCIL-PRICE when pencil-qty >= 5.
     exercise-5 : Number, Number -> Number |#

  (+
   (calculate-amount NOTEBOOK-PRICE notebook-qty NOTEBOOK-DISCOUNT-PERCENTAGE NOTEBOOK-QTY-THRESHOLD)
   (calculate-amount PENCIL-PRICE pencil-qty PENCIL-DISCOUNT-PERCENTAGE PENCIL-QTY-THRESHOLD)
  )
)

(define (exercise-6 notebook-qty pencil-qty)
  #| Returns the total amount of the buy of notebooks and pencils
     applyng the offers of 10% on NOTEBOOK-PRICE when notebook-qty >= 4
     and 15% on PENCIL-PRICE when pencil-qty >= 5
     or 18% on the total when notebook-qty + pencil-qty >= 10.
     Apply the greater discount, they are not acumulative.
     exercise-6 : Number, Number -> Number |#

  (define TOTAL-QTY (+ notebook-qty pencil-qty))
  (define TOTAL-AMOUNT-WITH-DISCOUNTS (exercise-5 notebook-qty pencil-qty))
  (define TOTAL-AMOUNT (+ (* NOTEBOOK-PRICE notebook-qty) (* PENCIL-PRICE pencil-qty)))
  (define TOTAL-AMOUNT-WITH-TOTAL-DISCOUNT (apply-discount TOTAL-AMOUNT TOTAL-DISCOUNT-PERCENTAGE))
  
  (if (and (>= TOTAL-QTY TOTAL-QTY-THRESHOLD)(>= TOTAL-AMOUNT-WITH-TOTAL-DISCOUNT TOTAL-AMOUNT-WITH-DISCOUNTS))
      TOTAL-AMOUNT-WITH-DISCOUNTS
      TOTAL-AMOUNT-WITH-TOTAL-DISCOUNT
  )
)

(define (collantz n)
  #| Returns n/2 if n is odd, 3*n+1 if n is even
     collantz : Number - > Nomber |#

  (define IS-ODD (= (modulo n 2) 0))

  (if IS-ODD
      (/ n 2)
      (+ (* 3 n) 1)
  )
)

; // 2

(define (build-three-line-flag color-a color-b color-c [is-vertical #t])
  #| Returns an image of a rectangle flag with three lines of differents colors
     that can be horizontal o vertical distributed
     build-three-line-flag : String, String, String -> Image |#
  
  (define HIGHT 60)
  (define WIDHT 90)

  (define HIGHT-REC (if is-vertical HIGHT (/ HIGHT 3)))
  (define WIDHT-REC (if is-vertical (/ WIDHT 3) WIDHT))

  (define REC-A (rectangle WIDHT-REC HIGHT-REC "solid" color-a))
  (define REC-B (rectangle WIDHT-REC HIGHT-REC "solid" color-b))
  (define REC-C (rectangle WIDHT-REC HIGHT-REC "solid" color-c))

  (define POS-X-A (if is-vertical (/ WIDHT 6) (/ WIDHT 2)))
  (define POS-Y-A (if is-vertical (/ HIGHT 2) (/ HIGHT 6)))

  (define POS-X-B (if is-vertical (* POS-X-A 3) POS-X-A))
  (define POS-Y-B (if is-vertical POS-Y-A (* POS-Y-A 3)))

  (define POS-X-C (if is-vertical (* POS-X-A 5) POS-X-A))
  (define POS-Y-C (if is-vertical POS-Y-A (* POS-Y-A 5)))
 
  (place-image
   REC-A
   POS-X-A POS-Y-A
   (place-image
    REC-B
    POS-X-B POS-Y-B
    (place-image
     REC-C
     POS-X-C POS-Y-C
     (empty-scene WIDHT HIGHT)
    )
   )
  )
)



