.text

## unsigned int
## circular_shift(unsigned int in, unsigned char s) {
##     return (in >> 8 * s) | (in << (32 - 8 * s));
## }

.globl circular_shift
circular_shift:
	# Your code goes here :)
	mul $t0, $a1, 8
	srl $t1, $a0, $t0
	li  $t2, 32
	sub $t2, $t2, $t0
	sll $t3, $a0, $t2
	or $v0, $t1, $t3
	jr	$ra
