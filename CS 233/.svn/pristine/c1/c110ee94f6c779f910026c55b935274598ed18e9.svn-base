## struct Shifter {
##     unsigned int value;
##     unsigned int *to_rotate[4];
## };
## 
## 
## void
## shift_many(Shifter *s, int offset) {
##     for (int i = 0; i < 4; i++) {
##         unsigned int *ptr = s->to_rotate[i];
## 
##         if (ptr == NULL) {
##             continue;
##         }
## 
##         unsigned char x = (i + offset) & 3;
##         *ptr = circular_shift(s->value, x);
##     }
## }
.globl shift_many
shift_many:
	# Your code goes here :)
	sub $sp, $sp ,28
	sw   $ra, 0($sp)
	sw   $s0, 4($sp)
	sw   $s1, 8($sp)
	sw   $s6, 12($sp)
	sw   $s3, 16($sp)
	sw   $s4, 20($sp)
	sw   $s7, 24($sp)
	
	move	$s1, $a0
	move	$s0, $a1

	add	$s3, $s1, 4
	li	$s6, 0

for_loop:
	bge	$s6, 4 , done
	sll	$t0, $s6, 2
	add	$s4, $s3, $t0
	lw	$s7, 0($s4)
	beq	$s7, 0, end_for
	
	add	$t1, $s0, $s6
	add	$a1, $t1, 3
	lw	$a0, 0($s1) 
	jal	circular_shift
	sw	$v0, 0($s7)

end_for:
	add	$s6, $s6, 1
	j	for_loop
done:
	move	$a0, $s1
	move	$a1, $s0
	
	lw  	$ra, 0($sp)
	lw  	$s0, 4($sp)
	lw  	$s1, 8($sp)
	lw  	$s6, 12($sp)
	lw  	$s3, 16($sp)
	lw  	$s4, 20($sp)
	lw  	$s7, 24($sp)
	add	$sp, $sp ,28
		
	jr 	$ra
