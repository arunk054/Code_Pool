
(require "main.ss")

;;Function to validate if the two identifiers are equal or unequal,
;;And display the appropriate message.
;; validate : [any any boolean? symbol?] -> void?
;;--------------------------------------------------
(define validate
  (lambda(a1 a2 expected s)
    (display a2)      (display ": ")  (display a1) (newline)
    (display s)(display ": ")
    ;;The idea here is to check if the equality of a1 and a2 is equal to expected.
    (if (eq? (eq? a1 a2) expected)
        (begin (display "SUCCESS") (newline))
        (begin (set! failures (add1 failures));; increment the counter, this is used at the end
               (display "!!!**FAILURE**!!!") (newline))
    )))

(define failures 0)

(display "### Test cases to validate the 2D point datatype ###")(newline)(newline)
(display "========Testing make-point and point?=========")(newline)
(define x1 -2)(define y1 5)
(define p1 (make-point x1 y1))
(validate (point? p1) #t #t "make-point-point?-test-1")
(validate (point? (vector 0 x1 y1)) #f #t "point?-test-2")
(newline)

(display "========Testing accesors point-x and point-y=========")(newline)
(validate (point-x p1) x1 #t "point-x-test-1")
(validate (point-y p1) y1 #t "point-y-test-1")
(newline)

(display "========Testing mutators set-point-x! and set-point-y!=========")(newline)
(set! x1 1)(set! y1 2)
(set-point-x! p1 x1)
(validate (point-x p1) x1 #t "set-point-x!-test-1")
(set-point-y! p1 y1)
(validate (point-y p1) y1 #t "set-point-y!-test-1")
(newline)

(display "========Testing equality predicate point-equal?=========")(newline)
(define x2 x1)(define y2 y1)
(define p2 (make-point x2 y2))
(validate (point-equal? p1 p2) #t #t "point-equal?-test-1")
(validate (point-equal? p1 (make-point (+ x1 2) y1)) #f #t "point-equal?-test-2")
(newline)

(display "========Testing point-origin?=========")(newline)
(validate (point-origin? p1) #f #t "point-origin?-test1")
(validate (point-origin? (make-point 0 0)) #t #t "point-origin?-test-2")
(newline)

(display "========Testing point operations=========")(newline)
(validate (point-distance p1 p2) 0 #t "point-distance-test-1")
(validate (point-distance p1 p2) x1 #f "point-distance-test-2")
(point-distance p1 p2)
(validate (point-distance-from-origin p1) (sqrt (+ (sqr x1) (sqr y1))) #t "point-distance-from-origin-test-1")

(define dx 2)(define dy -3)
(point-move! p1 dx dy)
(validate (point-x p1) (+ x1 dx) #t "point-move!-test-1")
(validate (point-y p1) (+ y1 dy) #t "point-move!-test-2")
(set! x1 (+ x1 dx)) (set! y1 (+ y1 dy))
(newline)

(validate (point-quadrant p1) 4 #t "point-quadrant-test-1")
(validate (point-quadrant p2) 1 #t "point-quadrant-test-2")
(newline)

(if (= failures 0)
    (display "### SUCCESS: All test cases passed. ###")
    (begin (display "!!!***ERROR: ")(display failures) (display " test case(s) FAILED***!!!")))
