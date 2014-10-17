;3. Design the function rember-all (remberAll in Javascript)
;that takes a list ls and an element x and returns a new list
;which is equivalent to the old list except that all
;occurrences of the elementx are removed.

;; We first define the recursive version of remember-all

;;remember-all : [list? any] -> list?
;;--------------------------------------
(define remember-all
  (lambda(ls x)
    (cond
      [(null? ls) '()]
      [(not (eq? (car ls) x))
       (cons (car ls) (remember-all (cdr ls) x))]
      [(remember-all (cdr ls) x)])))


;; We now define the iterative/goto version of remember-all

;;remember-all/goto : [list? any] -> list?
;;-------------------------------------------
(define remember-all/goto
  (lambda(ls x)
    (let ([count (sub1 (length ls))] [ls-ret '()])
      (letrec ([f (lambda ()
                    (cond
                      [(= count -1) ls-ret]
                      [(not (eq? (list-ref ls count) x))
                       (begin
                         (set! ls-ret (cons (list-ref ls count) ls-ret))
                         (set! count (- count 1))
                         (f))]
                      [else 
                       (set! count (- count 1))
                       (f)]))])
        (f)))))

;;=====================================================================
;;Following are some testcases
'(remember-all '(1 2 3 4) 3)
(remember-all '(1 2 3 4) 3) (newline)

'(remember-all '(1 2 3 4) 8)
(remember-all '(1 2 3 4) 8) (newline)

'(remember-all '(1 2 3 2) 2)
(remember-all '(1 2 3 2) 2) (newline)

'(remember-all '(3 3 3 3) 3)
(remember-all '(3 3 3 3) 3) (newline)


'(remember-all/goto '(1 2 3 4) 3)
(remember-all/goto '(1 2 3 4) 3) (newline)

'(remember-all/goto '(1 2 3 4) 8)
(remember-all/goto '(1 2 3 4) 8) (newline)

'(remember-all/goto '(1 2 3 2) 2)
(remember-all/goto '(1 2 3 2) 2) (newline)

'(remember-all/goto '(3 3 3 3) 3)
(remember-all/goto '(3 3 3 3) 3) (newline)
