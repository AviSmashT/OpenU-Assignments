; THIS IS THE ERRORS INPUT FILE
.entry LABLE1
.extern testLab
abcd: add r3, LABLE1
rts
inc r6, r3
mov r3,, K
sub r1, r4
bne Avii
cmp K, #-10
bne #Avii
.entry abcd
STR: .string "sting to test input
add testLab, testLab
Avii: stop
; lets see the error if 'LABLE1: .data 6, -9' is missing
.data ,-100
K: .data 3341,

