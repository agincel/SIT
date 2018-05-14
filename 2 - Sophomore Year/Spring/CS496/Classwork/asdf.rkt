#lang racket

; <Program> -> <Expression>
;     let <identifier> = <Expression>
;          in <Expression>
;     complete

; 2)
;
; let <Identifier> = <Expression>
;     in <Expression>
;
; let x = <Expression>
;     in <Expression>
;
; let x = <Number>
;     in <Expression>
;
; let x = 2
;     in <Expression>
;
; let x = 2
;     in -(<Expression>, <Expression>)
;
; let x = 2
;     in -(<Identifier>, <Expression>)
;
; let x = 2
;     in -(x, <Expression>)
;
; let x = 2
;     in -(x, <Number>)
;
; let x = 2
;     in -(x, 1)