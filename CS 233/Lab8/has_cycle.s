.data

.text
## struct Node {
##     int node_id;            // Unique node ID
##     struct Node **children; // pointer to null terminated array of children node pointers
## };
##
## int
## has_cycle(Node *root, int num_nodes) {
##     if (!root)
##         return 0;
## 
##     Node *stack[num_nodes];
##     stack[0] = root;
##     int stack_size = 1;
## 
##     int discovered[num_nodes];
##     for (int i = 0; i < num_nodes; i++) {
##         discovered[i] = 0;
##     }
## 
##     while (stack_size > 0) {
##         Node *node_ptr = stack[--stack_size];
## 
##         if (discovered[node_ptr->node_id]) {
##             return 1;
##         }
##         discovered[node_ptr->node_id] = 1;
## 
##         for (Node **edge_ptr = node_ptr->children; *edge_ptr; edge_ptr++) {
##             stack[stack_size++] = *edge_ptr;
##         }
##     }
## 
##     return 0;
## }

.globl has_cycle
has_cycle:
	# Your code goes here :)
	bne $a0, 0, end_if
	li $v0, 0
	jr $ra		#if(!root)

end_if:

	mul	$t3, $a1, 4 

	sub	$sp, $sp, $t3
	move	$t0, $sp	# stack
	
	sub	$sp, $sp, $t3
	move	$t2, $sp	# discovered
	
	sw	$a0, 0($t0)	# stack[0] = root
	li 	$t1, 1		# stack_size
	li	$t3, 0		# i 

for_loop:

	bge 	$t3, $a1, while		# i>= num_nodes
	mul	$t4, $t3, 4		# i * 4
	add 	$t4, $t2, $t4		# discovered[i]
	sw	$0, 0($t4)		# discovered[i] = 0


	add 	$t3, $t3, 1		# i++
	j 	for_loop

while:

	ble 	$t1, 0, done	# stack_size <= 0
	sub	$t1, $t1, 1		# stack_size - 1
	mul	$t3, $t1, 4
	add	$t3, $t0, $t3		#stack[stack_size] 
	lw	$t3, 0($t3)        	# node_ptr t4


	lw	$t4, 0($t3)	   	# node_ptr->id
	mul	$t5, $t4, 4
	add	$t5, $t2, $t5
	lw	$t6, 0($t5)	   	# discovered[node_ptr->node_id]
#	sub	$t2, $t2, $t5

	beq	$t6, 1, end_while_1	# discovered[node_ptr->node_id] = 1

	li	$t9, 1
	sw	$t9, 0($t5)	   # discovered[node_ptr->node_id] = 1

		
	lw	$t6, 4($t3)	  # edge_ptr (node_ptr->child) t8
	li	$t7, 0

for_2:
	mul	$t8, $t7, 4
	add	$t8, $t6, $t8
	lw	$t8, 0($t8)		# t9 edge_ptr 
	beq	$t8, 0, while		# edge_ptr == 0
	mul	$t9, $t1, 4		# stack_size * 4
	add	$t9, $t0, $t9
	sw	$t8, 0($t9)
	add	$t1, $t1, 1		#stack++
	add	$t7, $t7, 1		#edge_ptr++
	j	for_2	

end_while_1:
	mul 	$t5, $a1, 8
	add	$sp, $sp, $t5
	li	$v0, 1	
	jr	$ra
done:
	mul 	$t5, $a1, 8
	add	$sp, $sp, $t5
	li	$v0, 0
	jr	$ra