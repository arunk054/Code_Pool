;;4. Define a function list-reverse that takes a list and reverses
;;it. [Hint: use an accumulator.]

;;Here we only define the recursive version of list-reverse
;;Following is the signature and definition
;;==============================================================


;;list-reverse : list? -> list?
;;-------------------------------
(define list-reverse
  (lambda (ls)
    (letrec ([f (lambda(ls ls-acc)
                  (if (null? ls)
                      ls-acc
                      (f (cdr ls)  (cons (car ls) ls-acc))))])
      (f ls '()))))

;;=====================================================================
;;Following are some testcases
'(list-reverse '(1 2 3 4))
(list-reverse '(1 2 3 4)) (newline)

'(list-reverse '(5 4 3 2 1))
(list-reverse '(5 4 3 2 1)) (newline)

'(list-reverse '(1 2 1 2))
(list-reverse '(1 2 1 2)) (newline)

'(list-reverse '())
(list-reverse '()) (newline)


