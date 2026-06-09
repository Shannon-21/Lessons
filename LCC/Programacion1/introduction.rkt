#lang racket

(define (Resolvent a b c)
  #| Will take the roots of a cuadratic function by its coefficents
     Resolvent : Number, Number, Number -> list(Number, Number) |#
  
  (define discriminant (- (* b b) (* 4 a c)))
  (define common_term (* b -1))
  (define numerator1 (+ common_term (sqrt discriminant)))
  (define numerator2 (- common_term (sqrt discriminant)))
  (define denominator (* 2 a))
  
  (list (/ numerator1 denominator) (/ numerator2 denominator))
)

(define (AreComplementary a b)
  #| Takes two angles and returns true if are complementary
     AreComplementary : Number, Number -> Bool |#

  (= (+ a b) 90)
)