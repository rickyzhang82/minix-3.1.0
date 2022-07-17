.sect .text; .sect .rom; .sect .data; .sect .bss
.sect .text
.symd "alloca.c", 0x64,0
.symb "int:t1=r1;-2147483648;2147483647;", 0, 0x80, 4
.symb "char:t2=r2;-128;127;", 0, 0x80, 1
.symb "long:t3=r3;-2147483648;2147483647;", 0, 0x80, 4
.symb "short:t4=r4;-32768;32767;", 0, 0x80, 2
.symb "unsigned char:t5=r5;0;255;", 0, 0x80, 1
.symb "unsigned short:t6=r6;0;65535;", 0, 0x80, 2
.symb "unsigned long:t7=r7;0;-1;", 0, 0x80, 4
.symb "unsigned int:t8=r8;0;-1;", 0, 0x80, 4
.symb "float:t9=r9;4;0;", 0, 0x80, 4
.symb "double:t10=r10;8;0;", 0, 0x80, 8
.symb "long double:t11=r11;8;0;", 0, 0x80, 8
.symb "void:t12=12;", 0, 0x80, 0
.symb "pointer:t13=*12;", 0, 0x80, 4
__II0:
push ebp
mov ebp,esp
sub	esp,4
.sect .data
__II1:
.symb "find_stack_direction:f12;", __II0, 0x24, 1
.symb "addr:V14=*2;", __II1, 0x28, 0
.symb "dummy:2;", -1, 0x80, 0
.data4	0
.sect .text
.symd "", 0xc0,2
.symd "", 0x44,129
cmp (__II1),0
jne I1_1
.symd "", 0x44,131
lea edx,-1(ebp)
mov (__II1),edx
.symd "", 0x44,133
call __II0
jmp I1_2
I1_1:
.symd "", 0x44,138
lea edx,-1(ebp)
cmp (__II1),edx
jae I1_3
.symd "", 0x44,139
mov (__II2),1
jmp I1_2
I1_3:
.symd "", 0x44,141
mov (__II2),-1
I1_2:
.symd "", 0xe0,2
leave
ret
.symb "hdr:T15=u8align:16=ar1;0;7;2,0,64;h:17=s8next:18=*15,0,32;deep:14,32,32;;,0,64;;;", 0, 0x80, 8
.symb "header:t15;", 0, 0x80, 8
.sect .data
__II3:
.symb "last_alloca_header:S18;", __II3, 0x28, 0
.extern _alloca
.data4	0
.sect .text
_alloca:
push ebp
mov ebp,esp
sub	esp,16
.symb "alloca:F13;", _alloca, 0x24, 1
.symb "size:p8;", 8, 0xa0, 0
.symb "probe:2;", -1, 0x80, 0
.symd "", 0x44,182
.symb "depth:14;", -8, 0x80, 0
lea edx,-1(ebp)
mov -8(ebp),edx
.symd "", 0xc0,2
.symd "", 0x44,185
cmp (__II2),0
jne I2_1
.symd "", 0x44,186
call __II0
I2_1:
.symb "hp:18;", -12, 0x80, 0
.symd "", 0xc0,3
.symd "", 0x44,199
mov edx,(__II3)
mov -12(ebp),edx
I2_2:
cmp -12(ebp),0
je I2_3
.symd "", 0x44,201
! kill cc
cmp (__II2),0
jle I2_4
mov edx,-12(ebp)
mov ecx,-8(ebp)
cmp 4(edx),ecx
ja I2_5
I2_4:
cmp (__II2),0
jns I2_6
mov edx,-12(ebp)
mov ecx,-8(ebp)
cmp 4(edx),ecx
jae I2_6
I2_5:
.symd "", 0x44,203
.symb "np:18;", -16, 0x80, 0
mov eax,-12(ebp)
mov edx,(eax)
mov -16(ebp),edx
.symd "", 0xc0,4
.symd "", 0x44,205
push -12(ebp)
call _free
pop ecx
.symd "", 0x44,207
mov edx,-16(ebp)
mov -12(ebp),edx
.symd "", 0xe0,4
jmp I2_2
I2_6:
.symd "", 0x44,210
I2_3:
.symd "", 0x44,212
mov edx,-12(ebp)
mov (__II3),edx
.symd "", 0xe0,3
.symd "", 0x44,219
cmp 8(ebp),0
jne I2_7
.symd "", 0x44,220
xor eax,eax
jmp I2_8
I2_7:
.symd "", 0x44,225
.symb "new:13;", -12, 0x80, 0
mov edx,8
add edx,8(ebp)
push edx
call _malloc
pop ecx
mov -12(ebp),eax
.symd "", 0xc0,3
.symd "", 0x44,228
cmp -12(ebp),0
jne I2_9
.symd "", 0x44,229
call _abort
I2_9:
.symd "", 0x44,231
mov edx,(__II3)
mov eax,-12(ebp)
mov (eax),edx
! kill eax
.symd "", 0x44,232
mov edx,-12(ebp)
mov ecx,-8(ebp)
mov 4(edx),ecx
.symd "", 0x44,234
mov edx,-12(ebp)
mov (__II3),edx
.symd "", 0x44,238
mov edx,-12(ebp)
! kill edx
lea eax,8(edx)
jmp I2_8
.symd "", 0xe0,3
.symd "", 0xe0,2
I2_8:
leave
ret
.symb "stack_dir:S1;", __II2, 0x28, 0
.sect .bss
.comm __II2,4
.sect .text
