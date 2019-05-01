.data

.text

## struct Node {
##     int node_id;            // Unique node ID
##     struct Node **children; // pointer to null terminated array of children node pointers
## };
##
## int
## max_depth(Node *current) {
##     if (current == NULL)
##         return 0;
## 
##     int cur_child = 0;
##     Node *child = current->children[cur_child];
##     int max = 0;
##     while (child != NULL) {
##         int depth = max_depth(child);
##         if (depth > max)
##             max = depth;
##         cur_child++;
##         child = current->children[cur_child];
##     }
##     return 1 + max;
## }

.globl max_depth
max_depth:
	# Your code goes here :)
	bne	$a0, 0, end_if
	li	$v0, 0
	jr	$ra

end_if:	
	
	sub  $sp, $sp ,28
	sw   $ra, 0($sp)
	sw   $s0, 4($sp)
	sw   $s1, 8($sp)
	sw   $s2, 12($sp)
	sw   $s3, 16($sp)
	sw   $s4, 20($sp) 
	sw   $s5, 24($sp) 
		
	move	$s5, $a0
	li	$s0, 0		# s0 cur_child = 0 
	lw	$s1, 4($s5)	# s1 current->children
	mul	$t0, $s0, 4	# 4 * cur_child
	add	$s1, $s1, $t0	
	lw	$s2, 0($s1)	# child 
#	sub	$s1, $s1, $t0
	li	$s3, 0		# max = 0  $3 

while:

	beq	$s2, 0, done
	move	$a0, $s2
	jal	max_depth
	move	$s4, $v0	# depth s4

if:
	ble	$s4, $s3, end_if_1   # depth <= max  s4 <= s3
	move	$s3, $s4	# max = depth

end_if_1:
	
	add	$s0, $s0, 1	# cur_child ++

	mul	$t0, $s0, 4	
		
	lw	$t1, 4($s5)	# t1 current->children
	add	$t1, $t1, $t0	# current->children[cur_child]
	lw	$s2, 0($t1)
#	sub	$t1, $t1, $t0
	j	while

done:
	add	$v0, $s3, 1
	
	lw   $ra, 0($sp)
	lw   $s0, 4($sp)
	lw   $s1, 8($sp)
	lw   $s2, 12($sp)
	lw   $s3, 16($sp)
	lw   $s4, 20($sp)
	lw   $s5, 24($sp)
	add  $sp, $sp ,28
	jr	$ra	



	
