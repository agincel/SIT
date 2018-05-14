#lang eopl


(define (digitize n)
  (reverse (Digitize n))
  )


(define (Digitize n)
  (if (< n 10)
      (list n)
      (append (list (modulo n 10)) (Digitize (quotient n 10)))
      )
  )

(define (sum elemList)
  (if
    (null? elemList)
    0
    (+ (car elemList) (sum (cdr elemList)))
  )
)

(define (sum-digits n)
  (sum (digitize n))
  )


;===

(define (even-parity? bitstring)
  (if (= (modulo (sum bitstring) 2) 0)
        #t
        #f
        )
  )

(define (parity-bit bitstring)
  (if (= (modulo (sum bitstring) 2) 0)
        0
        1
        )
  )

;====

(define tomato-soup '(0 5 1 0 0 0 1 4 8 7 2 8))

(define (upc? list-of-ints)
  (if (= (modulo (UPC list-of-ints #t) 10) 0)
      #t
      #f
  )
  )

(define (UPC list-of-ints isOddPlace)
  (if (null? list-of-ints)
      0
  (if isOddPlace
      (+ (* (car list-of-ints) 3) (UPC (cdr list-of-ints) (not isOddPlace)))
      (+ (car list-of-ints) (UPC (cdr list-of-ints) (not isOddPlace)))
      )
  )
  )

(define Aleve320 '(3 2 5 8 6 6 5 5 1 1 2 2))
(define hotSalsa '(0 2 8 4 0 0 0 5 5 9 9 4))

(define (missingCheckDigit n)
  (cond
    [(= n 0) (display #\X)]
    [(< n 10) (- 10 n)]
    [else "?"]
    )
  )

(define FlipSide '(0 1 9 2 7 5 0 5 4 6 0))

(define (upc-check-digit list-of-ints)
  (missingCheckDigit (modulo (UPC-check-digit list-of-ints #t) 10))
  )

(define (UPC-check-digit list-of-ints isOddPlace)
  (if (null? list-of-ints)
      0
  (if isOddPlace
      (+ (* (car list-of-ints) 3) (UPC (cdr list-of-ints) (not isOddPlace)))
      (+ (car list-of-ints) (UPC (cdr list-of-ints) (not isOddPlace)))
      )
  )
  )
    
(define PuffsTissues '(0 3 7 0 0 0 6 2 2 6 2))
(define ChunkyChickenNoodle '(0 5 1 0 0 0 1 6 7 7 5))


(define (ISBN? myList)
  (if (= (modulo (isbn myList) 11) 0)
      #t
      #f
      )
  )

(define (isbn myList)
  (if (null? myList)
      0
      (+ (* (car myList) (length myList)) (isbn (cdr myList)))
      )
  )

(define winningways1 '(1 5 6 8 8 1 1 3 0 6))

(define winningways2 '(1 5 6 8 8 1 1 4 2 10))  ;#t  that 10 is "X"
(define winningways3 '(1 6 5 8 8 1 1 4 3 8))   ;#f  Look closely and you can see the probable transposition error
(define winningways4 '(1 5 6 8 8 1 1 4 4 6))   ;#t
(define ritchie '(0 1 3 1 1 0 3 7 0 8))        ;#f  Check digit altered
(define ritchiePBK '(0 1 3 1 1 0 3 6 2 8))     ;#t

;[Show your TA a good one (#t) and a bad one (#f).]
(define hofstadter '(0 4 6 5 0 8 6 4 3 8))     ;#t     
;OK, sorry, Hofstadter is a bit tough to spell!
(define knuth '(0 3 2 1 5 3 4 9 7 4))          ;#f  Altered digit somewhere.  (I did it intentionally.)

;====

(define (hexconvert hexvalue)
  (if (null? hexvalue)
      '()
      (cons (altHEXsubletter (car hexvalue)) (hexconvert (cdr hexvalue)))))

(define (altHEXsubletter value)
  (cond ((= 10 value) 'A)
        ((= 11 value) 'B)
        ((= 12 value) 'C)
        ((= 13 value) 'D)
        ((= 14 value) 'E)
        ((= 15 value) 'F)
        ((= 16 value) 'G)
        ((= 17 value) 'H)
        ((= 18 value) 'I)
        ((= 19 value) 'J)
        ((= 20 value) 'K)
        ((= 21 value) 'L)
        ((= 22 value) 'M)
        ((= 23 value) 'N)
        ((= 24 value) 'O)
        ((= 25 value) 'P)
        ((= 26 value) 'Q)
        ((= 27 value) 'R)
        ((= 28 value) 'S)
        ((= 29 value) 'T)
        ((= 30 value) 'U)
        ((= 31 value) 'V)
        ((= 32 value) 'W)
        ((= 33 value) 'X)
        ((= 34 value) 'Y)
        ((= 35 value) 'Z)
        ((= 36 value) '-)
        ((= 37 value) '!)
        (else value)))

(define (numconvert numberlist)
  (if (null? numberlist)
      '()
      (cond ((eq? (car numberlist) 'A) (cons 10 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'B) (cons 11 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'C) (cons 12 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'D) (cons 13 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'E) (cons 14 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'F) (cons 15 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'G) (cons 16 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'H) (cons 17 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'I) (cons 18 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'J) (cons 19 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'K) (cons 20 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'L) (cons 21 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'M) (cons 22 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'N) (cons 23 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'O) (cons 24 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'P) (cons 25 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'Q) (cons 26 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'R) (cons 27 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'S) (cons 28 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'T) (cons 29 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'U) (cons 30 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'V) (cons 31 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'W) (cons 32 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'X) (cons 33 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'Y) (cons 34 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) 'Z) (cons 35 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) '-) (cons 36 (numconvert (cdr numberlist))))
            ((eq? (car numberlist) '!) (cons 37 (numconvert (cdr numberlist))))
            (else (cons (car numberlist) (numconvert (cdr numberlist)))))))


(define Rosen '(0 0 7 3 3 8 3 0 9 0))
(define RosenSlip '(0 0 7 3 3 8 3 0 9 8))
(define RosenSwap '(0 0 3 7 3 8 3 0 9 0))

(define chips '(0 2 8 4 0 0 3 7 2 1 6 ))
(define upc-find1 chips)

(define HuntsTomatoPaste '(0 2 7 0 0 0 3 8 8 1 5))
(define upc-find2 HuntsTomatoPaste)


(define huntsTomatoPaste '(0 2 7 0 0 0 3 8 8 1 5 0))
(define huntsTomatoePast '(0 2 7 0 0 0 3 8 8 1 5 7))
(define huntsTomatoPayst '(0 7 2 0 0 0 3 8 8 1 5 0));#t!  Should be #f.
(define huntsTomatopaste '(0 2 7 0 0 0 8 3 8 1 5 0));This too!
(define huntstomatopaste '(0 2 7 0 0 0 8 8 3 1 5 0));And this!
(define huntstomatoPaste '(0 2 7 0 0 0 3 5 8 1 8 0))

(define upc-good huntsTomatoPaste)
(define upc-bad1 huntsTomatoePast)
(define upc-bad2 huntstomatoPaste)

(define secret 48420295610439194978804589923121515475455500393246020365720930824673275)

(define (convert number base)
  (reverse (Convert number base)))

(define (Convert number base)
  (if (= number 0)
      '()
      (cons (modulo number base) (Convert (quotient number base) base))))

(define (base10 oldbase numberlist)
  (Base10 oldbase (reverse numberlist) 0))

(define (Base10 oldbase numberlist kount)
  (if (null? numberlist)
      0
      (+ (* (expt oldbase kount)(car numberlist)) (Base10 oldbase (cdr numberlist) (+ kount 1))))) 


(define secretMod 97)

(define (printSecret)
  (hexconvert (convert (quotient secret secretMod) 37))
  )

(define (myJoke)
  (display "Why couldn't the archaeologist read his map? It 1027565!")
  )

;===

(define (goldenTicketAnswers)
  (hexconvert (convert 366860 13))
  (hexconvert (convert 344770 13))
  )







