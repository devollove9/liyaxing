/****************************************************************************
  Yaxing Li
  CSE 320
  Project #8
****************************************************************************/
		.global is_negative
		.section ".text"
		.align 4
is_negative:
                set 0x80000000,%l6
		save %sp, -96, %sp
		
                andcc %i0,%l6,%l7
  
                cmp %l7,%l6
                be negative
		nop
valid:
		mov 0, %i0
		ba done
		nop

negative:
                mov 1,%i0
                nop
done:
		ret
		restore

/****************************************************************************/        
                .global is_zero
                .section ".text"
		.align 4
is_zero:
                set 0x80000000,%l6
                set 0x0,%l5
                set 0x0,%l6
		save %sp, -96, %sp
		
                orcc %i0,%l6,%l7
                orcc %i1,%l5,%l4
                cmp %l7,%l6
                be zero
		nop
validz:
		mov 0, %i0
		ba donez
		nop

zero:
                cmp %l4,%l5
                be zerotrue
                nop
                mov 0,%i0
                ba done
                nop
zerotrue:
                mov 1,%i0
                nop
donez:
		ret
		restore

/****************************************************************************/ 

                .global is_denormal
                .section ".text"
		.align 4
is_denormal:
                set 0x000fffff,%l6
                set 0x0,%l5
                set 0x7ff00000,%l4
                
		save %sp, -96, %sp
		
                andcc %i0,%l4,%l7
                andcc %i0,%l6,%l3
                
                
                cmp %l7,%l5
                be denormal
		nop
validd:
		mov 0, %i0
		ba doned
		nop

denormal:
                cmp %l5,%i1
                be denormal1
                mov 1,%i0
                ba doned
                nop
denormal1:
                cmp %l3,%l5
                be denormaltrue
                mov 1,%i0
                ba doned
                nop
denormaltrue:
                mov 0,%i0
                nop
doned:
		ret
		restore

/****************************************************************************/

                .global is_nan
                .section ".text"
		.align 4
is_nan:
                set 0x000fffff,%l6
                set 0x0,%l5
                set 0x7ff00000,%l4
		save %sp, -96, %sp
                andcc %i0,%l4,%l7
                andcc %i0,%l6,%l3            
                cmp %l7,%l4        
                be nan
		nop
        
validn:
		mov 0, %i0
		ba donen
		nop

nan:
                cmp %l5,%i1
                be nan1
                mov 1,%i0
                ba donen
                nop
nan1:
                cmp %l3,%l5
                be nantrue
                mov 1,%i0
                ba donen
                nop
nantrue:
                mov 0,%i0
                nop

donen:
		ret
		restore

/****************************************************************************/

                .global is_infinite
                .section ".text"
		.align 4
is_infinite:
                set 0x000fffff,%l6
                set 0x0,%l5
                set 0x7ff00000,%l4
		save %sp, -96, %sp
		set fmt1, %o0 ! Display the first 4-byte operand                
		andcc %i0,%l4,%l7
                andcc %i0,%l6,%l3  
                        
                cmp %l7,%l4  
                be infinite
		nop
validi:
		mov 0, %i0
		ba donei
		nop

infinite:
                cmp %l5,%i1
                be infinite1
                mov 0,%i0
                ba donei
                nop
infinite1:
                cmp %l3,%l5
                be infinitetrue
                mov 0,%i0
                ba donei
                nop
infinitetrue:
                mov 1,%i0
                nop

donei:
		ret
		restore

/****************************************************************************/

                .global is_finite
                .section ".text"
		.align 4
is_finite:
                set 0x000fffff,%l6
                set 0x0,%l5
                set 0x7ff00000,%l4
		save %sp, -96, %sp
		
                orcc %i0,%l6,%l7
        
                
                cmp %l7,%l6
                bne finite
		nop
validf:
		mov 1, %i0
		ba donen
		nop

finite:
                mov 1,%i0
                nop

donef:
		ret
		restore

/****************************************************************************/

                .global negate
                .section ".text"
		.align 4
negate:
                set 0x80000000,%l6
                set 0x7fffffff,%l5
		save %sp, -96, %sp
                nop
                andcc %i0,%l6,%l7
  
            
                !call iu_window
                cmp %l7,%l6
                be negateneg
		nop
validpos:
		orcc %i0,%l6,%l3
                st %l3,[%i2+0]
                
		ba donenegate
		nop

negateneg:
                andcc %i0,%l5,%l3
                st %l3,[%i2+0]
                nop

donenegate:
                
		ret
		restore

/****************************************************************************/

                .global absolute
                .section ".text"
		.align 4
absolute:
                set 0x7fffffff,%l6
                
		save %sp, -96, %sp
                nop
                andcc %i0,%l6,%l7
                st %l7,[%i2+0]
                
doneabsolute:
		ret
		restore

/****************************************************************************/

        

                .global display
                .section ".text"
		.align 4
display:
                set 0x000fffff,%l6
                set 0x000005ff,%l4
                set 0x7ff00000,%l5
                set 0xffffffff,%l7
		save %sp, -96, %sp
                nop
                
                !call iu_window
                andcc %i0,%l5,%l0
                andcc %i0,%l6,%l1
                andcc %i1,%l7,%l2
                srl %l0,20,%l0
                
                
                set fmt1,%o0
                mov %l1,%o1
                mov %l2,%o2
                call printf
                nop

                
                
                
                set fmt2,%o0
                mov %l0,%o1
                mov %l0,%o2
                call printf
                nop
                addcc %l4,%l0,%l1
                andcc %l4,%l1,%l1
                
                
                set fmt3,%o0 
                mov %l1,%o1
                mov %l1,%o2
                call printf
                nop
               ! set fmt4.%o0
               ! mov %l2,%o1
               ! call printf
               ! nip
                
                
donedisplay:
		ret
		restore

/****************************************************************************/
        
fmt1:	.asciz "Significantn: %05x%08x\n"
fmt2:	.asciz "Biased exponent: %x (%d)\n"
fmt3:	.asciz "True exponent:  %03x (%d)\n"
!fmt3:	.asciz "True exponent %08x\n  "
!fmt3:	!.ascii "----------\n"
!	.asciz "= %08x\n\n"
!fmt4:	.ascii "----------\n"
!	.asciz "= %08x (*** overflow ***)\n\n"
