# before running your code for the first time, run:
#     module load QtSpim
# run with:
#     QtSpim -file main.s question_5.s

# struct node_t {
#     node_t *children[4];
#     int data;
# };
# 
# int quad_leaf_average(node_t *root) {
#     if (root == NULL) {
#         return 0;
#     }
# 
#     if (root->children[0] != NULL) {
#         int total = 0;
#         for (int i = 0; i < 4; i++) {
#             total += quad_leaf_average(root->children[i]);
#         }
#         return total >> 2;
#     }
# 
#     return root->data;
# }
.globl quad_leaf_average
quad_leaf_average:
	bne	$a0, 0, start
	li	$v0, 0
	jr	$ra
start:	
	lw	$t0, 0($a0)
	beq	$t0, 0, end_if

	sub	$sp, $sp, 16
	sw	$ra, 0($sp)
	sw	$s0, 4($sp)
	sw	$s1, 8($sp)
	sw	$s2, 12($sp)

	move	$s2, $a0

	li	$s0, 0
	li	$s1, 0
	
for:
	bge	$s1, 4, end_for
	mul	$t1, $s1, 4
	add	$t1, $t1, $s2
	lw	$a0, 0($t1)
	jal	quad_leaf_average
	add	$s0, $s0, $v0
	add	$s1, $s1, 1
	j 	for

end_for:
	srl	$v0, $s0, 2
	lw	$ra, 0($sp)
	lw	$s0, 4($sp)
	lw	$s1, 8($sp)
	lw	$s2, 12($sp)
	add	$sp, $sp, 16
	jr	$ra
end_if:
	lw	$v0, 16($a0)
	jr	$ra
