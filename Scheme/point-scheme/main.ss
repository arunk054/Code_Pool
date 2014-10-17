#lang scheme

;;============================
;;       2-Dimensional Point
;;============================

;; This is an implementation of a mutable two-dimensional point datatype.

;; Author: Arun K <arun.k@iiitb.net>

;; A 2-d point has two coordinates, which are x and y. Here we represent the point
;; as a vector of 3 elements. The first element is a tag which identifies that the data
;; is a 2-d point. The next two elements represent the x and y coordinates respectively.
;;The reason why we use a vector instead of a list is because we want our datatype to be mutable.

;; Examples:
;;--------------
;; (<tag> <x> <y>)
;; (point2D 5 3) represents a point (5,3) on the co-ordinate system
;; (point2D 4.3 -1) represents a point (4.3, -1) on the co-ordinate system

(provide
;;Type predicate
point?

;;constructor
make-point

;;projectors or accessors
point-x
point-y

;;Mutators
set-point-x!
set-point-y!

;;Equality predicate
point-equal?

;;A useful point and its predicate - origin
origin
point-origin?

;;Some common operations
point-distance
point-distance-from-origin
point-move!

;;Some more useful operations
point-mid-point
point-quadrant
)

;;Use an identifier for the tag name, so that there is no risk of typo.
(define tag 'point2D)

;;Type Predicate
;;==================

;; point? : [any] -> boolean?
;;------------------------------

(define point?
  (lambda (p)
    (and 
    (vector? p)
    (= (vector-length p) 3)
    (eq? (vector-ref p 0) tag)
    (number? (vector-ref p 1)) ;; x co-ordinate
    (number? (vector-ref p 2)) ))) ;;y coordinate

;; Constructor
;;===============

;; make-point : [number? number?] -> point?
;;---------------------------------------------

(define make-point
  (lambda (x y)
    (vector tag x y)))

;; Accessors
;;=================

;; Function to access the x co-ordinate in a point
;; point-x : [ point? ] -> number?
;;---------------------------------------

(define  point-x
  (lambda (p)
    (vector-ref p 1)))



;; Function to access the y co-ordinate in a point
;; point-y : [ point? ] -> number?
;;-------------------------------------

(define  point-y
  (lambda (p)
    (vector-ref p 2)))

;; Mutators
;;===========

;; Function to set the x coordinate
;; set-point-x! : [point? number?] -> void?
;;----------------------------------------------

(define set-point-x!
  (lambda (p val)
    (vector-set! p 1 val)))

;; Function to set the y coordinate
;; set-point-y! : [point? number?] -> void?
;;----------------------------------------------

(define set-point-y!
  (lambda (p val)
    (vector-set! p 2 val)))

;; Equality Predicate
;;====================

;; point-equal? : [point? point?] -> boolean?
;; -------------------------------------------------

(define point-equal?
  (lambda (p1 p2)
    (and
     (= (point-x p1) (point-x p2)) ;;check if the x co-ordinate matches
     (= (point-y p1) (point-y p2))))) ;; then check if the y co-ordinate matches

;;Useful Points
;;=================

;;One useful point on the co-ordinate axes is the origin ==> (0,0)
(define origin  (make-point 0 0))

;;Predicae to identify the Origin
;;point-origin? : [point?] -> boolean?
;;-----------------------------------------
(define point-origin?
  (lambda (p)
    (point-equal? p origin)))


;;Some common operations performed on point(s).
;;=============================================

;;NOTE: The helper functions for these operations are defined below.

;;This function returns distance (absolute value) between two points
;;This will always return a non-negative number because we take the square
;; point-distance : [point? point?] -> non-negative?
;;----------------------------------------------------

(define point-distance
  (lambda (p1 p2)
    (sqrt (+ (sqr (point-sub-x p1 p2)) (sqr (point-sub-y p1 p2))))))

;;This function returns a the distance between the point and origin
;; point-distance-from-origin : [point?]-> non-negative?
;;------------------------------------------------------

(define point-distance-from-origin
  (lambda (p)
    (point-distance p origin)))

;; Takes a point and two numbers dx and dy.
;; Updates the points x and y coordinates by the amounts
;; dx and dy respectively. This is also a kind of mutator
;; point-move! :  [point? number? number?] -> void?
;;----------------------------------------------------

(define point-move!
  (lambda (p dx dy)
    ;;Here we dont have to use begin, coz the body of a procedure is treated like begin,
    ;; i.e the expressions are evaluated in order. Anyway sequence doesn't matter here.
    (point-move-x! p dx) ;;First move the x co-ordinate
    (point-move-y! p dy))) ;;Then move the y co-ordinate.

 
;;Following are some helper functions
;;====================================

;;Function to find the difference in x co-ordinate of two points
;; point-sub-x : [point? point?] -> number?
;;------------------------------------------

(define point-sub-x
  (lambda (p1 p2)
    (- (point-x p1) (point-x p2))))

;;Function to find the difference in y co-ordinate of two points
;; point-sub-y : [point? point?] -> number?
;;------------------------------------------

(define point-sub-y
  (lambda (p1 p2)
    (- (point-y p1) (point-y p2))))


;;Function to move the x co-ordinate by dx
;; point-move-x : [point? number?] -> void?
;;-------------------------------------------

(define point-move-x!
  (lambda (p dx)
    (set-point-x! p (+ (point-x p) dx))))

;;Function to move the y co-ordinate by dy
;; point-move-x : [point? number?] -> void?
;;-------------------------------------------

(define point-move-y!
  (lambda (p dy)
    (set-point-y! p (+ (point-y p) dy))))

;;Following are some more useful operations on point(s)
;;========================================================

;;Function to find mid-point of two given points
;; point-mid-point : [point? point?] -> point?
;;----------------------------------------------

(define point-mid-point 
  (lambda (p1 p2)
    (make-point (/ (point-add-x p1) 2) (/ (point-add-y p1) 2))))

;;Function to find which quadrant the point belongs to
;; point-quadrant : [point?] -> number?
;;-----------------------------------------

(define point-quadrant
  (lambda (p)
    (define x (point-x p))
    (define y (point-y p))
    (if (>= x 0)
        (if (>= y 0)
            1 ;; implies first quadrant
            4) ;; implies 4th quad, as y is negative and x positive
        (if (>= y 0)
            2 ;; implies x negative and y positive, 2nd quadrant
            3)))) ;; implies 3rd quad, as x and y both negative


;;Some more helper functions for the above operations
;;====================================================
;;Function to find the sum in x co-ordinate of two points
;; point-add-x : [point? point?] -> number?
;;------------------------------------------

(define point-add-x
  (lambda (p1 p2)
    (- (point-x p1) (point-x p2))))

;;Function to find the sum in y co-ordinate of two points
;; point-add-y : [point? point?] -> number?
;;------------------------------------------

(define point-add-y
  (lambda (p1 p2)
    (- (point-y p1) (point-y p2))))
