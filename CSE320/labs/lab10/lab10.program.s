
/****************************************************************************
  Lab Exercise #10
****************************************************************************/ 
 
        .global  sum_list
        .global  main

!********************
! Function sum_list
!********************

        .section ".text"
        .align   4
sum_list:
        save     %sp, -96, %sp

        call     iu_window
        nop

        clr      %l7             ! initialize the sum

        mov      %i0, %l0        ! base address of array
        mov      %i1, %l1        ! number of elements in array
        clr      %l2             ! initialize index
loop:
        cmp      %l2, %l1        ! compare index and limit
        bge      endloop
        nop

        !************************
        ! Insert your code here
        !************************

                                 ! offset = index * 4
                                 ! load from RAM[base address + offset]
                                 ! add to sum

        inc      %l2             ! increment index
        ba       loop
        nop
endloop:
        mov      %l7, %i0        ! return the sum

        ret
        restore

!********************
! Function main
!********************

        .section ".text"
        .align   4
main:
        save     %sp, -96, %sp

        set      main, %l0
        set      format, %l1
        set      total, %l2
        set      list, %l3
        set      endlist, %l4
        set      sum_list, %l5
        set      loop, %l6
        set      endloop, %l7
        set      iu_window, %i0
        set      memory, %i1

        call     iu_window
        nop

        set      sum_list, %o0
        add      %o0, 0x150, %o1
        call     memory
        nop

        set      list, %l0       ! address of "list"
        set      endlist, %l1    ! address of "endlist"

        sub      %l1, %l0, %l2   ! compute number of bytes in the list
        sra      %l2, 2, %l3     ! compute number of elements in the list

        mov      %l0, %o0        ! first arg = address of list
        mov      %l3, %o1        ! second arg = number of elements
        call     sum_list        ! compute sum of list elements
        nop

        set      total, %l4      ! address of total
        st       %o0, [%l4]      ! store sum in memory

        set      format, %o0     ! first arg = address of format
        mov      %l3, %o1        ! second arg = number of elements
        ld       [%l4], %o2      ! third arg = sum
        call     printf
        nop

        ret
        restore

format:
        .asciz   "\nThe sum of the %d elements in the array is %d\n"

        .section ".data"
        .align   4
total:
        .skip    4
list:
        .word    10, 20, 30, 40, 50, 60, 70, 80
endlist:

