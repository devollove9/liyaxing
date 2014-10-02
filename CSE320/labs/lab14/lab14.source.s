
! Lab Exercise #14

        .section ".text"
        .align   4
unpack:
        set      masks, %l7
        ld       [%l7+0], %o2
        ld       [%l7+4], %o3
        ld       [%l7+8], %o4
        and      %o1, %o2, %o2
        and      %o1, %o3, %o3
        and      %o1, %o4, %o4

        retl
        nop

        .section ".data"
        .align   4
list:   .single  0r-64.0
        .single  0r+1.625
        .single  0r-1.3e-6
        .single  0r-100.0625
        .single  0r+12.6e+32

masks:  .word    0x80000000
        .word    0x7f800000
        .word    0x007fffff

fmt:    .asciz   "Number: %8.8x Fields: %8.8x %8.8x %8.8x\n"
        .align   4

SIZE    =        5

        .global  main
        .section ".text"
        .align   4
main:
        save     %sp, -96, %sp

        mov      0, %l0
        set      list, %l2
loop:
        cmp      %l0, SIZE
        bge      endloop
        nop

        sll      %l0, 2, %l1
        ld       [%l2+%l1], %o1
        call     unpack
        nop
        set      fmt, %o0
        call     printf
        nop

        inc      %l0
        ba       loop
        nop
endloop:

        ret
        restore

