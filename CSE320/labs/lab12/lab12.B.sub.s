
/******************************************************************************
  Lab Exercise #12, Part B -- support module
******************************************************************************/

! Function real_roots
!
! Called from C using:
!
!   real_roots( &A, &B, &Disc, &Root1, &Root2 );

        .global  real_roots

        .section ".text"
        .align   4
real_roots:
        save     %sp, -96, %sp

! Fetch 2.0 from memory

        set      rcon2, %l0      ! Load 2.0 into f30 and f31
        ldd      [%l0], %f30

! Fetch A, B and Disc from memory

        ldd      [%i0], %f0      ! Load A into f0 and f1
        ldd      [%i1], %f2      ! Load B into f2 and f3
        ldd      [%i2], %f4      ! Load Disc into f4 and f5

! Compute 2.0 * A

        fmuld    %f30, %f0, %f28

! Compute sqrt( disc )

        fsqrtd   %f4, %f26

! Compute -B


! Compute -B + sqrt( Disc )


! Compute (-B+sqrt(Disc)) / (2.0*A)


! Compute -B - sqrt( Disc )


! Compute (-B-sqrt(Disc)) / (2.0*A)


! Store Root1 and Root2 in memory


        ret
        restore

        .align   8
rcon2:
        .double  0r2.0

