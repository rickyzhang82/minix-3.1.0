#

; $Id: lib.e,v 1.1 2005/09/01 12:13:28 beng Exp $

 mes 2, _EM_WSIZE, _EM_PSIZE

 exp $__Get_LB
 pro $__Get_LB,0
 lor 0
1
 lol 0
 zlt *2
 dup _EM_PSIZE
 zer _EM_PSIZE
 cmp
 zeq *2
 dch
 del 0
 bra *1
2
 ret _EM_PSIZE
 end

 exp $__Get_Hol0
 pro $__Get_Hol0,0
 lae 0
 ret _EM_PSIZE
 end

 exp $__Get_HP
 pro $__Get_HP,0
 lor 2
 ret _EM_PSIZE
 end

 exp $__Set_HP
 pro $__Set_HP,0
 lal 0
 loi _EM_PSIZE
 str 2
 ret 0
 end

 exp $__Cvt_LB_AB
 pro $__Cvt_LB_AB,0
 lal 0
 loi _EM_PSIZE
 zer _EM_PSIZE
 cmp
 zeq *2
 lal 0
 loi _EM_PSIZE
 lpb
 ret _EM_PSIZE
2
 zer _EM_PSIZE
 ret _EM_PSIZE
 end
