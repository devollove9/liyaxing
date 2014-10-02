
! Lab Exercise #11 (Part B)

! Program to read a character sequence from standard input and display it.
!
! Modify the program to copy the character sequence to another area of memory
! and display it again.

EOL = '\n'
SIZE = 60

        .global  main

        .section ".text"
        .align   4
fmt1:
        .asciz   "\nEnter a sequence of characters, then touch RET\n"
        .align   4
fmt2:
        .asciz   "\nThe character sequence is:\n>%s<\n"
        .align   4

main:
        save     %sp, -96, %sp

        set      fmt1, %o0        ! Prompt user to enter character sequence
        call     printf
        nop

        clr      %l0              ! Initialize character count
        set      original, %l7    ! address of .original --> %l7
loop:
        call     getchar          ! Returns one character in register o0
        nop

        cmp      %o0, EOL         ! Compare return value to newline
        be       endloop          ! If newline found, exit loop
        nop
        cmp      %l0, SIZE-1      ! Compare character count to memory size
        be       endloop          ! If too many characters, exit loop
        nop

        stb      %o0, [%l7+%l0]   ! Store character in memory

        inc      %l0              ! Increment character count
        ba       loop             ! Jump to top of loop
        nop
endloop:
        stb      %g0, [%l7+%l0]   ! Store null byte in memory

        set      fmt2, %o0        ! Display original character sequence
        set      original, %o1
        call     printf
        nop

!**********
!
! Add code here to copy the character sequence from the first memory area
! ("original") into the second memory area ("copy"), then print it again
!
!**********

        ret
        restore

        .section ".data"
        .align   4
original:
        .skip    60
        .align   4
copy:
        .skip    60
        .align   4

