#
;
; (c) copyright 1988 by the Vrije Universiteit, Amsterdam, The Netherlands.
; See the copyright notice in the ACK home directory, in the file "Copyright".
;

;
; Module:	coroutine primitives
; Author:	Kees Bot, Edwin Scheffer, Ceriel Jacobs
; Version:	$Id: par_misc.e,v 1.1 2005/09/01 12:13:28 beng Exp $
;
; This has been taken from the ACK Modula-2 runtime system and adapted.
;

 mes 2,_EM_WSIZE,_EM_PSIZE

;
; ___topsave: save the stack by sending it to the debugger
;
 exp $___topsave

 pro $___topsave, 0
#ifdef __sparc
 inp $___topsave1
 inp $___topsave2
 cal $___topsave1
 lfr _EM_WSIZE
 ret _EM_WSIZE
 end 0

 pro $___topsave1,0
 cal $___topsave2
 lfr _EM_WSIZE
 ret _EM_WSIZE
 end 0

 pro $___topsave2,0
#endif
 mes 11
 loe 0
 lae 4			; load line number and file name
 loi _EM_PSIZE
 lim			; load ignore mask
 lor 0			; load LB

; now find the last argument base: first find the local base that has
; dynamic link 0.

 lor 0
1
 dup _EM_PSIZE
 dch
 zer _EM_PSIZE
 cmp
 zeq *2
 dch
 bra *1
2
 lpb			; last argument base

; Now the stuff between the current stack pointer and this argument base
; is saved by sending it to the debugger.

 lor 1
 sbs _EM_WSIZE
 loc _EM_WSIZE
 adu _EM_WSIZE		; gives size
 lor 1			; SP (the SP BEFORE pushing)
 lor 1			; SP (address of stack top to save)
 cal $___sendtop	; ___sendtop(char *address, char *SP, unsigned size)
 asp 4*_EM_PSIZE+3*_EM_WSIZE	; remove the lot from the stack
 loc 1
 ret _EM_WSIZE			; return 1
 end 0

 exp $___topload
 pro $___topload, 0
#ifdef __sparc
 inp $___topload1
 inp $___topload2
 cal $___topload1
 lfr _EM_WSIZE
 ret _EM_WSIZE
 end 0

 pro $___topload1,0
 lxl 0
 dch
 lpb
 loi _EM_PSIZE
 cal $___topload2
 asp _EM_PSIZE
 lfr _EM_WSIZE
 ret _EM_WSIZE
 end 0

 pro $___topload2,0
#endif
 mes 11

 lal 0
 loi _EM_PSIZE

 lxl 0
2
 dup _EM_PSIZE
 adp -3*_EM_PSIZE
 lal 0
 loi _EM_PSIZE		; compare target SP with current LB to see if we must
 cmp			; find another LB first
 zgt *1
 dch			; just follow dynamic chain to make sure we find
			; a legal one
 bra *2
1
 str 0

 str 1			; restore SP
 lor 1
 adp -_EM_PSIZE
#ifdef __sparc
 inp $restore
 cal $restore
#else
 cal $___restoretop	; ___restoretop(char *SP)
#endif
 asp _EM_PSIZE+_EM_WSIZE
 str 0			; restore local base
 sim			; ignore mask
 lae 4
 sti _EM_PSIZE
 ste 0			; line and file
 loc 0
 ret _EM_WSIZE		; return 0
 end 0

#ifdef __sparc
 pro $restore
 mes 11
 lal 0
 loi _EM_PSIZE
 cal $___restoretop
 asp _EM_PSIZE
 ret 0
 end 0
#endif
