
;; Test suite for Problem - 1, which is implemented in exp.ss
;; ============================================================

(require (planet schematics/schemeunit:3)
  (planet schematics/schemeunit:3/text-ui))

(require "exp.ss")

;; Just define some global variables for testing with these.
(define n1 (numexp 1))
(define n2 (numexp 2))
(define n3 (numexp 3))
(define n4 (numexp 4))
(define p1 (plusexp n1 n2))
(define p2 (plusexp n3 n4))
(define p3 (plusexp p1 p2))

(define exp-ts
  
  (test-suite
    "exp test-suite"
    (let ([p4 (plusexp p2 p3)])

      (check-pred numexp? (list 'numexp 3) "test-numexp?")
    
      (check-pred numexp? n2 "test-numexp? numexp")
  
      (check-pred plusexp? (list 'plusexp n1 n2) "test-plusexp?")

      (check-pred plusexp? p2 "test-plusexp? plusexp")
          
      (check-eq? (evaluate n3) 3 "test-evaluate-1")
      (check-eq? (evaluate p2) 7 "test-evaluate-2")
      (check-eq? (evaluate p3) 10 "test-evaluate-3")
      (check-eq? (evaluate p4) 17 "test-evaluate-4")
      )))

(run-tests exp-ts)
