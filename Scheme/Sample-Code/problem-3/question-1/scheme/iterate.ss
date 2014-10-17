;1. function iterator: takes a function f and a nat n and
;returns the nth iterate of f. 
;
; iterate: [[any? -> any?] nat?] -> [any? -> any?]
;
;a. (iterate f 0) => a function equal to the identity function (lambda (x) x).
;b. (iterate f n+1) => (f (iterate f n)), for n : nat?
;
;Examples:
; ((iterate add1 3) 2) => 5
; ((iterate sqr 2) 3) => 81
; ((iterate D) 2)  => a function equivalent to the 2nd derivative 
;  (D is the derivative function we did in class). 


;;Recursive definition of iterate
;; The idea here is to return a function which takes an argument x,
;; and will apply the function f on x n times, using letrec
(define iterate
  (lambda (f n)
    (lambda (x)
      (letrec
          ([g (lambda(x n)
                (if (eq? n 0)
                    x
                    (g (f x) (- n 1))))])
        (g x n))
      
      )))


;;Goto definition of iterate function i.e. non-recursive
(define iterate/goto
  (lambda (f m)
    (lambda (x)
      (let ([n m][a x])
        (letrec
            ([g (lambda()
                  (if (eq? n 0)
                      a
                      (begin
                        (set! n (- n 1))
                        (set! a (f a))
                        (goto g))))])
          (goto g))))))

(define goto
  (lambda (f)
    (f)))

;;================================================================
;;Following are some testcases

'((iterate add1 3) 2)
((iterate add1 3) 2)

'((iterate sqr 2) 3)
((iterate sqr 2) 3)

'((iterate sqr 0) 3)
((iterate sqr 0) 3)

'((iterate sqrt 1) 16)
((iterate sqrt 1) 16)

;;Test cases for iterate/goto

'((iterate/goto add1 3) 2)
((iterate/goto add1 3) 2)

'((iterate/goto sqr 2) 3)
((iterate/goto sqr 2) 3)

'((iterate/goto sqr 0) 3)
((iterate/goto sqr 0) 3)

'((iterate/goto sqrt 1) 16)
((iterate/goto sqrt 1) 16)