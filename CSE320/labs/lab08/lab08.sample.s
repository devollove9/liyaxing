
/******************************************************************************

  Lab Exercise #8 -- demonstrate use of "reglib" functions

  Compute (A*5-B) * (C+D) / 2 and store results at X, display memory and regs

  Translate (assemble and link) using:

    gcc lab08.sample.s ~cse320/lib/reglib.o

******************************************************************************/

        .global  main

        .section ".text"
        .align   4
main:
        save     %sp, -96, %sp

        set      A, %r24
        ld       [%r24], %r16      ! load value at loc A into register %r16
        set      B, %r25
        ld       [%r25], %r17      ! load value at loc B into register %r17
        set      C, %r26
        ld       [%r26], %r18      ! load value at loc C into register %r18
        set      D, %r27
        ld       [%r27], %r19      ! load value at loc D into register %r19

        smul     %r16, 5, %r23     ! register %r23 <== A*5
        sub      %r23, %r17, %r23  ! register %r23 <== A*5 - B
        add      %r18, %r19, %r22  ! register %r22 <== C+D
        smul     %r23, %r22, %r21  ! register %r21 <== (A*5 - B) * (C+D)
        mov      0, %y             ! register %y <= upper 32 bits of dividend
        sdiv     %r21, 2, %r20     ! register %r20 <== (A*5 - B) * (C+D) / 2

        set      X, %r28
        st       %r20, [%r28]      ! store contents of register %r20 at loc X

        set      main, %r8         ! register %r8 contains first address
        set      main+0x280, %r9   ! register %r9 contains second address
        call     memory            ! display memory (from main to main+0x27f)
        nop

        set      A, %r8            ! register %r8 contains first address
        set      X+4, %r9          ! register %r9 contains second address
        call     memory            ! display memory (from A to X+3)
        nop

        call     iu_registers      ! display registers
        nop

        ret
        restore

        .section ".data"
        .align   4

A:      .word    15
B:      .word    23
C:      .word    18
D:      .word    29
X:      .word    0

