# before running your code for the first time, run:
#     module load QtSpim
# run with:
#     QtSpim -file main.s question_4.s

# int bit_expand(int *out, int num) {
#     int net = 0;
# 
#     for (int i = 31; i >= 0; i--) {
#         int temp = num & 1;
#         num = num >> 1;
# 
#         out[i] = temp;
#         if (temp == 0) {
#             net--;
#         } else {
#             net++;
#         }
#     }
# 
#     return net;
# }
.globl bit_expand
bit_expand:
	li $t0, 0	#net
	li $t1, 31	#i
for:
	blt $t1, 0, end_for
	and $t2, $a1, 1  #temp
	srl $a1, $a1, 1
	mul $t5, $t1, 4
	add $t3, $a0, $t5
	sw $t2, 0($t3)
if:
	bne $t2, 0, else
	sub $t0, $t0, 1 
	sub $t1, $t1, 1
	j for
else:
	add $t0, $t0,1
	sub $t1, $t1, 1
	j for
end_for:
	move $v0, $t0
	jr $ra
