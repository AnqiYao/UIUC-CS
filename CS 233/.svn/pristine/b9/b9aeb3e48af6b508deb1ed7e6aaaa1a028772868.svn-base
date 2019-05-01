.data
uniq_chars: .space 256

.text

## int
## nth_uniq_char(char *in_str, int n) {
##     if (!in_str || !n)
##         return -1;
## 
##     uniq_chars[0] = *in_str;
##     int uniq_so_far = 1;
##     int position = 0;
##     in_str++;
##     while (uniq_so_far < n && *in_str) {
##         char is_uniq = 1;
##         for (int j = 0; j < uniq_so_far; j++) {
##             if (uniq_chars[j] == *in_str) {
##                 is_uniq = 0;
##                 break;
##             }
##         }
##         if (is_uniq) {
##             uniq_chars[uniq_so_far] = *in_str;
##             uniq_so_far++;
##         }
##         position++;
##         in_str++;
##     }
## 
##     if (uniq_so_far < n) {
##         position++;
##     }
##     return position;
## }

.globl nth_uniq_char
nth_uniq_char:
	# Your code goes here :)
##	la $t8, uniq_chars

if:
	bne $a0, 0, condition1
	li $v0, -1	
	jr 	$ra

condition1:
	bne $a1, 0, end_if
	li $v0, -1	
	jr 	$ra

end_if:
	la $t8, uniq_chars
	lb $t0, 0($a0)
	sb $t0, 0($t8)
	li $t1, 1
	li $t2, 0
	add $a0, $a0, 1	

while:
	bge $t1, $a1, end_while
	lb  $t3, 0($a0)
	beq $t3, 0, end_while
	li  $t5, 0

for_loop:
	bge $t5, $t1, end_for
	add $t8, $t8, $t5
	lb  $t6, 0($t8)
	sub $t8, $t8, $t5
	bne $t6, $t3, end_if_1
	j end_if_2	

end_if_1:
	add $t5, $t5, 1
	j for_loop	

end_if_2:
	add $t2, $t2, 1
	add $a0, $a0, 1	
	j while

end_while:
	bge $t1, $a1, ending
	add $t2, $t2, 1

ending:
	move $v0, $t2
	jr	$ra


end_for:
	add $t8, $t8, $t1
	sb $t3, 0($t8)
	sub $t8, $t8, $t1
	add $t1, $t1, 1
	j end_if_2


		
	
