org 0000h
mov r0,#30h
mov r1,#40h
mov r3,#10h
loop:
mov a,@r0
mov @r1,a
inc r0
inc r1
djnz r3,loop
end
