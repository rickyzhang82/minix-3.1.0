.sect .text; .sect .rom; .sect .data; .sect .bss
.sect .text
.define	.strhp
.extern ___brk, EHEAP, .trp

	! STR 2 ; store HP register

! EM calling convention - called routine cleans stack
.strhp:
	pop	ebx		! Return address

	! Value to store as brk at top of stack
	! Note that ___brk uses C calling convention
	call	___brk
	add	esp,2
	or	eax,eax
	jnz	1f
	jmp	ebx

1:	! On failure, raise an EM trap
	mov	eax,EHEAP
	push	ebx
	jmp	.trp

