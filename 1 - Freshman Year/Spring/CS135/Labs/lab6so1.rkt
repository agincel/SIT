#lang eopl

(define (keep-evens intList)
  (if (null? intList)
      '()
      (if (even? (car intList))
          (cons (car intList) (keep-evens (cdr intList)))
          (keep-evens (cdr intList)))
      )
  )

(define (filter predicate? listThings)
  (if (null? listThings)
      '()
      (if (predicate? (car listThings))
          (cons (car listThings) (filter predicate? (cdr listThings)))
          (filter predicate? (cdr listThings))
          )
      )
  )


(define (EuclidAlgo a d)
  (if (= d 0)
      a
      (EuclidAlgo d (modulo a d))
      )
  )

(define (Euclid-list a d)
  (if (= d 0)
      (list a)
      (append (list a) (Euclid-list d (modulo a d)))
      )
  )

(define (isMultipleOf? a b)
  (if (= (modulo a b) 0)
      #t
      #f
      )
  )

(define (integers n)
  (cdr (reverse (Integers n))))

(define (Integers n)
  (if (= 0 n) 
      '()
      (cons n (Integers (- n 1)))))

;Simple launch:
(define (sieve n)
  (Sieve (integers n)))

;List-building procedure:
(define (Sieve list-of-ints)
  (if (null? list-of-ints)
      '()
      (cons (car list-of-ints) (Sieve (cross-out (car list-of-ints) (cdr list-of-ints))))
      )
  )


(define (cross-out prime listThings)
 (if (null? listThings)
      '()
      (if (not (isMultipleOf? (car listThings) prime))
          (cons (car listThings) (cross-out prime (cdr listThings)))
          (cross-out prime (cdr listThings))
          )
      )
  )

(define (pi n)
  (length (sieve n))
  )

(define (prime? n)
  (cond ((= n 1) #f)
        ((= n 2) #t)
         (else
          (Prime? n 2))))

(define (Prime? n k)
    (cond ((= n k) #t)
          ((= (modulo n k) 0) #f)
          (else
           (Prime? n (+ k 1)))))




(define (factor n)
   (Factor 2 n))


(define (Factor divisor n)
  (cond ((> (* divisor divisor) n)
        (cons n '()))
        ((equal? (modulo n divisor) 0)
         (cons divisor (Factor divisor (/ n divisor))))
        (else 
         (Factor (+ divisor 1) n))))








