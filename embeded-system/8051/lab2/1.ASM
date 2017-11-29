result equ 30h
org 0000h
mov a,#41h
clr c
subb a,#37h
mov result,a
sjmp $
end
