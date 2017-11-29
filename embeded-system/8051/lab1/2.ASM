    org 0000h
    mov dptr,#3000h
    mov a,#01h
    mov r5,#0
loop:
    movx @dptr,a
    inc dptr
    djnz r5,loop
    mov r0,#30h
    mov r1,#00h
    mov r2,#40h
    mov r3,#00h
    mov r7,#0
loop1:
    mov dph,r0
    mov dpl,r1
    movx a,@dptr
    mov dph,r2
    mov dpl,r3
    movx @dptr,a
    inc r1
    inc r3
    djnz r7,loop1
    sjmp $
    end


