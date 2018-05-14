#lang racket
(require compatibility/mlist)

(define counter
  (let ((local-state 0))
    (lambda ()
      (let ((dummy (set! local-state (+ local-state 1))))
        local-state))))

(define stack
  (let ((stk '()))
    (lambda (message)
      (case message
        ((empty?) (lambda () (null? stk)))
        ((push!) (lambda (x)
                   (set! stk (append (list x) stk))))
        ((pop!) (lambda ()
                  (if (null? stk)
                      (error "stack: Can't pop empty stack.")
                      (set! stk (cdr stk)))))
        ((top) (lambda ()
                 (if (null? stk)
                     (error "stack: No top of empty stack.")
                     (car stk))))
        (else (error "stack: Invalid message" message))))))

(define (ex1 v1 v2)
  (let ((f
         (let ((rList '()))
           (lambda (x)
             (set! rList (append (list x) rList))
             rList
             )
           )
         ))
    (begin (f v1) (f v2))))

(define c (mcons 1 2))
(define d (mcons 0 c))
(define e (mcons 0 c))

(define l (mcons 'a (mcons 'b '())))

(define x (mcons 1 2))
(define (modify y)
  (set-mcdr! y 5))
