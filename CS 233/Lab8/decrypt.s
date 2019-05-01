
.data

.text

## void
## decrypt(unsigned char *ciphertext, unsigned char *plaintext, unsigned char *key,
##         unsigned char rounds) {
##     unsigned char A[16], B[16], C[16], D[16];
##     key_addition(ciphertext, &key[16 * rounds], C);
##     inv_shift_rows(C, (unsigned int *) B);
##     inv_byte_substitution(B, A);
##     for (unsigned int k = rounds - 1; k > 0; k--) {
##         key_addition(A, &key[16 * k], D);
##         inv_mix_column(D, C);
##         inv_shift_rows(C, (unsigned int *) B);
##         inv_byte_substitution(B, A);
##     }
##     key_addition(A, key, plaintext);
##     return;
## }

.globl decrypt
decrypt:
	# Your code goes here :)
	
	sub $sp, $sp, 16
	move $t0, $sp
	
	sub $sp, $sp, 16
	move $t1, $sp
	
	sub $sp, $sp, 16
	move $t2, $sp
	
	sub $sp, $sp, 16
	move $t3, $sp
	

	sub $sp, $sp ,36
	sw   $ra, 0($sp)
	sw   $s0, 4($sp)
	sw   $s1, 8($sp)
	sw   $s2, 12($sp)
	sb   $s3, 16($sp)
	sw   $s4, 20($sp) #a
	sw   $s5, 24($sp) #b
	sw   $s6, 28($sp) #c
	sw   $s7, 32($sp) #d


	move $s4 , $t0
	move $s5 , $t1
	move $s6 , $t2
	move $s7 , $t3
	
	move $s0, $a0	 #ciphertext
	move $s1, $a1    #plaintext
	move $s2, $a2	 #key
	move $s3, $a3	 #counts

	move $a0, $s0
	mul $t0, $s3, 16
	add $a1, $s2, $t0
	move $a2, $s6
	jal key_addition
	
	move $a0, $s6
	move $a1, $s5
	jal inv_shift_rows


	move $a0, $s5
	move $a1, $s4
	jal inv_byte_substitution
	
	subu $s3, $s3, 1
 	

for:
	
	bleu $s3, 0, end_for

	mul $t0, $s3, 16
	add $a1, $s2, $t0
	move $a0, $s4
	move $a2, $s7
	jal key_addition
	
	move $a0, $s7
	move $a1, $s6
	jal inv_mix_column


	move $a0, $s6
	move $a1, $s5
	jal inv_shift_rows


	move $a0, $s5
	move $a1, $s4
	jal inv_byte_substitution

	subu $s3, $s3, 1

	j for

end_for:
	
	move $a0, $s4
	move $a1, $s2
	move $a2, $s1
	jal key_addition


	lw   $ra, 0($sp)
	lw   $s0, 4($sp)
	lw   $s1, 8($sp)
	lw   $s2, 12($sp)
	lb   $s3, 16($sp)
	lw   $s4, 20($sp)
	lw   $s5, 24($sp)
	lw   $s6, 28($sp)
	lw   $s7, 32($sp)
	add $sp, $sp ,100
	

	jr $ra
