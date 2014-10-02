
! Program for Lab Exercise #8

        .global  main

        .section ".text"
        .align   4
main:
        save     %sp, -96, %sp

        set      A, %r27          ! Put address of "A" into register
        ld       [%r27], %r16     ! Load contents of "A" into register

        set      B, %r28          ! Put address of "B" into register
        ld       [%r28], %r17     ! Load contents of "B" into register

        smul     %r16, %r16, %r18
        smul     %r18, 3, %r19

        smul     %r16, 6, %r20
        smul     %r20, %r17, %r21

        smul     %r17, 3, %r22
        smul     %r22, %r22, %r23

        sub      %r19, %r21, %r24
        add      %r24, %r23, %r25

        set      C, %r29          ! Put address of "C" into register
        st       %r25, [%r29]     ! Store contents of register into "C"

        ret
        restore

        .section ".data"
        .align   4

A:      .word    5
B:      .word    4
C:      .word    0

