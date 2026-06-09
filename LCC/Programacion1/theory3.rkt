#lang racket
(require 2htdp/image)
(require 2htdp/universe)

;//// theory

(define START-COLOR "red")
(define START-SIZE 20)

(define (interpret size)
  (place-image
     (circle size "solid" START-COLOR)
     150 150
     (empty-scene 300 300)
  )
)

(define (change-color color)
  (cond
    [(string=? color "red") "yellow"]
    [(string=? color "yellow") "green"]
    [(string=? color "green") "red"]
  )
)

(define (change-size size)
  (if (>= size 150)
     20
     (+ size 1)
  )
)

(define (keyboard-handler status key)
  (cond
    [(key=? key "y") "yellow"]
    [(key=? key "g") "green"]
    [(key=? key "r") "red"]
    [(key=? key "left") (change-color status)]
    [(key=? key "right") (change-color status)]
    [else status]
  )
)

(define (distance-two-points x1 y1 x2 y2)
  #| Returns the distance of the point (x, y) to the second point (x2, y2)
     distance : NUmber, Number, Number, Number -> Number |#

  (sqrt (+ (expt (- x1 x2) 2) (expt (- y1 y2) 2)))
)

(define (mouse-handler status x y mode)
  (if (string=? mode "button-down")
      (distance-two-points x y 150 150)
      status
  )
)

(define (ends? size)
  (>= size 150)
)

(define SECONDS-COLOR 1)
(define SECONDS-SIZE 0.1)

(big-bang START-SIZE
  [to-draw interpret]
  [on-tick change-size SECONDS-SIZE]
  [on-mouse mouse-handler]
  [stop-when ends?]
)

