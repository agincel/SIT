#lang eopl
(define firstlist (list 3 4 5 6))
(define secondlist '(7 8 9 10))

(define ay '(a y))

(define (last list-of-things)
  (car(reverse list-of-things)))

(define (yoda list-of-three)
  (cons (last list-of-three) (reverse (cdr (reverse list-of-three)))))

(define (pig-latin wordaslist)
  (append (cdr wordaslist) (cons (car wordaslist) ay)))

;--

(define student 
  '((IDnumber DegreeSought) (LastName FirstName) (day month year) (class/year ((major) (minor)) GPA) ((number street apt) (city state zip)) (class1 class2 ... classN))) ;given

(define Charlie 
  '((123456789 BS) (Bucket Charles) (4 July 1976) (2015 ((CS math) (theater)) 4.00) ((221 BakerSt B) (Hoboken NJ 07030)) (CS135 CS284 CS385)))


(define (IDnum student-name)   ;this will be a number
  (car (car student-name)))

(define (lastname student-name) ;this will be just a name
  (car (cadr student-name)))

(define (GPA student-name)     ;this will be a number
  (last (cadddr student-name)))

(define (birthdate student-name)  ;this will be a list
  (caddr student-name))
  
(define (address student-name) ;this will be a list of lists
  (cadr (reverse student-name)))

(define (class student-name)    ;This will be a number (year)
  (car (cadddr student-name)))

(define (schedule student-name) ;this will be a list.
  (last student-name))

;----

(define (YODA list-of-three)
  (cons (last list-of-three) (list (car list-of-three) (cadr list-of-three))))

;--Golden Ticket

(define AugustusGloop
  '((((A) (u g))) ((u) (s (t)) ((u) s) (G l (o * o)) (p))))

;(define AugustusGloop1
 ; '((A) (u g))) ((u) (s (t)) ((u) s) (G l (o * o)) (p))

(define (c!@#&$...%^r Augustus)
  (cadr (caddr (cadddr (cadr Augustus)))))

(define (get list-of x)
  (if (null? list-of) (display "out of bounds")
  (if (= x 0) 
      (car list-of)
    (get (cdr list-of) (- x 1)))))






