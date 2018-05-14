#lang racket
(require eopl/eopl)

;; #4
(define-datatype dTree dTree?
  (leaf-t
   (datum number?))
  (node-t
   (symbol symbol?)
   (left dTree?)
   (right dTree?)
   )
  )

;; #5
(define tLeft
  (node-t 'w (node-t 'x (leaf-t 2) (leaf-t 5)) (leaf-t 8)))

(define tRight
  (node-t 'w (node-t 'x (leaf-t 2) (leaf-t 5)) (node-t 'y (leaf-t 7) (leaf-t 6))))

;; #6 a
;; dTree -> number?
(define (dTree-height t)
  (cases dTree t
    (leaf-t (x) 0)
    (node-t (symbol left right)
            (max (+ 1 (dTree-height left)) (+ 1 (dTree-height right)))
            )
    )
  )

;; #6 b
;; dTree -> number?
(define (dTree-size t)
  (cases dTree t
    (leaf-t (x) 1)
    (node-t (symbol left right)
            (+ 1 (dTree-size left) (dTree-size right))
            )
    )
  )


;; #6 c
;; dTree? -> list?
(define ret null)
(define (dTree-paths t)
  (set! ret null) ;probably bad practice? Listed in the Scheme documentation.
  (dTree-paths-rec t '())
   ret
)
(define (dTree-paths-rec t currList)
  (cases dTree t
    (leaf-t (x)
            (set! ret (cons currList ret)))
    (node-t (s l r)
            (dTree-paths-rec l (append currList (list 0)))
            (dTree-paths-rec r (append currList (list 1)))
            )
    )
  )

;; #6 d
;; dTree -> boolean?
(define (dTree-perfect? t)
  (cases dTree t
    (leaf-t (x) #t)
    (node-t (s l r)
            (and (= (dTree-height l) (dTree-height r)) (dTree-perfect? l) (dTree-perfect? r))
            )
   )
  )


;; symbol? -> symbol? 2
(define symbol-upcase (compose string->symbol (compose string-upcase symbol->string)))
(define (++ x) (+ x 1))

;; #6 e
;; dTree? -> dTree
(define (dTree-map f g t)
  (cases dTree t
    (leaf-t (x) (leaf-t (g x)))
    (node-t (s l r)
            (node-t (f s) (dTree-map f g l) (dTree-map f g r))
            )
    )
  )
  
  
            