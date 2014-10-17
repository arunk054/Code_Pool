;7. Define the function list-reduce which takes a seed value,
;a, binary function p, and a list ls of values and
;reduces the list to a value according to the following pattern.

;Also rewrite the problems 5 and 6 using list-reduce.

;(list-reduce seed p '()) = seed
;
;(list-reduce seed p '(a b c)) = (p a (p b (p c seed)))

;;We define the recursive version of list-reduce

;;list-reduce : [any [[any any] -> any] list?] -> any
;;-----------------------------------------------------
(define list-reduce
  (lambda(a p ls)
    (if (null? ls)
        a
        (p (car ls) (list-reduce a p (cdr ls))))))

;;Now rewrite the problems 5 and 6 using list-reduce.

;;We first defing list-sum and list-product using list-reduce

;;list-sum : lon? -> number? OR 'Empty-List
;;------------------------------------------
(define list-sum
  (lambda (ls)
    (if (null? ls)
        'Empty-List
        (list-reduce 0 + ls))))

;;list-product : lon? -> number? OR 'Empty-List
;;----------------------------------------------
(define list-product
  (lambda (ls)
    (if (null? ls)
        'Empty-List
        (list-reduce 1 * ls))))

;;We now define list-every and list-some using list-reduce

;;list-every : [[any -> boolean?] list?] -> boolean? OR 'Empty-List
;;------------------------------------------------------------------
(define list-every
  (lambda (p ls)
    (if (null? ls)
        'Empty-List
        (list-reduce #t (and-pred p) ls))))

;;We define function which takes an unary predicate and returns a binary predicate
;;function. This is required because the predicate p in list-every is unary function whereas
;; the list-reduce requires a binary function.

;;and-pred : [[any -> boolean?]] -> [[any boolean?] -> boolean?]
;;---------------------------------------------------------------
(define and-pred
  (lambda(p)
    (lambda (x y)
      (and (p x) y))))

;;list-some : [[any -> boolean?] list?] -> boolean? OR 'Empty-List
;;------------------------------------------------------------------
(define list-some
  (lambda (p ls)
    (if (null? ls)
        'Empty-List
        (list-reduce #f (or-pred p) ls))))

;;or-pred : [[any -> boolean?]] -> [[any boolean?] -> boolean?]
;;---------------------------------------------------------------
(define or-pred
  (lambda(p)
    (lambda (x y)
      (or (p x) y))))

;;=====================================================================
;;Following are some testcases for list-reduce

;;First define some binary functions for testing

;;my-and : [boolean? boolean?] -> boolean?
;;-----------------------------------------
(define my-and (lambda (x y)
                 (and x y)))

;;some test cases
'(list-reduce 1 + '(1 2 3))
(list-reduce 1 + '(1 2 3))(newline)

'(list-reduce 1 + '())
(list-reduce 1 + '())(newline)

'(list-reduce #t and '(#t #f #t))
(list-reduce #t my-and '(#t #f #t))(newline)

'(list-reduce #t and '(#t #t #t))
(list-reduce #t my-and '(#t #t #t))(newline)

;;=====================================================================
;;Following are some testcases for list-sum and list-product
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

;;=================================================================
;;Following are some testcases for list-every and list-some
'(list-every number? '(1 2 3 4))
(list-every number? '(1 2 3 4)) (newline)

'(list-every number? '(1 2 'a 4))
(list-every number? '(1 2 'a 4)) (newline)

'(list-every number? '())
(list-every number? '()) (newline)

'(list-some number? '(1 2 3 4))
(list-some number? '(1 2 3 4)) (newline)

'(list-some number? '(1 2 'a 4))
(list-some number? '(1 2 'a 4)) (newline)

'(list-some number? '('c 'b 'a))
(list-some number? '('c 'b 'a)) (newline)

'(list-some number? '())
(list-some number? '()) (newline)

