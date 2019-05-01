.text

## void
## key_addition(unsigned char *in_one, unsigned char *in_two, unsigned char *out) {
##     for (unsigned int i = 0; i < 16; i++) {
##         out[i] = in_one[i] ^ in_two[i];
##     }
## }

.globl key_addition
key_addition:
	# Your code goes here :)
	li $t0, 0
loop:
	bge $t0, 16, end
	lb $t1, 0($a0)
	lb $t2, 0($a1)
	xor $t3, $t1, $t2
	sb  $t3, 0($a2)
	add $a2,$a2,1
	add $a1,$a1,1
	add $a0,$a0,1
	add $t0,$t0,1
	j loop
end:
	jr	$ra
