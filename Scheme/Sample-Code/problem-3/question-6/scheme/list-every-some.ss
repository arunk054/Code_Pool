;6.  Define functions list-every and list-some that takes a
;predicate p and a list ls, and returns #t if every
;(respectively, some) element of ls satisfies p, #f
;otherwise.  Be careful and rationalize about the choice of
;your definition for the base case (when ls is empty).

;;Here we only define the recursive versions of list-some and list-every
;;Following are the signatures
;;========================================================================

;;The function takes in the predicate as the first parameter,
;;The predicate is basically a function which returns a boolean, based on the
;; parameter passed to the predicate

;;The idea here is to call recursively, with initial value of accumulator
;;being 'Empty-List.

;;list-every : [[any -> boolean?] list?] -> boolean? OR 'Empty-List
;;------------------------------------------------------------------
(define list-every
  (lambda(p ls)
    (letrec 
        ([f (lambda(ls a)
              (cond
                [(null? ls) a]
                [(not (p (car ls))) #f]
                [else (f (cdr ls) #t)]))])
      (f ls 'Empty-List))))


;;list-some : [[any -> boolean?] list?] -> boolean? OR 'Empty-List
;;------------------------------------------------------------------
(define list-some
  (lambda(p ls)
    (letrec 
        ([f (lambda(ls a)
              (cond
                [(null? ls) a]
                [(p (car ls)) #t]
                [else (f (cdr ls) #f)]))])
      (f ls 'Empty-List))))

;;=====================================================================
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