.text

## unsigned int
## my_strlen(char *in) {
##     if (!in)
##         return 0;
## 
##     unsigned int count = 0;
##     while (*in) {
##         count++;
##         in++;
##     }
## 
##     return count;
## }

.globl my_strlen
my_strlen:
	# Your code goes here :)
#my_strlen_if: 
	bne $a0, 0, my_strlen_if_skip   #skip if 
	li  $v0, 0
	jr $ra	
my_strlen_if_skip:
	li $t0, 0

my_strlen_while:
	lb $t1, 0($a0)
	beq $t1, 0, my_strlen_done
	add $t0, $t0, 1
	add $a0, $a0, 1
	j my_strlen_while
my_strlen_done:
	move $v0, $t0	
	jr	$ra
