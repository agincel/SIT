#lang eopl

(define (nand p q)
 (not(and p q))) ;given

(define (if->then p q)
  (or (not p) q)) ;given

(define (xor p q)
  (or (and p (not q)) (and (not p) q))) ;Either p and not q, or not p and q. 

(define (xor3 p q r)
  (or (and p (not q) (not r)) (and (not p) q (not r)) (and (not p) (not q) r))) ;just p, or just q, or just r. Used in Isosceles definition.
 
(define (commutes? operator);The input "data" here will be function names
  (equal? (operator #t #f) (operator #f #t))) ;given

(define (or2 p q)
  (or p q)) ;given

(define (and2 p q)
  (and p q)) ;given

(define (law-binary? left right)
  (and (equal? (left #t #t) (right #t #t))
       (equal? (left #t #f) (right #t #f))
       (equal? (left #f #t) (right #f #t))
       (equal? (left #f #f) (right #f #f)))) ;given

(define (not-p-or-not-q p q)
  (or (not p) (not q))) ;given

(define (nor p q)
  (not (or p q))) ;the not gets distributed, turning this into not p and not q

(define (not-p-and-not-q p q)
  (and (not p) (not q))) ; a different definition of nor

(define (3majority p q r)
  (or (and p q) (and p r) (and q r))) ;at least 2 of 3 parameters are true, but all 3 can be true too.

(define (isosceles p q r)
  (xor3 (and p q) (and p r) (and q r))) ;exactly 2 of the 3 parameters are true. Uses my own defined xor3.

;Golden Ticket
(define (if->then-if->then p q r)
  (equal? (if->then p (if->then q r)) (if->then (if->then p q) r))) ;shows that if->then is not associative. Returns #f for #f #f #f.



