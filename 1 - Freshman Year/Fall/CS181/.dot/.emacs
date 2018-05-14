;; -*- Mode: Emacs-Lisp -*-

;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;
;;			Basic Customization			    ;;
;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;;

;;; Make F1 execute the `what-line' command, 
;;; which prints the current line number in the echo area.
(global-set-key [f1] 'what-line)

;;; Define an ad-hoc interactive function to print out the column
;;; number in the minibuffer (columns are counted starting from 0.)
(defun what-column ()
  "Print the current buffer column number."
  (interactive)
  (message "Column %d" (current-column)))

;; Make F2 execute the `what-column' interactive command defined above.
(global-set-key [f2] 'what-column)

;; Make F3 be `find-file'
(global-set-key [f3] 'find-file)

;; Make F4 be `save-buffer'
(global-set-key [f4] 'save-buffer)

;; Make F5 be "mark", F6 be "copy", F7 be "paste", F8 be "cut"
(global-set-key [f5] 'set-mark-command)
(global-set-key [f6] "\M-w")
(global-set-key [f7] "\C-y")
(global-set-key [f8] "\M-w")

;; Make F9 be `undo' 
(global-set-key [f9] 'undo)

;; Make F11 be `beginning-of-buffer' 
(global-set-key [f11] 'beginning-of-buffer)

;; Make F12 be `end-of-buffer'
(global-set-key [f12] 'end-of-buffer)

;; Shortcut for inserting tabs in code (useful for formatting comments)	 
;; Note that this does not work in TTY frames, where tab and shift-tab are
;; indistinguishable.  There, you'll have to stick with `C-q TAB'
;;
;; (define-key global-map '(shift tab) 'self-insert-command)

;;; ********************
;;; java-mode (the mode you're in when editing Java files)

;; Change the indentation amount to 2 spaces instead of 4.
;; You have to do it in this complicated way because of the
;; strange way java-mode initializes the value of `java-basic-offset'.
;;
;(add-hook 'java-mode-hook (lambda () (setq java-basic-offset 2)))

;;; Compile all java files in the current directory by default
(add-hook 'java-mode-hook
	  (lambda()
	    (set (make-local-variable 'compile-command) 
		 (concat "javac -g " (buffer-name)))))

;; java-mode key bindings
;; Make C-c C-c be "compile" 
;; Make C-c C-r be "comment-region", C-c C-u be "uncomment-region"
;; Make F9 be "recompile", F10 "next-error", F11 "java-shell", F12 "jdb"
(add-hook 'java-mode-hook (function (lambda ()
	 (define-key java-mode-map "\C-c\C-c" 'compile)
	 (define-key java-mode-map "\C-c\C-r" 'comment-region)
	 (define-key java-mode-map "\C-c\C-u" 'uncomment-region)
	 (define-key java-mode-map [f9] 'recompile)
	 (define-key java-mode-map [f10] 'next-error)
	 (define-key java-mode-map [f11] 'java-shell)
	 (define-key java-mode-map [f12] 'jdb)
	 )))

(defun java-shell ()
  (interactive)
  (java-shell-file-name 
    (replace-regexp-in-string ".java$" "" (buffer-name))))

(defun java-shell-file-name (classname)
  (shell "*java-shell*")
;; work-around to avoid color codes showing up as escape codes 
  (kill-new (concat "PS1=\"\\w> \"; "
	    "alias ls > /dev/null &> /dev/null && unalias ls; "
	    "printf \"\\n\\n\\tRunning Java on " classname " ...\\n\\n\" "
	    "&& java " classname))
  (yank)
  (comint-send-input)
)


;;; ********************
;;; Load a partial-completion mechanism, which makes minibuffer completion
;;; search multiple words instead of just prefixes; for example, the command
;;; `M-x byte-compile-and-load-file RET' can be abbreviated as `M-x b-c-a RET'
;;; because there are no other commands whose first three words begin with
;;; the letters `b', `c', and `a' respectively.
;;;
;;(load-library "completer")

;;; Misc variable customization

(setq current-language-environment "English")
(global-font-lock-mode t)
(setq ispell-program-name "aspell")

;;;
(add-hook 'text-mode-hook (function (lambda () (flyspell-mode 1))))
(add-hook 'text-mode-hook (function (lambda () (auto-fill-mode 1))))

;;; Plain black-on-white editing is the easiest on your eyes
(set-background-color "white")
(set-foreground-color "black")

;;; Make sure the following buffers get their own frames
(setq special-display-buffer-names '("*compilation*" "*grep*" "*java-shell*"))

;;; Use bash as shell when doing M-x shell
(setq explicit-shell-file-name "/usr/bin/bash.exe")


;;; shortcuts for changing font size
;;; use as "M-x my-<size>-font", where size is:
;;;   regular (12 pts) 
;;;   medium  (14 pts) 
;;;   large   (18 pts) 
;;;   huge    (24 pts)
;;;
;;; use "xlsfonts" on a shell to get a (much longer) list of alternatives
(defun my-regular-font ()
  "Set the frame's font size to 12."
  (interactive)
  (set-default-font
   "-*-courier-medium-r-normal--12-*-*-*-m-*-iso8859-1"))

(defun my-medium-font ()
  "Set the frame's font size to 14."
  (interactive)
  (set-default-font
   "-*-courier-medium-r-normal--14-*-*-*-m-*-iso8859-1"))

(defun my-large-font ()
  "Set the frame's font size to 18."
  (interactive)
  (set-default-font
   "-*-courier-medium-r-normal--18-*-*-*-m-*-iso8859-1"))

(defun my-huge-font ()
  "Set the frame's font size to 24."
  (interactive)
  (set-default-font
   "-*-courier-medium-r-normal--24-*-*-*-m-*-iso8859-1"))

;;; the .emacs file ends here.
