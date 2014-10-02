/****************************************************************************
  Yaxing Li
  CSE 320
  Project #10
****************************************************************************/
!**************************************************
! Function:	absolute
!
! Purpose:	Return absolute value of X.
!
!**************************************************
	.global	absolute
	.section ".text"
	.align 4
absolute:
 
	save	%sp, -112, %sp
 
 
	std	%i0, [%sp+96]
	ldd	[%sp+96], %f2		! Load X into FPU Register
 
 
	mov	0, %l0
	std	%l0, [%sp+96]
 
	ldd	[%sp+96], %f4		! Load Zero into FPU Register for comparrison
	fitod	%f4, %f6		! Convert to double
 
 
	fcmpd	%f2, %f6		! Compare X to Zero
	nop
 
 
	fbl	negate
	nop
 
 
	fmovd	%f2, %f0		! Return value if positive
 
 
	ba	end
	nop
 
 
negate:
 
	mov	-1, %l0
	std	%l0, [%sp+96]
 
	ldd	[%sp+96], %f4		! Load negative into FPU Register
	fitod	%f4, %f6		! Convert to double
 
 
	fmuld	%f6, %f2, %f0		! Multiply by negative
 
end:
 
	ret
	restore
 
 
 
 
!***************************************************
! Function:	sqroot
!
! Purpose:	Return square root of X.
!
!***************************************************
	.global sqroot
	.section ".text"
	.align 4
sqroot:
 
	save	%sp, -112, %sp
 
 
	std	%i0, [%sp+96]
	ldd	[%sp+96], %f2		! Load X into FPU Register
 
 
	fsqrtd	%f2, %f0		! Calculate square root
 
 
	ret
	restore
 
 
 
 
!**************************************************
! Function:	factorial
!
! Purpose:	Return factorial of N
!
!**************************************************
	.global	factorial
	.section ".text"
	.align 4
factorial:
 
	save	%sp, -112, %sp
 
 
	std	%i0, [%sp+96]
	ldd	[%sp+96], %f2		! Load N into FPU Register
 
	mov	1, %l0
	std	%l0, [%sp+96]
 
	ldd	[%sp+96], %f4		! Load one into FPU Register
	fitod	%f4, %f4
 
	fmovd	%f4, %f6
 
loop:
	fcmpd	%f2, %f4		! Compare value to one
	nop
 
	fble	endloop
	nop
 
	fmuld	%f6, %f2, %f6		! Multiply value by the current total
	fsubd	%f2, %f4, %f2		! Decrement value of multiplier
 
	ba	loop
	nop
 
endloop:
 
	fmovd	%f6, %f0		! Return factorial
 
	ret
	restore
 
 
 
 
!**************************************************
! Function:	power
!
! Purpose:	Return X raised to the Nth power.
!
!**************************************************
	.global power
	.section ".text"
	.align 4
power:
 
	save	%sp, -112, %sp
 
	std	%i0, [%sp+96]
	ldd	[%sp+96], %f2
 
	cmp	%i2, %r0		! Compare power to zero (Return 1 if 0)
	be	zero
	nop
 
	std	%i2, [%sp+96]
	ldd	[%sp+96], %f4		! Load power into FPU Register
	fitod	%f4, %f4		! Convert power to double
 
	mov     1, %l0
	std     %l0, [%sp+96]
 
	ldd     [%sp+96], %f6           ! Load one into FPU Register for comparrison
	fitod   %f6, %f6
 
	mov     1, %l0
	std     %l0, [%sp+96]
 
	ldd     [%sp+96], %f8           ! Load one into answer
	fitod   %f8, %f8
 
	mov     1, %l0
	std     %l0, [%sp+96]
 
	ldd     [%sp+96], %f10		! Load one into FPU Register to increment "index"
	fitod   %f10, %f10
 
loop1:
 
	fcmpd   %f6, %f4		! Compare index to power
	nop
	fbg     endloop1
	nop
 
 
	fmuld	%f8, %f2, %f8		! Multiply value (X) by answer
	faddd	%f6, %f10, %f6		! Increment the "index"
 
	ba	loop1
	nop
 
endloop1:
 
	ba	end1
	nop
 
zero:
 
	mov	1, %l0
	std	%l0, [%sp+96]
	ldd	[%sp+96], %f8		! Load one into FPU Register
	fitod	%f8, %f8		! Convert to double precision
 
end1:
 
	fmovd	%f8, %f0		! Return X to the Nth power
 
	ret
	restore
 
 
 
 
 
 
!*******************************************
! Function:	sine
!
! Purpose:	Return value of sine X
!
!*******************************************
	.global sine
	.section ".text"
	.align 4
sine:
	save	%sp, -112, %sp
 
	std	%i0, [%sp+96]
	ldd	[%sp+96], %f12		! Load value into FPU Register
 
	set	0x3e112e0b, %l0
	std	%l0, [%sp+96]
	ldd	[%sp+96], %f14		! Load 1.0e-9 into FPU Register for precision comparrison
 
	mov	1, %l0			! Initialize the index for the power series
 
	std	%l0, [%sp+96]
 
	ldd	[%sp+96], %f28		! Load the value one into the answer register
 
 
	fitod	%f28, %f28		! Convert to double precision
 
	mov	-1, %l2
	std	%l2, [%sp+96]
	ldd	[%sp+96], %f16		! Load negative one into FPU Register for calculations
	fitod	%f16, %f16		! Convert to double precision
 
	mov	2, %l3
loop2:
!!!
!	inc	%l0
!!!
	std	%f16, [%sp+96]
	ldd	[%sp+96], %o0		! Load negative one into output register
	mov	%l0, %o2		! Copy the power series index into output register
	call	power			! Calculate (-1)^k
	nop
	fmovd	%f0, %f18 		! Move (-1)^k to FPU Register
 
	umul	%l3, %l0, %l4		! Calculate 2k
 
	std	%i0, [%sp+96]
	ldd	[%sp+96], %o0
	mov	%l4, %o2
	call	power			! Calculate X^(2k)
	nop
	fmovd	%f0, %f20
 
	std	%l4, [%sp+96]
	ldd	[%sp+96], %f30		! Load 2k into FPU Register
 
 
 
!!!
!	mov     1, %l6
!	std     %l6, [%sp+96]
 
!	ldd     [%sp+96], %f10		! Load one into FPU Register to increment "index"
 
!	faddd	%f30, %f10, %f30		! add 1 to 2k
!	fitod   %f10, %f10
!!!
 
 
 
	fitod	%f30, %f30		! Convert 2k to double precision
 
 
	std	%f30, [%sp+96]
	ldd	[%sp+96], %o0
	call	factorial		! Calculate (2k)!
	nop
	fmovd	%f0, %f24
 
	fdivd	%f20, %f24, %f26	! Calculate ( (X^(2k) ) / (2k)!)
 
	fcmpd	%f26, %f14		! Compare the current value in the power series to 1.0e-9
	nop
	fbl	endloop2
	nop
 
	fmuld	%f26, %f18, %f26	! Multiply the current value of the power series by (-1)^k
 
	faddd   %f26, %f28, %f28        ! Add the result to the answer
 
	inc	%l0			! Increment k
 
	ba	loop2
	nop
 
endloop2:
	fmovd	%f28, %f0
 
	ret
	restore
