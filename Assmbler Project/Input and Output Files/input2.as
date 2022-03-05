; THIS IS THE SECOND INPUT FILE
.entry LABLE1
.extern testLab
abcd: add r3, LABLE1
inc r6
mov r3, K
sub r1, r4
bne Avii
cmp K, #-10
bne &Avii
.entry abcd
STR: .string "sting to test input"
add testLab, testLab
Avii: stop
LABLE1: .data 6, -9
.data -100
K: .data 3341

