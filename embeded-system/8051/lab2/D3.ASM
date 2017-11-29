ZERO equ '0'
CA equ 'A'
result equ 40h
org 0000h
mov 30h,#61h
mov 31h,#4eh
mov 32h,#00h
mov r0,#30h
mov r1,#result
loop:
mov a,@r0
jz over
mov r2,a
mov r3,#02h
hlbits:
mov a,r2
swap a
mov r2,a
anl a,#0Fh
cjne a,#10,next
next:
jnc alpha
add a,#ZERO
sjmp update
alpha:
clr c
subb a,#10
add a,#CA
update:
mov @r1,a
inc r1
djnz r3,hlbits
inc r0
jmp loop 
over:
sjmp $
end
