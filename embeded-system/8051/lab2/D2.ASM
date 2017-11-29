result equ 30h
org 0000h
mov a,#0d8h
mov b,#100
div ab
mov result,a
mov a,b
mov b,#10
div ab
mov result+1,a
mov result+2,b
sjmp $
end
