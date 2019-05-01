.text

## void
## max_unique_n_substr(char *in_str, char *out_str, int n) {
##     if (!in_str || !out_str || !n)
##         return;
## 
##     char *max_marker = in_str;
##     unsigned int len_max = 0;
##     unsigned int len_in_str = my_strlen(in_str);
##     for (unsigned int cur_pos = 0; cur_pos < len_in_str; cur_pos++) {
##         char *i = in_str + cur_pos;
##         int len_cur = nth_uniq_char(i, n + 1);
##         if (len_cur > len_max) {
##             len_max = len_cur;
##             max_marker = i;
##         }
##     }
## 
##     my_strncpy(out_str, max_marker, len_max);
## }

.globl max_unique_n_substr
max_unique_n_substr:
	# Your code goes here :)
if:
	bne $a0, 0, condition1 
	jr	$ra
condition1:
	bne $a1, 0, condition2
	jr	$ra
condition2:
	bne $a2, 0, end_if
	jr	$ra
end_if:
	sub  $sp, $sp, 36
	sw   $ra, 0($sp)
	sw   $s0, 4($sp)
	sw   $s1, 8($sp)
	sw   $s2, 12($sp)
	sw   $s3, 16($sp)
	sw   $s4, 20($sp)
	sw   $s5, 24($sp)
	sw   $s6, 28($sp)
	sw   $s7, 32($sp)


	move $s0, $a0
	move $s7, $a0
	move $s1, $a1
	move $s2, $a2
	li $s3, 0
	jal my_strlen

	move $s4, $v0

	li $s5, 0 
for:
	bge $s5, $s4, end_for

	add $s7, $s7, $s5
	move $s6, $s7
	sub $s7, $s7, $s5

	add $s2, $s2, 1	
	move $a0, $s6
	move $a1, $s2
	sub $s2, $s2, 1
	jal nth_uniq_char

	ble $v0, $s3, end_if_1
	move $s3, $v0
	move $s0, $s6
end_if_1: 
	add $s5,$s5,1
	j for
end_for:

	move $a0, $s1
	move $a1, $s0
	move $a2, $s3
	jal my_strncpy
	lw   $ra, 0($sp)
	lw   $s0, 4($sp)
	lw   $s1, 8($sp)
	lw   $s2, 12($sp)
	lw   $s3, 16($sp)
	lw   $s4, 20($sp)
	lw   $s5, 24($sp)
	lw   $s6, 28($sp)
	lw   $s7, 32($sp)
	add  $sp,$sp,36
	jr $ra



