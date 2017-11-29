     ORG 0000H
     START EQU 8000H
MAIN:
     MOV DPTR,#START
     MOV R0,#0
     MOV A,#1H
LOOP:
     MOVX @DPTR,A
     INC DPTR
     DJNZ R0,LOOP
     NOP
     SJMP $
     END
