#
 mes 2,EM_WSIZE,EM_PSIZE
; $Id: setline.e,v 1.1 2005/09/01 12:13:18 beng Exp $
; Save the line where the error occurred
 exp $_setline
 pro $_setline,0
 exa _erlsym
 loe 0
 ste _erlsym
 ret 0
 end
