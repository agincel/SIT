#lang eopl



(define Hasse72 '((6 12) (6 18) (9 18) (8 24) (12 24) (12 36) (18 36) (24 72) (36 72) (1 2) (1 3) (2 4) (2 6) (3 6) (3 9) (4 8) (4 12)))

;And its reverse: 
(define RevHasse72 (reverse Hasse72))


(define HasseX '((LowerLeft Middle) (Middle UpperRight) (LowerRight Middle) (Middle UpperLeft)))

(define (minimal-elements HasseDuples)
  (set-difference (minimal-elements-break HasseDuples 0) (minimal-elements-break HasseDuples 1)))


(define (minimal-elements-break HasseDuples i)
  (if (not (null? HasseDuples))
      (if (= i 0)
          (cons (caar HasseDuples) (minimal-elements-break (cdr HasseDuples) i))
          (cons (cadar HasseDuples) (minimal-elements-break (cdr HasseDuples) i))
          )
      '()
      )
  )
;========

(define (rinse min-element HasseDuples)
  (if (not (null? HasseDuples))
      (if (equal? (caar HasseDuples) min-element)
          (rinse min-element (cdr HasseDuples))
          (cons (car HasseDuples) (rinse min-element (cdr HasseDuples)))
          )
      '()
      )
  )

;=======

(define (topological-sort HasseDuples)
  (if (not (null? HasseDuples))
      (cons (car (minimal-elements HasseDuples)) (topological-sort (rinse (car (minimal-elements HasseDuples)) HasseDuples)))
      '()
      )
  )
  
;======
(define (maximal-elements HasseDuples)
  (set-difference (maximal-elements-break HasseDuples 1) (maximal-elements-break HasseDuples 0)))


(define (maximal-elements-break HasseDuples i)
  (if (not (null? HasseDuples))
      (if (= i 0)
          (cons (caar HasseDuples) (minimal-elements-break (cdr HasseDuples) i))
          (cons (cadar HasseDuples) (minimal-elements-break (cdr HasseDuples) i))
          )
      '()
      )
  )

(define (topo-sort HasseDuples)
  (union (topological-sort HasseDuples) (maximal-elements HasseDuples))
  )
























;BELOW ARE SET DATA STRUCTURE FUNCTIONS AVAILABLE FOR USE IN THIS LAB
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

(define (element? item list-of-items)
  (if (null? list-of-items)                  ;Is our "set" empty?
      #f                                     ;If empty, not an element!
      (if (equal? item (car list-of-items))  ;Is our item first in list?
          #t                                 ;Yes?  Then it's an element!
          (element? item (cdr list-of-items)))));No? Check the rest.

(define (make-set list-of-items)
  (if (null? list-of-items) ;An empty list can have no duplicates,
      '()                   ;so just return an empty list.
      (if (element? (car list-of-items) (cdr list-of-items))
          (make-set (cdr list-of-items))
          (cons (car list-of-items) (make-set (cdr list-of-items))))))
         
(define (union setA setB)
  (make-set (append setA setB))) 

(define (intersection setA setB)
  (make-set (Intersection (make-set setA) (make-set setB))))

(define (Intersection setA setB)
  (if (null? setA) 
      '()
      (if (element? (car setA) setB)
          (cons (car setA) (intersection (cdr setA) setB))
          (intersection (cdr setA) setB))))

(define (subset? setA setB)
  (if (null? setA)
      #t
      (if (element? (car setA) setB)
          (subset? (cdr setA)  setB)
          #f)))

(define (set-equal? setA setB)
   (and (subset? setA setB) (subset? setB setA)))

(define (proper-subset? setA setB)
  (and (subset? setA setB) (not (set-equal? setA setB))))

(define (set-difference setA setB)
  (make-set (Set-Difference setA setB)))

(define (Set-Difference setA setB)
  (if (null? setA)
      '()
      (if (element? (car setA) setB)
          (Set-Difference (cdr setA) setB)
          (cons (car setA) (Set-Difference (cdr setA) setB)))))

(define (sym-diff setA setB)
  (union (set-difference setA setB) (set-difference setB setA)))

(define (cardinality set)
  (length (make-set set)))

(define (disjoint? setA setB)
  (null? (intersection setA setB)))

(define (superset? setA setB)
  (subset? setB setA))

(define (insert element set)
  (make-set (cons element set)))

(define (remove element set)
  (set-difference set (list element)))


;(define (complement setA)
;  (set-difference universe setA))


(define DapperDan '((tie jacket) (pants belt) (pants shoes) (boxers shoes) (boxers pants) (socks shoes) (shirt tie) (shirt belt) (belt jacket) (watch watch)))

;;;;;;