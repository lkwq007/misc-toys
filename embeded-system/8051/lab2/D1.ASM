asciia equ 61h
org 0000h
mov r0,#30h
loop:
mov a,@r0
jz rear
cjne a,#asciia,next
next:
jnc update
add a,#32
mov @r0,a
update:
inc r0
sjmp loop
rear:
sjmp $
end
