#lang racket
(require test-engine/racket-tests)

;// 2.0

(define (seconds->minutes-seconds seconds)
  #| Given n seconds, returns the equivalent time n writen as minutes' seconds''
     seconds->minutes-seconds : Number -> String
     Examples :
        n = 60 => "1' 0''"
        n = 125 => "2' 5''"
  |#

  (define minutes (quotient seconds 60))
  (define remainder (- seconds (* minutes 60)))

  (string-append (number->string minutes) "' " (number->string remainder) "''")
)

(check-expect (seconds->minutes-seconds 60) "1' 0''")
(check-expect (seconds->minutes-seconds 125) "2' 5''")

(define (round-decimal number [decimals 3])
  #| Given a number, returns the number rounded to decimals digits
     round-decimal : Number, [Number] -> Number
     Examples:
        3.141516 -> 3.141
        4.5, 2 -> 4.50
  |#

  (define multiplier (expt 10 decimals))
  ( / (round (* number multiplier)) multiplier)
)

(define (exercise-1 x y)
  #| Given a point of coordinates p = (x, y), returns the distance of p from the origin (0, 0)
     exercise-1 : Number, Number -> Number
     Examples:
        (1, 2) => (sqrt 5)
        (-3, 1) => (sqrt 10)
  |#

  (sqrt (+ (expt x 2) (expt y 2)))
)

(check-expect (number->string (exercise-1 1 2)) (number->string (sqrt 5)))
(check-expect (number->string (exercise-1 -3 1)) (number->string (sqrt 10)))

;///////////

(check-expect (number->string (personal-amount 2 2)) (number->string 487.5))
(check-expect (number->string (personal-amount 3 3)) (number->string 422.5))
(check-expect (number->string (personal-amount 1 5)) (number->string 487.5))

(define (apply-discount price discount)
  #| Returns the price with the discount applied
     apply-discount : Number, Number -> Number |#

  (* price (- 1 discount))
)

(define (personal-amount person-qty month-qty [individual-price 650])
  #| Given the qty of person to be joined and the qty of months they will pay,
     returns the amount to pay for each individual person.
     The resultant amount applies these promotions:
       if person-qty = 2, each one get a 10% off,
       if person-qty >= 3, each one get a 30% off,
       if month-qty = 2, each one get a 15% off,
       if month-qty >= 2, each one get a 25% off,
     Promotions are acumulable, but cannot get more than 35% off.
     personal-amount : Number, Number, [Number] -> Number
     Examples:
       (personal-amount 2 2) => 487.5
       (personal-amount 3 3) => 422.5
       (personal-amount 1 5) => 487.5 |#
  
  (define TWO-PEOPLE-DISCOUNT-PERCENTAGE 0.1)
  (define THREE-OR-MORE-PEOPLE-DISCOUNT-PERCENTAGE 0.3)
  (define TWO-MONTH-DISCOUNT-PERCENTAGE 0.15)
  (define THREE-OR-MORE-MONTH-DISCOUNT-PERCENTAGE 0.25)
  (define LIMIT-DISCOUNT-PERCENTAGE 0.35)

  (define DISCOUNT-PEOPLE
    (cond
      [(= person-qty 1) 0]
      [(= person-qty 2) TWO-PEOPLE-DISCOUNT-PERCENTAGE]
      [(>= person-qty 3) THREE-OR-MORE-PEOPLE-DISCOUNT-PERCENTAGE]
    )
  )

  (define DISCOUNT-MONTH
    (cond
      [(= month-qty 1) 0]
      [(= month-qty 2) TWO-MONTH-DISCOUNT-PERCENTAGE]
      [(>= month-qty 3) THREE-OR-MORE-MONTH-DISCOUNT-PERCENTAGE]
    )
  )

  (define TOTAL-DISCOUNT (+ DISCOUNT-PEOPLE DISCOUNT-MONTH))

  (if (> TOTAL-DISCOUNT LIMIT-DISCOUNT-PERCENTAGE)
      (apply-discount individual-price LIMIT-DISCOUNT-PERCENTAGE)
      (apply-discount individual-price TOTAL-DISCOUNT)
  )
)



