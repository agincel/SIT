#lang eopl

(define (pig-latin wordaslist)
  (if (not (null? wordaslist))
      (append (cdr wordaslist) (cons (car wordaslist) '(a y)))
      '())) ;mine from week 2

(define (tax2012cond income)
  (cond ((<  income 0)     (display "You made less than zero?"))
        ((<= income 8700)               (*    income         0.10))
        ((<= income 35350) (+ 870       (* (- income 8700)   0.15)))
        ((<= income 85650) (+ 4867.5    (* (- income 35350)  0.25)))
        ((<= income 178650)(+ 17442.5   (* (- income 85650)  0.28)))
        ((<= income 388350)(+ 43482.5   (* (- income 178650) 0.33)))
        (else              (+ 112683.15 (* (- income 388350) 0.35))) ) ) ;given

(define (BMI height weight)
  (define metricHeight (* height 0.0254))
  (define metricMass (* weight 0.453592))
  (define yourBMI (/ metricMass (* metricHeight metricHeight)))
  (cond [(<= yourBMI 16) (list yourBMI "Severely Underweight")]
        [(<= yourBMI 18.5) (list yourBMI "Underweight")]
        [(<= yourBMI 25) (list yourBMI "Normal")]
        [(<= yourBMI 30) (list yourBMI "Overweight")]
        [(<= yourBMI 40) (list yourBMI "Obese")]
        [else (list yourBMI "Morbidly Obese")]
        )) ;made myself

(define (arithmetic-prog start step length)
  (if (> length 0) 
         
      (cons start (arithmetic-prog (+ start step) step (- length 1))) 
          
      '()
          
   )) ;made myself

(define (geometric-prog start step length)
  (if (> length 0) 
         
      (cons start (geometric-prog (* start step) step (- length 1))) 
          
      '()
          
   )) ;made myself



(define (sum list-of-nums)
  (if (not (null? list-of-nums))
      
      (+ (car list-of-nums) (sum (cdr list-of-nums)))
      
      0
      
      )) ;made myself

(define (arith-sum start step length)
  (+ (* start length) (* step length (/ (- length 1) 2)))) ;made myself

(define (geo-sum start step length)
  [* start (/ (- (expt step (+ length 0)) 1) (- step 1))]) ;made myself

;--

(define (make-duples item list-of-items)
  (if (not (null? list-of-items))
      (cons (list item (car list-of-items)) (make-duples item (cdr list-of-items)))
      '()
  )
  ) ;made myself

(define (cart-prod setA setB)
  (if (not (null? setA))
     [append (make-duples (car setA) setB) (cart-prod (cdr setA) setB)]
     '()
     )
  ) ;made myself

;--

(define (make-triplesC itemA itemB listC)
  (if (not (null? listC))
      (cons (list itemA itemB (car listC)) (make-triplesC itemA itemB (cdr listC)))
      '()
      
   )) ;made myself

(define (make-triplesB itemA listB listC)
  (if (not (null? listB))
      (append (make-triplesC itemA (car listB) listC) (make-triplesB itemA (cdr listB) listC))
      '()
      )
  )

(define (triple-cart-prod setA setB setC)
  (if (not (null? setA))
      (append (make-triplesB (car setA) setB setC) (triple-cart-prod (cdr setA) setB setC))
      '()
      )
  )
  
;given
(define salad  '(Caesar IcebergWedge Cobb Waldorf))
(define side   '(MixedVeggies Spinach Asparagus))
(define starch '(BakedPotato RicePilaf  Mac&Cheese Succotash)) 
(define bev    '(coffee tea cappuccino cognac port))
(define dessert '(CremeBrulee StrawberryShortcake BakedAlaska))
(define soup    '(Tomato ChickenNoodle))
(define entree  '(RoastBeef SteamedLobster FriedTofu Liver&Onions))



