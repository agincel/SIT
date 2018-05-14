(module interp (lib "eopl.ss" "eopl")
  
  ;; interpreter for the LET language.  The \commentboxes are the
  ;; latex code for inserting the rules into the code in the book.
  ;; These are too complicated to put here, see the text, sorry.

  (require "drscheme-init.scm")
  (require "lang.scm")
  (require "data-structures.scm")
  (require "environments.scm")
  
  (provide value-of-program value-of)

;;;;;;;;;;;;;;;; the interpreter ;;;;;;;;;;;;;;;;

  ;; value-of-program : Program -> ExpVal
  ;; Page: 71
  (define value-of-program 
    (lambda (pgm)
      (cases program pgm
        (a-program (exp1)
          (value-of exp1 (init-env))))))

  ;; value-of : Exp * Env -> ExpVal
  ;; Page: 71
  (define value-of
    (lambda (exp env)
      (cases expression exp

        ;\commentbox{ (value-of (const-exp \n{}) \r) = \n{}}
        (const-exp (num) (num-val num))

        ;\commentbox{ (value-of (var-exp \x{}) \r) = (apply-env \r \x{})}
        (var-exp (var) (apply-env env var))

        ;\commentbox{\diffspec}
        (diff-exp (exp1 exp2)
          (let ((val1 (value-of exp1 env))
                (val2 (value-of exp2 env)))
            (let ((num1 (expval->num val1))
                  (num2 (expval->num val2)))
              (num-val
                (- num1 num2)))))

        ;\commentbox{\zerotestspec}
        (zero?-exp (exp1)
          (let ((val1 (value-of exp1 env)))
            (let ((num1 (expval->num val1)))
              (if (zero? num1)
                (bool-val #t)
                (bool-val #f)))))
              
        ;\commentbox{\ma{\theifspec}}
        (if-exp (exp1 exp2 exp3)
          (let ((val1 (value-of exp1 env)))
            (if (expval->bool val1)
              (value-of exp2 env)
              (value-of exp3 env))))

        ;\commentbox{\ma{\theletspecsplit}}
        (let-exp (var exp1 body)       
          (let ((val1 (value-of exp1 env)))
            (value-of body
              (extend-env var val1 env))))

        ;; Extensions follow
        (minus-exp (exp1)
                   (let ((val1 (value-of exp1 env)))
                     (let ((num1 (expval->num val1)))
                       (num-val
                       (* -1 num1)))))

        (add-exp (exp1 exp2)
          (let ((val1 (value-of exp1 env))
                (val2 (value-of exp2 env)))
            (let ((num1 (expval->num val1))
                  (num2 (expval->num val2)))
              (num-val
                (+ num1 num2)))))

        (mult-exp (exp1 exp2)
          (let ((val1 (value-of exp1 env))
                (val2 (value-of exp2 env)))
            (let ((num1 (expval->num val1))
                  (num2 (expval->num val2)))
              (num-val
                (* num1 num2)))))

        (div-exp (exp1 exp2)
          (let ((val1 (value-of exp1 env))
                (val2 (value-of exp2 env)))
            (let ((num1 (expval->num val1))
                  (num2 (expval->num val2)))
              (num-val
                (/ num1 num2)))))

        (cons-exp (exp1 exp2)
           (let ((val1 (value-of exp1 env))
                 (val2 (value-of exp2 env)))
             (cond
               [(and (equal? val1 (list-val '())) (equal? val2 (list-val '())))
                  (list-val '())]
               [(equal? val2 (list-val '()))
                  (let ((list1 (expval->list (list-val (list val1)))))
                    (list-val list1))]
               [(equal? val1 (list-val '()))
                  (let ((list2 (expval->list (list-val (list val2)))))
                    (list-val list2))]
               [else
                  (let ((list1 (expval->list (list-val (list val1 val2)))))
                    (list-val list1))])))

        (car-exp (e1)
            (let ((val1 (value-of e1 env)))
              (let ((list1 (expval->list val1)))
                (cond
                  [(= (length list1) 0) (write "contract violation, send car an emptylist")]
                  [else (car list1)]
                  ))))

        (cdr-exp (e1)
            (let ((val1 (value-of e1 env)))
              (let ((list1 (expval->list val1)))
                (cond
                  [(= (length list1) 1) (list-val '())]
                  [(= (length list1) 0) (write "contract violation, sent cdr an emptylist")]
                  [else (list-val (cdr list1))])
                )))
                 
        (null-exp (exp1)
            (let ((val1 (value-of exp1 env)))
                (bool-val
                 (or
                  (equal? val1 (list-val '()))
                  (equal? val1 (num-val 0))
                  ))))
      
        (emptylist-exp ()
                       (list-val '()))

)
  )))

