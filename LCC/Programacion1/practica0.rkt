#lang racket
(require 2htdp/image)

(define (resolvent a b c)
  #| Will take the roots of a cuadratic function by its coefficents
     resolvent : Number, Number, Number -> list(Number, Number) |#
  
  (define discriminant (- (* b b) (* 4 a c)))
  (define common_term (* b -1))
  (define numerator1 (+ common_term (sqrt discriminant)))
  (define numerator2 (- common_term (sqrt discriminant)))
  (define denominator (* 2 a))
  
  (list (/ numerator1 denominator) (/ numerator2 denominator))
)

(define (are-complementary a b)
  #| Takes two angles and returns true if are complementary
     are-complementary : Number, Number -> String |#

  (if (= (+ a b) 90)
     "Complementaries" "No complementaries"
  )
)

(define (distance-to-origin x y)
  #| Returns the distance of the point (x, y) to the origin (0, 0)
     distance : NUmber, Number -> Number |#

  (sqrt (+ (expt (- x 0) 2) (expt (- y 0) 2)))
)

(define (distance-two-points x1 y1 x2 y2)
  #| Returns the distance of the point (x, y) to the second point (x2, y2)
     distance : NUmber, Number, Number, Number -> Number |#

  (sqrt (+ (expt (- x1 x2) 2) (expt (- y1 y2) 2)))
)

(define (vol-cube side)
  #| Returns the volume of a cube given a side lenght
     vol-cube : Number -> Number |#

  (expt side 3)
)

(define (posible-triangle? a b c)
  #| Returns true if it's possible to build a tringle with sides a, b and c
     posible-triangle? : Number, Number, Number -> Bool |#

  (and (> (+ a b) c) (> (+ a c) b) (> (+ b c) a))
)

(define (pitagorean-triple? a b c)
  #| Returns true if a^2 + b^2 = c^2
     pitagorean-triple? : Number, Number, Number -> Bool |#

  (define c-calculated (sqrt (+ (expt a 2) (expt b 2))))
  (= c c-calculated)
)

(define (put-hyphen string index)
  #| Returns the string with a hyphen added in the positions 'index' if the string
     put-hyphen : String, Number -> String |#

  (string-append
    (substring string 0 index)
    "-"
    (substring string index (string-length string)))
 )
  
