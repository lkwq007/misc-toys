org 0000h
mov r0,#30h
mov dptr,#1030h
mov r1,#10h
loop:
mov a,@r0
movx @dptr,a
inc a
inc dptr
djnz r1,loop
end
