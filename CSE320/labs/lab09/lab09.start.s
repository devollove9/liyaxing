
/******************************************************************************
  Lab #9 -- Part B

  The program reads zero or more characters from standard input.
******************************************************************************/

        .global  main

        .section ".text"
        .align   4
main:
        save     %sp, -96, %sp

loop:
        call     getchar          ! Read one character (returned in %o0)
        nop

        cmp      %o0, -1          ! Compare return value to EOF
        be       endloop          ! If EOF found, exit loop
        nop

        ba       loop             ! Jump to top of loop
        nop
endloop:
        ret
        restore

