.extern begtext
.define _start_of_text
.extern crtso
.sect .text

_start_of_text:
	mov eax, crtso
	ret

