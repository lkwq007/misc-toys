org 0000h
mov r0,#30h
mov dptr,#103fh
mov r1,#10h
loop:
mov a,@r0
movx @dptr,a
inc r0
dec dptr
djnz r1,loop
end
