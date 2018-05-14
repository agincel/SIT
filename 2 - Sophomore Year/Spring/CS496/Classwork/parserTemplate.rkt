
(module parser racket

  (provide (all-defined-out))
  
  (require eopl/eopl)
  (require "lexer.rkt")


  ;; Grammar to parse
  ;; E ::= I | lam (I) E | app E E | (E)

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Expression datatype
  
(define-datatype expression expression?
  (var-exp
     (id symbol?))
  (lambda-exp 
     (id symbol?)
     (body expression?))
  (app-exp
     (rator expression?)
     (rand expression?)))

  (define (var-exp->datum e)
    (cases expression e
      (var-exp (datum) datum)
      (else (error "error"))))
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  
  ;; listof token? -> pair? expression? * listof token?  
  (define (parseFormParam xs)
    (let ((res1 (parseOpenParen xs)))
      (let ((res2 (parseIdent (cdr res1))))
        (let ((res3 (parseCloseParen (cdr res2))))
          (cons (car res2) (cdr res3))))))

  ;; listof token? -> pair? expression? * listof token?
 (define (parseIdent xs)
    (cases token (car xs)
      (ident-t (datum) (cons (var-exp datum) (cdr xs)))
      (else (error "error: expected identifier parenthesis"))
      ))

  ;; listof token? -> pair? expression? * listof token?
  (define (parseCloseParen xs)
    (cases token (car xs)
      (close-par-t () (cons (var-exp 'junk) (cdr xs)))
      (else (error "error: expected closing parenthesis"))
      ))

  ;; listof token? -> pair? expression? * listof token?
  (define (parseOpenParen xs)
    (cases token (car xs)
      (open-par-t () (cons (var-exp 'junk) (cdr xs)))
      (else (error "error: expected opening parenthesis" xs))
      ))

  ;; listof token? -> pair? expression? * listof token?
  (define (parseExp xs)
      (cases token (car xs)
        (ident-t (datum) (cons (var-exp datum) (cdr xs)))
        (open-par-t () (let ((exp (parseExp (cdr xs))))
                         (let ((closePar (parseCloseParen (cdr exp))))
                           (cons (car exp) (cdr closePar)))))
        (app-t () ( error "derp" ))
        (lambda-t () 
                  ( error "derp"))
        (else (error "parse: Invalid concrete syntax" xs))))

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Main
  
     ;; String -> pair? expression? * listof token?
    (define (main str)
      (match (parseExp (tokenize str))
         [(cons ast xs) (if (eofToken? (car xs))
                            ast
                            (error "Syntax error at " xs))]
      ))

  ;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;; Examples

  (define ex1
    "(lam (x) variable)")
  (define ex2
    "(lam (x) x)")
  (define ex3
    "app x app y z")
  (define ex4
    "app x ((app y z))")
  (define ex5
   "(app x ((app y z)))")

    (define ex6
   "(app x ((app y z))")

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
  )