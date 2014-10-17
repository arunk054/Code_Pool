;5. Define functions list-sum (and list-product,
;respectively) recursively that sum (and multiply,
;respectively) all the elements of a list of numbers.
;Carefully choose the base cases (when ls is empty). 

;;Here we only define the recursive versions of list-sum and list-product
;;Following are the signatures
;;==============================================================


;;list-sum : lon? -> number? OR 'Empty-List
;;==========================================

;;list-product : lon? -> number? OR 'Empty-List
;;============================================

;;But first we need to define the type predicate lon?
;;lon? : any -> boolean?
;;-----------------------
(define lon?
  (lambda (thing)
    (and
     (list? thing)
     (letrec ([f (lambda(ls)
                   (cond
                     [(null? ls) #t]
                     [(not (number? (car ls))) #f]
                     [else (f (cdr ls))]))])
       (f thing)))))

;;list-sum : lon? -> number? OR 'Empty-List
;;------------------------------------------
(define list-sum
 (lambda (ls)
   (letrec ([f (lambda(ls a)
                 (if (null? ls)
                     a
                     (f (cdr ls) (+ a (car ls)))))])
     (if (null? ls)
         'Empty-List
         (f ls 0)))))

;;list-product : lon? -> number? OR 'Empty-List
;;----------------------------------------------
(define list-product
 (lambda (ls)
   (letrec ([f (lambda(ls a)
                 (if (null? ls)
                     a
                     (f (cdr ls) (* a (car ls)))))])
     (if (null? ls)
         'Empty-List
         (f ls 1)))))


;;=====================================================================
;;Following are some testcases
'(list-sum '(1 2 3 4))
(list-sum '(1 2 3 4)) (newline)

'(list-sum '())
(list-sum '()) (newline)

'(list-sum '(-1 2 -3 4))
(list-sum '(-1 2 -3 4)) (newline)

'(list-product '(3 2 1 4))
(list-product '(3 2 1 4)) (newline)

'(list-product '())
(list-product '()) (newline)

'(list-product '(2 -3 1))
(list-product '(2 -3 1)) (newline)