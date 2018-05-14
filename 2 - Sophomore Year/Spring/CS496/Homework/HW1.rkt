#lang racket

;; number? -> number?
(define (succ x) ; returns x + 1
  (+ x 1)
  )

;; number? -> number?
(define (double x) ; returns x * 1
    (* x 2)
  )

;; null? -> number?
(define (seven x) ; returns the atomic value 7
  (7)
  )

;; number? -> number?
(define (sign x) ; returns 1 if x > 0, -1 if x < 0, 0 if x == 0
    (cond [(> x 0) 1]
          [(< x 0) -1]
          [else 0]
    )
  )

;; number? -> number?
(define (absolute x) ; returns the absolute value of x
    (if (>= x 0) x (* x -1))
  )

;; boolean?, boolean? -> boolean?
(define (andp x y) ; checks if both x and y are true
    (if x (if y #t #f) #f)
  )

;; boolean?, boolean? -> boolean?
(define (orp x y) ; checks if either x or y is true
    (if x #t (if y #t #f)) 
  )
  

;; Adam Gincel
;; HW1
;; CS496
;; 1/29/16

;; boolean? -> boolean?
(define (notp x) ; returns the opposite value of x
    (if x #f #t)
  )

;; boolean, boolean? -> boolean?
(define (xorp x y) ; returns the xor of x and y
    (if (or (andp x y) (andp (notp x) (notp y))) #f #t)
  )
  

;; number?, number? -> boolean?
(define (dividesBy x y) ; returns true if y can cleanly divide x
    (if (= (remainder x y) 0) #t #f)
  )

;; anything? -> boolean?
(define (singleton? x) ; returns true if x is a singleton
    (match x
      [(list a) #t]
      [_ #f]
    )
  )

;; anything? -> boolean?
(define (singleton2? x) ; returns true if x is a singleton (no match, only cons and null)
    (if (andp (cons? x) (null? (cdr x))) #t #f)
  )

;; pair? (a,b) -> pair? (b,a)
(define (swap x) ; swaps the first and second values of a list
    (match x
      [(cons l r) (cons r l)]
      [_ x]
      )
  )

;; {a->b}, a -> b
(define (app func x) ; applies x to a function func and returns the result
    (func x)
  )

;; {a->b}, a -> ((a->b) -> b)
(define (twice func x) ; applies x to a function func twice, and returns the result
    (app func (app func x))
  )

;; function? a, function? b, argument? c -> (a (b c))
(define (compose func func2 x) ; applies x to a function func2, then the result of that to a function func, then returns the result
    (app func (app func2 x))
  )


