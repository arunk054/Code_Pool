;2. Design the function braid.  Braid takes two lists ls1 and
;ls2 and returns a new list whose elements are alternately
;taken from ls1 and ls2.  Elements remaining from the longer
;list after braiding are copied without change.  Remember to
;mention the signature of braid.
;
;Eg., 
;
;(braid '(1 2 3 4) '(a b)) => (1 a 2 b 3 4)
;(braid '(1 2) '(a b c d)) => (1 a 2 b c d)

;;Following is the signature of braid
;;====================================
;; braid : [(list-of any) (list-of any)] -> (list-of any)
;;---------------------------------------------------------

;;We only define the recursive version of braid

;; braid : [(list-of any) (list-of any)] -> (list-of any)
;;----------------------------------------------------------
(define braid
  (lambda (ls1 ls2)
    (cond
      [(and (null? ls1) (null? ls2)) '()]
      [(and (not (null? ls1)) (not (null? ls2))) 
       (cons (car ls1) (cons (car ls2) (braid (cdr ls1) (cdr ls2))))]
      [(not (null? ls1)) (cons (car ls1) (braid (cdr ls1) '()))]
      [else (cons (car ls2) (braid '() (cdr ls2)))])))


;;=====================================================================
;;Following are some testcases
'(braid '(1 2 3 4) '(a b))
(braid '(1 2 3 4) '(a b)) (newline)

'(braid '(1 2) '(a b c d))
(braid '(1 2) '(a b c d)) (newline)

'(braid '(1 2 3 4) '(a b c d))
(braid '(1 2 3 4) '(a b c d)) (newline)

'(braid '(1 2 3 4) '())
(braid '(1 2 3 4) '()) (newline)

'(braid '() '(a b c d))
(braid '() '(a b c d)) (newline)

