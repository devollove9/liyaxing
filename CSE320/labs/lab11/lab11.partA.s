
! Lab Exercise #11 (Part A)

        .global  main

        .section ".data"
        .align   4
nums:
        .byte    0x93, 0x2e
        .half    0x3a67, 0xba98, 0x7654
store:
        .word    0xffffffff, 0xeeeeeeee, 0xdddddddd

        .section ".text"
        .align   4
main:
        save     %sp, -96, %sp

        set      0x12345678, %l7         ! 0x12345678 --> %l7
        set      store, %l6              ! address of store --> %l6
  
        st       %l7, [%l6+0]            ! store word
        sth      %l7, [%l6+4]            ! store halfword
        stb      %l7, [%l6+8]            ! store byte

!  store+0:  ______  ______  ______  ______
!
!  store+4:  ______  ______  ______  ______
!
!  store+8:  ______  ______  ______  ______
 
        set      nums, %l5               ! address of nums --> %l5

        ld       [%l5+4], %l0            ! load word
        ldsh     [%l5+4], %l1            ! load signed halfword
        lduh     [%l5+4], %l2            ! load unsigned halfword
        ldsb     [%l5+4], %l3            ! load signed byte
        ldub     [%l5+4], %l4            ! load unsigned byte

!  l0:  ______  ______  ______  ______
!
!  l1:  ______  ______  ______  ______
!
!  l2:  ______  ______  ______  ______
!
!  l3:  ______  ______  ______  ______
!
!  l4:  ______  ______  ______  ______

        ret
        restore

