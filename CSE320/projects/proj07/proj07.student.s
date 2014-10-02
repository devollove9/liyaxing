/****************************************************************************
  Yaxing Li
  CSE 320
  Project #7
****************************************************************************/
	.global main
        .section ".text"
        .align 4
        
main:   save %sp, -96, %sp
        
        set fmt, %r8           ! First arg -- address of format string
        call printf             ! Prompt the user to enter a line
        nop 
        
        clr %r17                ! Initialize character count
        clr %r18                ! Initialize white space  count
        clr %r19                ! Initialize octal count
        clr %r20                ! Initialize decimal count
        clr %r21                ! Initialize hexdecimal count
        clr %r22                ! Initialize letters count
        clr %r23                ! Initialize control characters count
        clr %r24                ! Initialize printable characters count
        clr %r16                ! Initialize characters count
        
loop:   call getchar            ! Read one character (returned in %r8)        
        nop
        mov %r8,%r25            !copy value to %r25 temp location
        
        cmp %r25,-1              !exit when EOF found
        beq end
        nop
        call putchar            ! print out character got
        nop
        inc %r16                ! Increment character count
        nop
       


! control characters if:0x00-0x1F
!                    if2:0x7F
!                    
if:     cmp %r25,0x00
        blt loop
        cmp %r25,0x1F            !if >1F jump to if2
        bgt if2
        nop
then:   inc %r23                ! increment control count
        ba if3
        nop
if2:    cmp %r25,0x7F            !if not equal to 0x7F jump to if5
        bne if5
        nop
then2:  inc %r23
        ba loop
        nop        


!NewLine if3:0x0A
if3:    cmp %r25, 0x0A           ! Compare return value to new line
        bne if4                 ! If newline not found, skip increment
        nop       
then3:  inc %r18                ! Increment white space count
        inc %r17                ! Increment newline count
        ba loop
        nop

!White Spaces if4: 0x09
if4:    cmp %r25, 0x09           ! Compare return value to blank
        bne loop                ! If tab not found, branch top
        nop      
then4:  inc %r18                ! Increment blank count
        ba loop
        nop


!Space (enter char: >0x1F and not queal to 0x7F)        
if5:    cmp %r25, 0x20           !if r8 == 0x20(Space)
        bne if6                 !if not space branch to if6
        nop
        
then5:  inc %r18                ! Increment white space count
        inc %r24                ! Increment printable count
        ba loop
        nop

        
!printable chracters(enter char: >0x20 and not queal to 0x7F)         
if6:          
then6:  inc %r24
        ba if7       
        nop

        
!numbers if7 : 0-7 oct&decimal&hex
!        if8 : 8-9 decimal&hex
if7:    cmp %r25,0x30
        blt loop
        nop
        cmp %r25,0x37
        bgt if8
        nop
then7:  inc %r19
        inc %r20
        inc %r21
        ba loop
        nop

if8:    cmp %r25,0x39
        bgt if9
        nop
then8:  inc %r20
        inc %r21
        ba loop
        nop

        
!letters if9 : A-F: letters & hex
!        if10: G-Z: letters
!        if11: a-f: letters & hex
!        if12: g-z: letters

if9:    cmp %r25,0x41
        blt loop
        nop
        cmp %r25,0x46
        bgt if10
        nop
then9:  inc %r21
        inc %r22
        ba loop
        nop       

if10:   cmp %r25,0x5A
        bgt if11
        nop
then10: inc %r22
        ba loop
        nop

if11:   cmp %r25,0x61
        blt loop
        nop
        cmp %r25,0x66
        bgt if12
        nop
then11: inc %r21
        inc %r22
        ba loop
        nop

if12:   cmp %r25,0x7A
        bgt loop
        nop
then12: inc %r22
        ba loop
        nop
!end letters
       
        ba loop
        nop
        
        
end:
       
    
        
        set fmt1, %r8 !
        mov %r17, %r9 !
	call printf !
	nop

	set fmt2, %r8 !
        mov %r18, %r9 !
        call printf !
        nop 

	set fmt3, %r8 !
        mov %r19, %r9 !
	call printf !
	nop

	set fmt4, %r8 !
        mov %r20, %r9 !
	call printf !
	nop
	
	set fmt5, %r8 !
        mov %r21, %r9 !
	call printf !
	nop

	set fmt6, %r8 !
        mov %r22, %r9 !
	call printf !
	nop

	set fmt7, %r8 !
        mov %r23, %r9 !
	call printf !
	nop

	set fmt8, %r8 !
        mov %r24, %r9 !
	call printf !
	nop

	set fmt9, %r8 !
        mov %r16, %r9 !
	call printf !
	nop
        
	ret
        restore



fmt:    .asciz  "\nEnter a line of text(control+D to end): \n\n"
fmt1:   .asciz  "\nThe line containeds %d new line characters"
fmt2:   .asciz  "\nThe line containeds %d white spaces"
fmt3:   .asciz  "\nThe line containeds %d octal digits"
fmt4:   .asciz  "\nThe line containeds %d decimal digits"
fmt5:   .asciz  "\nThe line containeds %d hexdecima digits"
fmt6:   .asciz  "\nThe line containeds %d letterrs"
fmt7:   .asciz  "\nThe line containeds %d control characters"
fmt8:   .asciz  "\nThe line containeds %d printable characters"
fmt9:   .asciz  "\nThe line containeds %d characters\n"



