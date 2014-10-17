;Problem 2: Tail Recursive and Iterative programs on lists
;---------------------------------------------------------
;
;Implement the list-memq (listMember in Javascript) function
;which takes a list ls and an value x and checks (using eq?
;in Scheme and === in Javascript) whether x exists in ls. 

;; list-memq : [list? number?] -> boolean?
;;--------------------------------------


;; Regular, recursive definition of list-memq
;; --------------------------------------------
;; Actually this is tail recursion, hence can also be seen as accumulator

(define list-memq
  (lambda (ls x)
    (cond
      [(null? ls) #f]
      [(eq? (car ls) x) #t]
      [else (list-memq (cdr ls) x)])))


;;Accumulator definition of list-memq
;;-------------------------------------
;;The accumulator and recursive version are same for this problem
;; Infact we dont need an accumulator in this case.

(define list-memq/acc
  (lambda (ls x)
    (letrec ([f (lambda (ls a)
                  (cond
                    [(null? ls) #f]
                    [(eq? (car ls) x) a]
                    [else (f (cdr ls) a)]))])
      (f ls #t)
      )))


;;Register definition of list-memq
;;----------------------------------
;; list-memq/reg

(define list-memq/reg
  (lambda (ls x)
    (let ([ls1 ls])
    (letrec ([f (lambda ()
                  (cond
                    [(null? ls1) #f]
                    [(eq? (car ls1) x) #t]
                    [else 
                     (begin
                       (set! ls1 (cdr ls1))
                       (f))]))])
                     
      (f)
      ))))

;;Goto definition of list-memq
;;----------------------------------
;; list-memq/goto

(define list-memq/goto
  (lambda (ls x)
    (let ([ls1 ls])
    (letrec ([f (lambda ()
                  (cond
                    [(null? ls1) #f]
                    [(eq? (car ls1) x) #t]
                    [else 
                     (begin
                       (set! ls1 (cdr ls1))
                       (goto f))]))])
                     
      (goto f)
      ))))


(define goto
  (lambda (f)
    (f)))

;;====================================================
;; Some test cases
(define ls '(1 2 3 8 5 4))
(list-memq ls 3)
(list-memq ls 9)
(list-memq/acc ls 3)
(list-memq/acc ls 9)

(list-memq/reg ls 3)
(list-memq/reg ls 9)

(list-memq/goto ls 3)
(list-memq/goto ls 9)
