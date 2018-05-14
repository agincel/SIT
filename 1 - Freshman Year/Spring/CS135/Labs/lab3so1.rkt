#lang eopl
;Lab 3
;Adam Gincel
;I pledge my honor that I have abided by the Stevens Honor System.


(define (element? item list-of-items)        ;given
  (if (null? list-of-items)                  ;Is our "set" empty?
      #f                                     ;If empty, not an element!
      (if (equal? item (car list-of-items))  ;Is our item first in list?
          #t                                 ;Yes?  Then it's an element!
          (element? item (cdr list-of-items)))));No? Check the rest.

(define (make-set list-of-items) ;given
  (cond [(null? list-of-items);An empty list can have no duplicates,
         '()]                 ;So just return an empty list.
        [(element? (car list-of-items) (cdr list-of-items))
         (make-set (cdr list-of-items))];We keep only the LAST item
        [else                           ;if there are duplicates
         (cons (car list-of-items) (make-set (cdr list-of-items)))]))
         ;this cons keeps an item ONLY if no more are available in list

(define (union setA setB) ;my implementation
  (make-set (append setA setB)))

(define (intersection setA setB) ;given
  (if (null? setA) 
      '()
      (if (element? (car setA) setB)
          (make-set (cons (car setA) (intersection (cdr setA) setB))) ;inefficient fix
          (intersection (cdr setA) setB))))

(define (subset? setA setB) ;given
  (cond [(null? setA) 
         #t]
        [(element? (car setA) setB)
         (subset? (cdr setA)  setB)]
        [else #f]))


(define (set-equal? setA setB) ;my function
  (and (subset? setA setB) (subset? setB setA)))

(define (proper-subset? setA setB) ;my function
  (and (subset? setA setB) (not (set-equal? setA setB))))

(define (set-difference setA setB) ;given
  (make-set (Set-Difference setA setB)))

(define (Set-Difference setA setB)
  (if (null? setA)
      '()
  (if (not (element? (car setA) setB))
      (cons (car setA) (Set-Difference (cdr setA) setB))
      (Set-Difference (cdr setA) setB))))

(define (sym-diff setA setB)
  (make-set (append (set-difference setA setB) (set-difference setB setA))))

;--

(define (cardinality set)
  (length (make-set set)))


(define (disjoint? setA setB)
  (equal? (intersection setA setB) '()))

(define (superset? setA setB)
  (subset? setB setA))

(define (insert element set)
  (make-set (cons element set)))

(define (remove element set)
  (if(not (null? set))
     (if (not (equal? element (car set))) ;if this element isn't the one we're removing
         (cons (car set) (remove element (cdr set)))
         (remove element (cdr set)))
     '())
  )

(define (complement setA)
  (set-difference universe setA))

;--golden ticket answers:
;Three rooms understaffed: fudge, inventing, juicing

;Supervisor who works in every room: GranfallOompah 
;found by using: (intersection chocolate (intersection fudge (intersection inventing (intersection juicing (intersection marshmallow (intersection teevee taffypulling))))))

;Boss of Chocolate: Bob
;Boss of Fudge: Fob
;Boss of Inventing: Hobnob
;Boss of Juicing: Slob
;Boss of Marshmallow: Kabob
;Boss of teevee: Nabob
;Boss of Taffypulling: Gob

;Total Oompah Loompahs in for work: 49.






;--given at end of file


(define on40 '())
(define on41 '(Nederlander))
(define on42 '(NewAmsterdam Lyric Selwyn))
(define on43 '(StephenSondheim))
(define on44 '(St.James HelenHayes Majestic Broadhurst Shubert Belasco Minskoff))
(define on45 '(Hirschfeld Golden Jacobs Schoenfeld Booth Lyceum Imperial MusicBox Minskoff Marquis))
(define on46 '(RichardRodgers Lunt-Fontanne Imperial Marquis))
(define on47 '(BrooksAtkinson Palace Barrymore Friedman))
(define on48 '(Longacre WalterKerr Cort))
(define on49 '(O-Neill, Ambassador))
(define on50 '(Gershwin CircleInTheSquare))
(define on51 '(Gershwin))
(define on52 '(NeilSimon AugustWilson))
(define on53 '(Broadway))
(define on54 '(Studio54))
(define on55 '())
(define on56 '())
(define on57 '())
(define on58 '())
(define on59 '())
(define on60 '())
(define on61 '())
(define on62 '())
(define on63 '())
(define on64 '())
(define on65 '(VivianBeaumont))
(define on7th '(WinterGarden Palace))
(define onBroadway '(Marquis Minskoff Broadway Palace WinterGarden))
(define EastOf7th '(Palace Cort Lyceum Belasco Sondheim))
(define WestOf8th '(Hirschfeld))
(define Nederlander '(Nederlander Palace BrooksAtkinson Lunt-Fontanne Gershwin NeilSimon Marquis Minskoff RichardRodgers)) 
(define Jujamcyn '(St.James AugustWilson O-Neill Hirschfeld WalterKerr))
(define Shubert '(WinterGarden Shubert MusicBox Majestic Lyceum Longacre Golden Imperial Schoenfeld Barrymore Cort Jacobs Booth Broadway Broadhurst Belasco Ambassador))
(define independent '(HelenHayes CircleInTheSquare))
(define Disney '(NewAmsterdam))
(define Ambassador '(Lyric))
(define non-profit '(VivianBeaumont Selwyn StephenSondheim Studio54 Friedman))
(define Roundabout '(Selwyn StephenSondheim Studio54))
(define LincolnCenter '(VivianBeaumont))
(define MTC '(Friedman))
(define initialB '(Booth Broadhurst Belasco Broadway Barrymore BrooksAtkinson))
(define critic '(BrooksAtkinson WalterKerr))
(define producer '(Belasco Nederlander Shubert Golden Cort))
(define playwright '(O-Neill NeilSimon AugustWilson Broadhurst))
(define composer '(StephenSondheim Gershwin RichardRodgers))
(define actress '(VivianBeaumont Barrymore Lunt-Fontanne HelenHayes))
(define actor '(Booth Lunt-Fontanne))
(define cartoonist '(Hirschfeld))
(define people '(Nederlander StephenSondheim HelenHayes Shubert Belasco Booth Schoenfeld Jacobs Golden RichardRodgers Cort WalterKerr BrooksAtkinson VivianBeaumont NeilSimon AugustWilson O-Neill Minskoff Selwyn Gershwin Friedman Broadhurst Lunt-Fontanne WalterKerr Barrymore))
(define notPeople '(Palace Lyceum Majestic Lyric St.James WinterGarden Broadway Studio54 Ambassador CircleInTheSquare MusicBox Imperial Longacre NewAmsterdam Marquis)) 
(define ShubertAlley '(Shubert Booth))
(define universe (append people notPeople))


(define chocolate '(OompahBluempah OompahBaboonpah OopmahBalloonpah OopmahBoonpah OompahBuffoonpah OompahBroompah OompahFlewmpah OompahFumpah OompahKaboompah OompahCrewmpah OompahGoonpah OompahIgloompah OompahStewnpah OompahMaroonpah OompahZoompah OompahNoonpah OompahSaloonpah OompahRangoonpah Bob OompahBluempah OompahBaboonpah OopmahBalloonpah OopmahBoonpah OompahBuffoonpah OompahBroompah OompahFlewmpah OompahFumpah OompahKaboompah OompahCrewmpah OompahGoonpah OompahIgloompah OompahStewnpah OompahMaroonpah OompahZoompah OompahNoonpah OompahSaloonpah OompahRangoonpah GranfallOompah OompahBluempah OompahBaboonpah OopmahBalloonpah OopmahBoonpah OompahBuffoonpah OompahBroompah OompahFlewmpah OompahFumpah OompahKaboompah OompahCrewmpah OompahGoonpah OompahIgloompah OompahStewnpah OompahMaroonpah OompahZoompah OompahNoonpah OompahSaloonpah OompahRangoonpah)) 

(define fudge '(OompahFluempah OompahFlewmpah OompahFloompah OompahFoompah OompahFumpah OompahBluempah OopmahBoonpah OompahCroonpah OompahCrewmpah OompahGruempah OompahGrewmpah OompahSpoonpah OompahMonsoonpah OompahMoonpah OompahTunepah OompahSaloonpah OompahPontoonpah Fob OompahFluempah OompahFlewmpah OompahFloompah OompahFoompah OompahFumpah OompahBluempah OopmahBoonpah OompahCroonpah OompahCrewmpah OompahGruempah OompahGrewmpah OompahSpoonpah OompahMonsoonpah OompahMoonpah OompahTunepah OompahSaloonpah OompahPontoonpah GranfallOompah OompahFluempah OompahFlewmpah OompahFloompah OompahFoompah OompahFumpah OompahBluempah OopmahBoonpah OompahCroonpah OompahCrewmpah OompahGruempah OompahGrewmpah OompahSpoonpah OompahMonsoonpah OompahMoonpah OompahTunepah OompahSaloonpah OompahPontoonpah))

(define inventing '(OompahKazoompah OompahCroonpah OompahCukoompah OompahKaboompah OompahCrewmpah OompahBluempah OompahBaboonpah OompahFloompah OompahGloompah OompahGrewmpah OompahMaroonpah OompahMacaroonpah OompahNoonpah OompahLoonpah OompahRacoonpah OompahBarroompah Hobnob OompahCluempah OompahKazoompah OompahCroonpah OompahCukoompah OompahKaboompah OompahCrewmpah OompahBluempah OompahBaboonpah OompahFloompah OompahGloompah OompahGrewmpah OompahMaroonpah OompahMacaroonpah OompahNoonpah OompahLoonpah OompahRacoonpah OompahBarroompah GranfallOompah OompahCluempah OompahKazoompah OompahCroonpah OompahCukoompah OompahKaboompah OompahCrewmpah OompahBluempah OompahBaboonpah OompahFloompah OompahGloompah OompahGrewmpah OompahMaroonpah OompahMacaroonpah OompahNoonpah OompahLoonpah OompahRacoonpah OompahBarroompah))

(define juicing '(OompahIgloompah OompahGruempah OompahGrewmpah OopmahBalloonpah OompahBuffoonpah OompahFluempah OompahCluempah OompahCukoompah OompahStewnpah OompahMacaroonpah OompahTunepah OompahPrunepah OompahPontoonpah OompahRangoonpah Slob OompahGluempah OompahGoonpah OompahGloompah OompahIgloompah OompahGruempah OompahGrewmpah OopmahBalloonpah OompahBuffoonpah OompahFluempah OompahCluempah OompahCukoompah OompahStewnpah OompahMacaroonpah OompahTunepah OompahPrunepah OompahPontoonpah OompahRangoonpah GranfallOompah OompahGluempah OompahGoonpah OompahGloompah OompahIgloompah OompahGruempah OompahGrewmpah OopmahBalloonpah OompahBuffoonpah OompahFluempah OompahCluempah OompahCukoompah OompahStewnpah OompahMacaroonpah OompahTunepah OompahPrunepah OompahPontoonpah OompahRangoonpah))

(define marshmallow '(OompahStewnpah OompahMonsoonpah OompahMaroonpah OompahMacaroonpah OompahBaboonpah OopmahBoonpah OompahFlewmpah OompahFoompah OompahCluempah OompahKazoompah OompahGluempah OompahIgloompah OompahMoonpah OompahPrunepah OompahBarroompah OompahBrigadoonpah Kabob OompahSoonpah OompahSpoonpah OompahStewnpah OompahMonsoonpah OompahMaroonpah OompahMacaroonpah OompahBaboonpah OopmahBoonpah OompahFlewmpah OompahFoompah OompahCluempah OompahKazoompah OompahGluempah OompahIgloompah OompahMoonpah OompahPrunepah OompahBarroompah OompahBrigadoonpah GranfallOompah OompahSoonpah OompahSpoonpah OompahStewnpah OompahMonsoonpah OompahMaroonpah OompahMacaroonpah OompahBaboonpah OopmahBoonpah OompahFlewmpah OompahFoompah OompahCluempah OompahKazoompah OompahGluempah OompahIgloompah OompahMoonpah OompahPrunepah OompahBarroompah OompahBrigadoonpah))

(define teevee '(OompahZoompah OompahNoonpah OompahMoonpah OompahLoonpah OompahTunepah OompahPrunepah OompahBuffoonpah OompahFluempah OompahFloompah OompahCroonpah OompahKaboompah OompahGluempah OompahGoonpah OompahSoonpah OompahMonsoonpah OompahRacoonpah OompahBrigadoonpah Nabob OompahZoompah OompahNoonpah OompahMoonpah OompahLoonpah OompahTunepah OompahPrunepah OompahBuffoonpah OompahBroompah OompahFluempah OompahFloompah OompahCroonpah OompahKaboompah OompahGluempah OompahGoonpah OompahSoonpah OompahMonsoonpah OompahRacoonpah OompahBrigadoonpah GranfallOompah OompahZoompah OompahNoonpah OompahMoonpah OompahLoonpah OompahTunepah OompahPrunepah OompahBuffoonpah OompahBroompah OompahFluempah OompahFloompah OompahCroonpah OompahKaboompah OompahGluempah OompahGoonpah OompahSoonpah OompahMonsoonpah OompahRacoonpah OompahBrigadoonpah))

(define taffypulling '(OompahSaloonpah OompahPontoonpah OompahRacoonpah OompahRangoonpah OompahBarroompah OompahBrigadoonpah OopmahBalloonpah OompahBroompah OompahFoompah OompahFumpah OompahKazoompah OompahCukoompah OompahGloompah OompahGruempah OompahSoonpah OompahSpoonpah OompahZoompah OompahLoonpah Gob OompahSaloonpah OompahPontoonpah OompahRacoonpah OompahRangoonpah OompahBarroompah OompahGruempah OompahSoonpah OompahSpoonpah OompahZoompah OompahLoonpah GranfallOompah OompahSaloonpah OompahPontoonpah OompahRacoonpah OompahRangoonpah OompahBarroompah OompahBrigadoonpah OopmahBalloonpah OompahBroompah OompahFoompah OompahFumpah OompahKazoompah OompahCukoompah OompahGloompah OompahGruempah OompahSoonpah OompahSpoonpah OompahZoompah OompahLoonpah))

                         









 


