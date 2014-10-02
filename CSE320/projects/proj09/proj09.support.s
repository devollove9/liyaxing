/****************************************************************************
  Yaxing Li
  CSE 320
  Project #9
****************************************************************************/
        .global	search
	.section ".text"
	.align 4
search:
	save	%sp, -96, %sp
 
	lduh	[%i0], %l0		! Load table capacity 
	lduh	[%i0+2], %l1		! Load table count 
	ld	[%i0+4], %l4		! Load pointer to array of players
        
	mov	%r0, %l7
	mov     %r0, %l2
        
loop0:
	cmp	%l1, %l7		! Compare table count to loop count
	bl	endloop0		
	nop
 
	lduh	[%l4], %l6		! Load player number
if0:
	cmp	%i1, %l6		! Compare input player # with current player #
	be	endif0			
	nop

        cmp     %i1, %l6
        blt     insertion
        nop
        
	add	%l4, 36, %l4		
	inc	%l7			! Increment loop count
        inc     %l2
	ba	loop0			
	nop
 
endif0:
	mov	%r0, %i0
	mov	1, %i0			! Set register to one for success return (found)
!        call    iu_window
	st	%l4, [%i2]		! Store pointer to player
	ba	else0
	nop
insertion:
        add     %l4, 36, %l4
        inc     %l2
        nop
        
endloop0:
	mov	%r0, %i0		! Clear register to zero for fail return (not found)
	mov	%l2, %i4	        ! put iterator in i4
	mov	%l5, %i5	        ! put array location in i5
        
 
else0:
        
	ret
	restore

/****************************************************************************/        
        .global  delete
	.section ".text"
	.align   4
delete: 
	save	%sp, -96, %sp
 
	lduh	[%i0], %l0		! Load table capacity 
	lduh	[%i0+2], %l1		! Load table count 
	ld	[%i0+4], %l2		! Load pointer to array of players
        
 	mov	%i0, %o0		! Copy table to output register for search call
	mov	%i1, %o1		! Copy player # to output register for search call
        mov     %i4, %o2
        
	call	search
	nop
	mov	%o0, %l7		! Copy searched table to local register for manipulation
	mov	%o2, %l6		! Copy searched player # to local register for search call
 
	cmp	%l7, %r0		! Check if search returns zero
	be 	notfound		
	nop
        
	ld	[%l6], %o0		! Load player to output %o0 for memmove
	add	%o0, 36, %o1		
	sub	%l1,1, %l1		! Decrement table count
        
	umul	%l1, 36, %o2
	
	call	memmove
	nop
 
	sth	%l1, [%i0+2]
 
	mov	%r0, %i0		
	mov	1, %i0
!	call    iu_window
!       nop
	ba	else1
	nop
 
notfound:
	mov	%r0, %i0		
 
else1:
	ret
	restore



	
/****************************************************************************/
        .global	insert
	.section ".text"
	.align 4
insert:

	save	%sp, -112, %sp
	lduh    [%i0],%l0		! Load table capacity 
	lduh    [%i0+2],%l1		! Load table count 
	cmp	%l1, %l0	!compare count to capacity
	bge	noinsert	
	nop
        ld      [%i0+4],%l2		! Load pointer to array of players
        
	mov	%i1, %l0	!put desired number in l0	
	mov	%i0, %o0	
	mov	%l0, %o1	
	mov	%i6, %o2	
	call	search		!search
	nop
    
	mov	%o0, %l7		! Copy searched table to local register for manipulation
	ld	[%o2], %l6		! Copy searched player # to local register for search call  
	cmp	%l7, %g0		
	bne 	noinsert		
	nop
        call    iu_window
        nop
        sub     %o4,1,%l3
        umul    %l3,36,%l3
        add     %l2,%l3,%l6             ! Corret the address to store insert
        
        mov     %l6,%o1                 ! move a place for insert
        add     %o1,36,%o0

        cmp     %o4,%l1                 ! Inserted Jersey number greater than all existing jersey number 
        bgt      empty                  ! Jump to the direct insert
        nop                             ! else dont jump
  
        sub     %l1,%o4,%l3             ! Get correct address and move the data behind target location to next 36 bits
        add     %l3,1,%l3
        umul    %l3,36,%l3
        mov     %l3,%o2
        call    memmove
        nop
empty:  
        sth     %i1,[%l6]               !store jersey number
        add     %l6,2,%l7               !store chars
        mov     %l7,%o0
        mov     %i2,%o1
        mov     20,%o2
        call    memmove
        nop
        sth     %i3,[%l6+22]            !store game numbers
        cmp     %i3,%g0                 !see if the game number = 0
        be      game0

        sth     %i4,[%l6+24]            !goals 

        sth     %i5,[%l6+26]            !assists

        add     %i4,%i5,%l4             !points
        sth     %l4,[%l6+28]

        st      %l4,[%sp]               !points to float
        ld      [%sp],%f4
        fitos   %f4,%f4

        st      %i3,[%sp]               !games to float
        ld      [%sp],%f5
        fitos   %f5,%f5

        fdivs   %f4,%f5,%f6             !points/games
        st      %f6,[%l6+32]            !store points/per game
        call    iu_window
        ba      good
        
game0:
        sth     %g0,[%l6+24]            !goals
        sth     %g0,[%l6+26]            !assists
        sth     %g0,[%l6+28]            !points
        st	%g0, [%sp]	        !push 0 out to ram
	ld	[%sp], %f7	        !pull from ram to f4
	fitos	%f7, %f9	        !float int to double
	st	%f9, [%l6+32]	        !store player/points_per_game
good:	
	inc	%l1		!increment count
	stuh	%l1, [%i0+2]	!store new count in table	
	mov	1, %i0		!move 1 to return true
	ba	iend		!always goto iend
	nop
noinsert:
	mov	0, %i0		!put 0 to return false
	ba	iend		!always goto iend
	nop                     !*/
iend:
	ret
	restore
