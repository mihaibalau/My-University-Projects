
; Write a function to return the sum of two vectors.

( DEFUN VSUM (V1 V2)
( COND
  ( (NULL V1) V2)
  ( (NULL V2) V1)
  ( T (CONS ( + (CAR V1) (CAR V2))
      (VSUM ( CDR V1) (CDR V2))))))

; Convert a tree of type (2) to type (1).
; Type one tree: (A 2 B 0 C 2 D 0 E 0)
; Type two tree: (A (B) (C (D) (E)))

(defun P4 (tree)
  (cond
    ((null tree) nil)
    (t (
        append (list (car tree) (length (cdr tree)))
               (mapcan #'P4 (cdr tree))
       )
    )
  )
)

; Write a function that returns the product of numeric atoms in a list, at any level.

(defun P4 (L)
    (cond
      ((null L) 1)
      ((numberp L) L)
      ((listp L) (apply '*(mapcar #'P4 L)))
      (t 1)
    ) 
)


; Write a function that produces the linear list of all atoms of a given list, from all levels, and written in 
; the same order. Eg.: (((A B) C) (D E)) --> (A B C D E)

(defun P16 (L)
    (cond
      ((Null L) nil)
      ((listp L) (apply #'append (mapcar #'P16 L)))
      (t (list L))
    ) 
)
