#lang scheme

;; Problem  1: Inductive Data types
;;-----------------------------------

;; Here we implement a datatype to define an expression

;; Exp :: = numExp(n: Number) | 
;         plusExp(operand1: Exp, operand2: Exp)

;An Exp is either 
;
;* a NumExp built from the constructor numExp that takes a
;  number n.  n is also the name of the component of a NumExp
;  instance.
;
;OR 
;
;* a PlusExp built from the constructor plusExp that takes
;  two arguments operand1 and operand2, which are of type
;  Exp.  Operand1 and Operand2 are also the names of the
;  components of a PlusExp instance. 

;Example: 
;(plusexp (numexp 5) (numexp 2)) ;; roughly corresponds to the ast +(5,2)

;; Here, as usual we need to define the following four for an datatype
;; 1. Type predicate, 2. Constructor, 3. accessors, 4. mutators (not applicable in this case)

;; Since the exp can either be a numexp or a plusexp we first define these two

;; Here our datatypes are constructed using lists, in which the first element is the tag

;;Following are provided by this module
(provide
 ;;type predicates
 numexp?
 plusexp?
 exp?
 ;;constructors
 numexp
 plusexp
 
 evaluate
)

;;=====================================================================
;; First define, Type predicates for numexp and plusexp

;; numexp? : any -> boolean?
;;------------------------
(define numexp? 
  (lambda (thing)
    (and
     (list? thing)
     (= (length thing) 2)
     (eq? (list-ref thing 0) 'numexp)
     (number? (list-ref thing 1))
     )))

;; exp? : any -> boolean?
;;------------------------
(define exp?
  (lambda (thing)
    (or
     (numexp? thing)
     (plusexp? thing))))

;;plusexp? any -> boolean
;;------------------------
(define plusexp?
  (lambda (thing)
    (and
     (list? thing)
     (= (length thing) 3)
     (eq? (list-ref thing 0) 'plusexp)
     (exp? (list-ref thing 1))
     (exp? (list-ref thing 2)))))

;;==========================================================================
;; Now we define the constructors numexp and plusexp

;; numexp : number? -> numexp?
;;-----------------------------
(define numexp
  (lambda (n)
    (list 'numexp n)))

;; plusexp : [exp? exp?] -> plusexp?
;;------------------------------------
(define plusexp
  (lambda (op1 op2)
    (list 'plusexp op1 op2)))

;;=========================================================================
;; We now define few accessors for the numexp and plusexp

;; numexp-number : numexp? -> number?
;;------------------------------------
(define numexp-number
  (lambda(nexp)
          (list-ref nexp 1)))

;; plusexp-op1 : plusexp? -> exp?
;;------------------------------------
(define plusexp-op1
  (lambda(pexp)
          (list-ref pexp 1)))

;; plusexp-op2 : plusexp? -> exp?
;;------------------------------------
(define plusexp-op2
  (lambda(pexp)
          (list-ref pexp 2)))

;;===========================================================================
;; 2. Implement a function evaluate that evaluates an AST.
;; The idea here is to evaluate the exp recursively using the accessors
;;evaluate : exp? -> number?
(define evaluate
  (lambda(exp)
    (if (numexp? exp)
      (numexp-number exp)
      ;;If its not a numexp then it is a plusexp, since an exp can only be either
      (+ (evaluate (plusexp-op1 exp)) (evaluate (plusexp-op2 exp))))))



