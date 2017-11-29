org 0000h
mov r0,#30h
mov r1,#50h
mov r2,#20h
l1:
mov a,@r0
mov @r1,a
inc r0
inc r1
djnz r1,l1
end
