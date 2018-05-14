#lang eopl


(define sample '((old new) (borrowed blue) (thing1 thing2) (oneFish twoFish) (redFish blueFish)))

(define author-character '((Doyle Holmes) (Poe Dupin) (Dickens Dodger) (Shakespeare Macbeth) (Shakespeare Lear) (Shakespeare Hamlet) (Twain Finn) (Hugo Valjean) (Shakespeare Romeo) (Shakespeare Juliet) (Tolstoy Karenina) (Dumas Athos) (Dumas Porthos) (Dahl WillyWonka) (Dumas Aramis) (Melville Ahab) (Stevenson Silver) (Christie Marple) (Christie Poirot) (Carroll Alice)))

;Here's a relation with fictional characters as domain and attributes 
;of those characters as codomain:
(define character-attributes '((Holmes detective) (Dupin detective) (Macbeth villain) (Lear king) (Hamlet prince) (Dodger rascal) (Finn rascal) (CharlieBucket GoodBoy) (WillyWonka Chocolatier) (valJean hero) (Romeo lover) (Juliet lover) (Macbeth king) (Karenina lover) (Athos musketeer) (Porthos musketeer) (Aramis musketeer) (Ahab captain) (Ahab whaler) (Silver pirate) (Marple detective) (Poirot detective) (Alice dreamer)))

(define cycle6 '((1 2) (2 3) (3 4) (4 5) (5 6) (6 1)))
(define david '((1 3) (3 1) (2 4) (4 2) (3 5) (5 3) (4 6) (6 4) (5 1) (1 5) (6 2) (2 6)))
(define study '((1 6) (2 2) (2 3) (3 1) (4 1) (5 1) (5 6) (6 5)))
(define test '((1 2) (2 3) (2 1) (3 3) (4 5) (5 2)))

(define not-relation '((1 2 3) (1 2) (4 5) 6))
(define U '(1 2 3 4 5 6))

(define (duple? theList)
  (if (list? theList)
      (if (= (length theList) 2)
          #t
          #f
          )
      #f
     )
  )

(define (relation? listOfDuples)
  (if (null? listOfDuples)
      #t
      (if (duple? (car listOfDuples))
          (relation? (cdr listOfDuples))
          #f
          )
      )
  )

(define test-relations (and (relation? sample)
                            (relation? author-character)
                            (relation? character-attributes)
                            (relation? cycle6)
                            (relation? david)
                            (relation? test)
                            (relation? study)))

;------------------

(define delta6 '((1 1) (2 2) (3 3) (4 4) (5 5) (6 6)))

(define (id n)
  (if (= n 0)
      '()
      (cons (list n n) (id (- n 1)))
      )
  )

(define (reflexive? relation n)
  (subset? (id n) relation))


(define (reflexive-closure relation n)
  (union relation (id n))
  )

;-------------------------

(define (R-minus-1 relation)
  (if (and (relation? relation) (not (null? relation)))
      (cons (list (cadar relation) (caar relation)) (R-minus-1 (cdr relation)))
      '()
      )
  )

(define (symmetric? relation)
  (subset? (R-minus-1 relation) relation))

(define (symmetric-closure relation)
  (union relation (R-minus-1 relation)))
;-----------

(define (related-to element relation)
  (if (null? relation)
      '()
      (if (equal? element (caar relation))
          (cons (cadar relation) (related-to element (cdr relation)))
              (related-to element (cdr relation))   
          )
      )
  )

;-------------

(define (compositeUnused relationOuter relationInner)
  (if (and (not (null? relationOuter)) (not (null? relationInner)))
      (cons (compositeUnused2 (car relationInner) relationOuter) (composite relationOuter (cdr relationInner)))
      '()
      )
  )


(define (compositeUnused2 innerPair relationOuter)
  (if (not (null? relationOuter))
      (if (equal? (cadr innerPair) (caar relationOuter))
          (cons (list (car innerPair) (cadar relationOuter)) (compositeUnused2 innerPair (cdr relationOuter)))
          '()
          )
      '()
     )
  )


(define (composite relationOuter relationInner)
  (Composite relationOuter relationInner))

(define (Composite keepintact shred)           
  (if (null? shred)                            
      '()                                      
      (append (pass (car shred) keepintact)    
            (Composite keepintact (cdr shred)))))

(define (pass duple wholerelation)         
  (if (null? wholerelation)                 
      '()                                   
      (if (= (cadr duple) (caar wholerelation))
          (cons (list (car duple) (cadar wholerelation))
                (pass duple (cdr wholerelation)))
          (pass duple (cdr wholerelation)))))



;-----------------







;=======================================================================
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
