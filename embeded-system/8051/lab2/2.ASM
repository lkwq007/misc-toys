result equ 30h
org 0000h
mov a,#23h
mov r0,a
anl a,#0f0h
swap a
mov b,#0ah
mul ab
mov result,a
mov a,r0
anl a,#0fh
add a,result
mov result,a
sjmp $
end
