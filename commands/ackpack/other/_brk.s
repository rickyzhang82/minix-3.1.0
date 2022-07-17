! Both OSF/1 and SYSVR4 man pages specify that brk(2) returns int.
! However, BSD4.3 specifies that brk() returns char*.  POSIX omits
! brk() on the grounds that it imposes a memory model on an architecture.
! For this reason, brk() and sbrk() are not in the lib/posix directory.
! On the other hand, they are so crucial to correct operation of so many
! parts of the system, that we have chosen to hide the name brk using _brk,
! as with system calls.  In this way, if a user inadvertently defines a
! procedure brk, MINIX may continue to work because the true call is _brk.

.sect .text; .sect .rom; .sect .data; .sect .bss
.extern .reghp, ___brk, _errno
.define _brk, __brk
.define _sbrk, __sbrk
ENOMEM = 12
.sect .text
_brk:
__brk:
	push	ebp
	mov	ebp,esp
	mov	eax,8(ebp)
	push	eax
	call	___brk
	or	eax,eax
	jz	1f
	mov	(_errno),ENOMEM
1:	pop	ebp		! Clean stack
	pop	ebp
	ret

_sbrk:
__sbrk:
	push	ebp
	mov	ebp,esp
	mov	eax,(.reghp)
	add	eax,8(ebp)
	push	eax
	call	__brk
	or	eax,eax
	pop	eax		! Clean stack
	pop	ebp
	jnz	1f
	mov	eax,(.reghp)
	ret
1:
	mov	eax,-1
	ret

