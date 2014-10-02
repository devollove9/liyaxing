
/******************************************************************************
  Lab Exercise #13 -- support function
******************************************************************************/

! Function sum_vector

        .global  sum_vector

        .section ".text"
        .align   4
sum_vector:
        save     %sp, -96, %sp

        set      zero, %l7
        ldd      [%l7], %f0
        ldd      [%l7], %f30

        mov      0, %l2
        mov      0, %l3

        mov      0, %l1
loop:
        cmp      %l1, %i1
        bge      endloop
        nop

        ! Multiply %l1 by 8 using ".umul"

        mov      %l1, %o0
        mov      8, %o1
        call     .umul
        nop
        mov      %o0, %l0

        ldd      [%i0+%l0], %f2
        faddd    %f0, %f2, %f0
if:
        fcmpd    %f2, %f30
        nop
        fbge     else
        nop
then:
        inc      %l2
        ba       endif
        nop
else:
        inc      %l3
endif:
        inc      %l1
        ba       loop
        nop
endloop:
        st       %l2, [%i2]
        st       %l3, [%i3]

        restore
        retl
        nop

        .align   8
zero:
        .double  0r0.0

