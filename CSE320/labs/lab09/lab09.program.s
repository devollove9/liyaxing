
/*****************************
  Lab Exercise #9
*****************************/ 

        .global  main

        .section ".text"
        .align   4
main:
        save     %sp, -96, %sp

! ****************
! *** Block #1 ***
! ****************

        set      W, %i0
        ld       [%i0], %l0
if1:
        cmp      %l0, 0x20
        ble      endif1
        nop
then1:
        sub      %l0, 10, %l0
endif1:

! ****************
! *** Block #2 ***
! ****************

        set      X, %i1
        ld       [%i1], %l1
if2:
        cmp      %l1, 0x50
        bg       else2
        nop
then2:
        add      %l1, 4, %l1
        ba       endif2
        nop
else2:
        sub      %l1, 8, %l1
endif2:

! ****************
! *** Block #3 ***
! ****************

        set      Y, %i2
        ld       [%i2], %l2
if3:
        cmp      %l2, 0x30
        bl       endif3
        nop
        cmp      %l2, 0x40
        bge      endif3
        nop
then3:
        mov      1, %l2
endif3:

! ****************
! *** Block #4 ***
! ****************

        set      Z, %i3
        ld       [%i3], %l3
if4:
        cmp      %l3, 0x38
        be       then4
        nop
        cmp      %l3, 0x48
        be       then4
        nop
        ba       endif4
        nop
then4:
        mov      10, %l3
endif4:

! ****************
! *** Block #5 ***
! ****************

        set      W, %i0
        ld       [%i0], %l4
        clr      %l5
loop1:
        cmp      %l4, 0x80
        bge      endloop1
        nop
        add      %l4, 20, %l4
        add      %l5, 1, %l5
        ba       loop1
        nop
endloop1:

! ****************
! *** Block #6 ***
! ****************

        set      X, %i1
        ld       [%i1], %l6
        clr      %l7
loop2:
        sub      %l6, 10, %l6
        add      %l7, 1, %l7
        cmp      %l6, 10
        bg       loop2
        nop
endloop2:

! ****************
! *** Block #7 ***
! ****************

        set      msg1, %o0
        call     printf
        nop

        set      msg1, %o0
        add      %o0, 0x30, %o1
        call     memory
        nop

        nop      ! Replace with call to iu_window
        nop

        ret
        restore

        .section ".data"
        .align   4

msg1:   .asciz   "\nLab Exercise #9\n"
        .align   4

W:      .word    55
X:      .word    72
Y:      .word    52
Z:      .word    78

