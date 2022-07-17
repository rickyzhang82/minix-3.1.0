#
! EM runtime environment must have access to the system heap, and hence,
! it is necessary to have close interaction with the Minix memory manager
! and to intercept all calls to the BRK system call. At this low-level,
! the normal support for system calls is not available (it is a part of
! the standard C library), and each system call must be implemented
! directly. Note also that on failure errno is NOT set -- that is the
! responsibility of the C library. Luckily, there is just a single error
! code, ENOMEM, set on failure.
!
! __brk() saves ebx, but destroys eax, ecx [just like _sendrec()].
! This property is used in the implementation of strhp (c.f em_strhp.s).
! Note that the C calling convention (caller cleans stack) is assumed
! in this code; whereas em_strhp.s uses the EM calling convention.

.sect .text; .sect .rom; .sect .data; .sect .bss
.extern endbss
.define ___brk, .reghp, __brksize
.sect .data
__brksize:
.reghp:	.data4 endbss
.sect .text
___brk:
	push	ebx

	! See /usr/include/minix/type.h for the definition of the
	! message structure. It occupies 36 bytes.
	sub	esp,MSG_SIZE

	! Stack now consists of:
	!	44(esp)		_brk() argument (address)
	!	40(esp)		<return address>
	!	36(esp)		saved-ebx
	!	28(esp)		\ new break address returned (reply_ptr)
	!	24(esp)		|
	!	20(esp)		| _brk() argument copy
	!	16(esp)		|
	!	12(esp)		|
	!	8(esp)		|
	!	4(esp)		| BRK==17 system call identifier
	!	(esp)		/

	mov	eax,MSG_SIZE+8(esp)
	mov	20(esp),eax
	mov	4(esp),17
	xor	eax,eax		! MM==0 is destination
	mov	ebx,esp		! message constructed on stack
	mov	ecx,3		! Send/receive
	int	33
	mov	eax,28(esp)	! Save new break address
	mov	ecx,eax
	inc	ecx		! == -1?
	jz	1f
	mov	(.reghp),eax
	xor	eax,eax		! Return 0 on success
1:
	add	esp,MSG_SIZE
	pop	ebx
	ret

