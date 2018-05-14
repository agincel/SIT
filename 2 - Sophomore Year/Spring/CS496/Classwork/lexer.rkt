
(module lexer racket

  (provide (all-defined-out))
  
  (require eopl/eopl)

  (define-datatype token token?
    (open-par-t)
    (close-par-t)
    (lambda-t)
    (app-t)
    (ident-t
     (id symbol?))
    (eof-t))

  (define (eofToken? t)
    (cases token t
      [eof-t () #t]
      [else #f]))
  
  ;; String -> listof token?
  (define (tokenize str)
    (tokenize-list (string->list str)))
  
  ;; listof char? -> listof token?
  ;; Note: for simplicity we assume variable names do not start with "l" nor "a"
  ;; Also, variables only consist of alphabet characters
  (define (tokenize-list xs)
    (cond
      [(eq? xs '()) (list (eof-t))]
      [(eq? (car xs) #\space ) (tokenize-list (cdr xs))]
      [(eq? (car xs) #\( ) (cons (open-par-t) (tokenize-list (cdr xs)))]
      [(eq? (car xs) #\) ) (cons (close-par-t) (tokenize-list (cdr xs)))]
      [(eq? (car xs) #\l ) (if (and (> (length xs) 4) (equal? (list->string (take xs 3)) "lam"))
                               (cons (lambda-t) (tokenize-list (drop xs 3)))
                               (error "Unrecognized token: did you mean lam?"))]
      [(eq? (car xs) #\a ) (if (and (> (length xs) 4) (equal? (list->string (take xs 3)) "app"))
                               (cons (app-t) (tokenize-list (drop xs 3)))
                               (error "Unrecognized token: did you mean app?"))]
      [(char-alphabetic? (car xs)) (cons (ident-t (string->symbol (list->string (takef xs char-alphabetic?)))) (tokenize-list (dropf xs char-alphabetic?)))]
      [else (error "Unrecognized token")]))


  )