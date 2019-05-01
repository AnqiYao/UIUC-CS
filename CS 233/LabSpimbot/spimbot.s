.data
# syscall constants
PRINT_STRING = 4
PRINT_CHAR   = 11
PRINT_INT    = 1

# debug constants
PRINT_INT_ADDR   = 0xffff0080
PRINT_FLOAT_ADDR = 0xffff0084
PRINT_HEX_ADDR   = 0xffff0088

# spimbot memory-mapped I/O
VELOCITY       = 0xffff0010
ANGLE          = 0xffff0014
ANGLE_CONTROL  = 0xffff0018
BOT_X          = 0xffff0020
BOT_Y          = 0xffff0024
OTHER_BOT_X    = 0xffff00a0
OTHER_BOT_Y    = 0xffff00a4
TIMER          = 0xffff001c
SCORES_REQUEST = 0xffff1018

REQUEST_JETSTREAM	= 0xffff00dc
REQUEST_RADAR		= 0xffff00e0
BANANA			= 0xffff0040
MUSHROOM		= 0xffff0044
STARCOIN		= 0xffff0048

REQUEST_PUZZLE		= 0xffff00d0
SUBMIT_SOLUTION		= 0xffff00d4

# interrupt constants
BONK_MASK	= 0x1000
BONK_ACK	= 0xffff0060

TIMER_MASK	= 0x8000
TIMER_ACK	= 0xffff006c

REQUEST_RADAR_INT_MASK	= 0x4000
REQUEST_RADAR_ACK	= 0xffff00e4

REQUEST_PUZZLE_ACK	= 0xffff00d8
REQUEST_PUZZLE_INT_MASK	= 0x800


# put your data things here
.align 2
starcoin_map: .space 4096
jetstream_map: .space 90000
puzzle_data: .space 4096


.text
main:

	li 	$s0, 0

	li 	$t0, REQUEST_RADAR_INT_MASK
	li	$t1, REQUEST_PUZZLE_INT_MASK
	or	$t1, $t0, $t1
	or 	$t0, $t1, TIMER_MASK
	or	$t0, $t0, BONK_MASK
	or 	$t0, $t0, 1

	mtc0 	$t0, $12



	la 	$t0, jetstream_map
	sw 	$t0, REQUEST_JETSTREAM

	la 	$t0, puzzle_data
	sw 	$t0, REQUEST_PUZZLE

	bge	$s0, 4, puzzle_1

	lw	$t0, TIMER		# read current time
	add	$t0, $t0, 100		# add 100 to current time
	sw	$t0, TIMER

	li	$t5, 0


setup:

	li	$a0, 10
	sw	$a0, VELOCITY

	bge	$s0, 4, puzzle_1

	lw $t1, BOT_X   #x=t1
	lw $t2, BOT_Y 	#y=t2


start:

	bge	$s0, 4, puzzle_1
		li	$t0, 1
	mtc0 	$t0, $12
	bge $t1, 150, else_1
	bge $t2, 150, else_2_1

	sub $t3, $t2, 1
	mul $t3, $t3, 300
	add $t3, $t3, $t1

	lb $t3, jetstream_map($t3)
	beq $t3, 2, else_3_1
	j go_east
	li	$t0, 1
	mtc0 	$t0, $12

else_3_1:

	add $t3, $t1, 1
	mul $t4, $t2, 300
	add $t3, $t3, $t4
	lb $t3, jetstream_map($t3)
	bne $t3, 2, go_north
	j setup

else_2_1:

	sub $t3, $t1, 1
	mul $t4, $t2, 300
	add $t3, $t3, $t4
	lb $t3, jetstream_map($t3)
	beq $t3, 2, else_3_2

go_north:

	li $t1, 1
	sw $t1, ANGLE_CONTROL
	li $t1, 270
	sw $t1, ANGLE


	j setup

else_3_2:

	sub $t3, $t2, 1
	mul $t3, $t3, 300
	add $t3, $t3, $t1
	#add $t3, $t3, REQUEST_JETSTREAM
	lb $t3, jetstream_map($t3)
	bne $t3, 2, go_west
	j setup

else_1:
	bge $t2, 150, else_2_2

	add $t3, $t1, 1
	mul $t4, $t2, 300
	add $t3, $t3, $t4
	#add $t3, $t3, REQUEST_JETSTREAM
	lb $t3, jetstream_map($t3)
	beq $t3, 2, else_3_3
	j go_south

else_3_3:

	add $t3, $t2, 1
	mul $t3, $t3, 300
	add $t3, $t3, $t1
	#add $t3, $t3, REQUEST_JETSTREAM
	lb $t3, jetstream_map($t3)
	beq $t3, 2, setup

go_east:

	li $t1, 1
	sw $t1, ANGLE_CONTROL
	sw $0, ANGLE
	j setup

else_2_2:

	add $t3, $t2, 1
	mul $t3, $t3, 300
	add $t3, $t3, $t1
	#add $t3, $t3, REQUEST_JETSTREAM
	lb $t3, jetstream_map($t3)
	beq $t3, 2, else_3_4

go_west:

	li $t1, 1
	sw $t1, ANGLE_CONTROL
	li $t1, 180
	sw $t1, ANGLE


	j setup

else_3_4:

	sub $t3, $t1, 1
	mul $t4, $t2, 300
	add $t3, $t3, $t4

	lb $t3, jetstream_map($t3)
	beq $t3, 2, setup

go_south:

	li $t1, 1
	sw $t1, ANGLE_CONTROL
	li $t1, 90
	sw $t1, ANGLE
	j setup

go_northeast:

	li $t1, 1
	sw $t1, ANGLE_CONTROL
	li $t1, 315
	sw $t1, ANGLE
	j setup

go_northwest:
	li $t1, 1
	sw $t1, ANGLE_CONTROL
	li $t1, 225
	sw $t1, ANGLE
	j setup

go_southeast:

	li $t1, 1
	sw $t1, ANGLE_CONTROL
	li $t1, 45
	sw $t1, ANGLE
	j setup

go_southwest:
	li $t1, 1
	sw $t1, ANGLE_CONTROL
	li $t1, 135
	sw $t1, ANGLE
	j setup

puzzle_1:
	la	$t7, puzzle_data
	sw	$t7, REQUEST_PUZZLE
	li	$t0, 1
	mtc0 	$t0, $12
	j	setup



	.kdata
chunkIH:	.space 44	# space for two registers
	non_intrpt_str:	.asciiz "Non-interrupt exception\n"
	unhandled_str:	.asciiz "Unhandled interrupt type\n"
	three:	.float	3.0
	five:	.float	5.0
	PI:	.float	3.141592
	F180:	.float  180.0

	.ktext 0x80000180


interrupt_handler:
	.set noat
		move	$k1, $at		# Save $at
	.set at
		la	$k0, chunkIH
		sw	$a0, 0($k0)		# Get some free registers
		sw	$a1, 4($k0)		# li $t0, 1by storing them to a global variable
		sw 	$v0, 8($k0)
		sw  	$t1, 12($k0)
		sw 	$t2, 16($k0)
		sw 	$t3, 20($k0)
		sw 	$t4, 24($k0)
		sw 	$t5, 28($k0)
		sw  	$t6, 32($k0)
		sw 	$t7, 36($k0)
		sw 	$t8, 40($k0)



		mfc0	$k0, $13		# Get Cause register
		srl	$a0, $k0, 2
		and	$a0, $a0, 0xf		# ExcCode field
		bne	$a0, 0, non_intrpt

interrupt_dispatch:			# Interrupt:
	mfc0	$k0, $13		# Get Cause register, again
	beq	$k0, 0, done		# handled all outstanding interrupts


	and $a0, $k0, REQUEST_RADAR_INT_MASK
	bne $a0, 0, starcoin_interrupt

	and	$a0, $k0, TIMER_MASK	# is there a timer interrupt?
	bne	$a0, 0, timer_interrupt

	and	$a0, $k0, REQUEST_PUZZLE_INT_MASK	# is there a puzzle intterrupt?
	bne	$a0, 0,	 puzzle_interrupt

	and	$a0, $k0, BONK_MASK	# is there a bonk interrupt?
	bne	$a0, 0, bonk_interrupt

# add dispatch for other interrupt types here.

	li	$v0, PRINT_STRING	# Unhandled interrupt types
	la	$a0, unhandled_str
	syscall
	j	done

bonk_interrupt:

	sw      $a1, 0xffff0060($zero)   # acknowledge interrupt

      	li      $a1, 10                  #  ??
	lw      $a0, 0xffff001c($zero)   # what
	and     $a0, $a0, 1              # does
	bne     $a0, $zero, bonk_skip    # this
	li      $a1, -10                 # code

bonk_skip:
	sw      $a1, 0xffff0010($zero)

	j       interrupt_dispatch

timer_interrupt:
	sw	$a1, TIMER_ACK		# acknowledge interrupt

	lw	$v0, TIMER
	bge 	$v0, 50, timer_skip
	sw 	$zero, VELOCITY
	la 	$t3, starcoin_map
	sw 	$t3, REQUEST_RADAR

timer_skip:

	lw	$v0, TIMER		# current time
	add	$v0, $v0, 50000
	sw	$v0, TIMER		# request timer in 50000 cycles

	j	interrupt_dispatch

puzzle_interrupt:

	sw	$a1, REQUEST_PUZZLE_ACK
	la	$a0, puzzle_data
	li	$t2, 0
	sw	$t2, VELOCITY
	jal 	puzzle
	sw	$v0, SUBMIT_SOLUTION
	j	interrupt_dispatch



starcoin_interrupt:

	sw 	$a1, REQUEST_RADAR_ACK
	add 	$s0, $s0, 1

	lw $t1, BOT_X
	lw $t2, BOT_Y
	lh $t3, starcoin_map($zero) #$t3=y*
	li $t4, 2
	lh $t4, starcoin_map($t4) #t4=x*
	lw $t5, starcoin_map($zero)
	beq $t5, 0xffffffff, starcoin_interrupt_end
	sub $a0, $t4, $t1 #a0 = x diff
	slt $t6, $a0, 10
	sgt $t7, $a0, -10
	and $t6, $t6, $t7
	beq $t6, $zero, starcoin_interrupt_end
	sub $a1, $t3, $t2 #a1 = y diff
	slt $t6, $a1, 10
	sgt $t7, $a1, -10
	and $t6, $t6, $t7
	beq $t6, $zero, starcoin_interrupt_end

getting_stars_x:

	bge $a0, 0, interrupt_go_east
	j interrupt_go_west

	getting_stars_y:

	sw $zero, VELOCITY
	bge $a1, 0, interrupt_go_south
	j interrupt_go_north

interrupt_go_east:
	li $v0, 4
	sw $v0, VELOCITY
	sw $0, ANGLE
	li $v0, 1
	sw $v0, ANGLE_CONTROL
	j getting_stars_xx

interrupt_go_west:
	li $v0, 4
	sw $v0, VELOCITY
	li $v0, 180
	sw $v0, ANGLE
	li $v0, 1
	sw $v0, ANGLE_CONTROL
	j getting_stars_xx

interrupt_go_south:
	li $v0, 4
	sw $v0, VELOCITY
	li $v0, 90
	sw $v0, ANGLE
	li $v0, 1
	sw $v0, ANGLE_CONTROL
	j getting_stars_yy

	interrupt_go_north:
	li $v0, 4
	sw $v0, VELOCITY
	li $v0, 270
	sw $v0, ANGLE
	li $v0, 1
	sw $v0, ANGLE_CONTROL
	j getting_stars_yy

	getting_stars_xx:
	lw $t5, BOT_X
	sub $a0, $t4, $t5 #a0 = x diff
	abs $a0, $a0
	ble $a0, 1, getting_stars_y
	j getting_stars_xx

	getting_stars_yy:
	lw $t6, BOT_Y
	sub $a1, $t3, $t6
	abs $a1, $a1
	ble $a1, 1, starcoin_interrupt_end
	j getting_stars_yy

	starcoin_interrupt_end:
	j interrupt_dispatch

non_intrpt:				# was some non-interrupt
	li	$v0, PRINT_STRING
	la	$a0, non_intrpt_str
	syscall				# print out an error message

	j done
done:
	la	$k0, chunkIH
	lw	$a0, 0($k0)		# Restore saved registers
	lw	$a1, 4($k0)
	lw  $v0, 8($k0)
	lw  $t1, 12($k0)
	lw 	$t2, 16($k0)
	lw 	$t3, 20($k0)
	lw 	$t4, 24($k0)
	lw 	$t5, 28($k0)
	lw  $t6, 32($k0)
	lw 	$t7, 36($k0)
	lw 	$t8, 40($k0)


.set noat
	move	$at, $k1		# Restore $at
.set at
	eret





















.globl decrypt
decrypt:
    # Your code goes here :)
    #There is the stack mem and the saved reg 
    sub $sp, $sp, 100 
 	sw	$ra, 0($sp)
	sw	$s0, 4($sp)
	sw	$s1, 8($sp)
	sw	$s2, 12($sp)
	sw	$s3, 16($sp)
	sw	$s4, 20($sp)
	sw	$s5, 24($sp)
	sw	$s6, 28($sp)
	sw	$s7, 32($sp)


    #Args, except rounds
    move $s0, $a0
    move $s1, $a1
    move $s2, $a2
    #stored in s7
    move $s7, $a3

    #A,B,C D loc 
    add $s3, $sp, 36
    add $s4, $sp, 52
    add $s5, $sp, 68
    add $s6, $sp, 84
    
    move $a0, $s0
    mul $t0, $s7,16
    add $a1,$s2 ,$t0
    move $a2, $s5
    jal key_addition

    move $a0, $s5
    move $a1, $s4
    jal inv_shift_rows

    move $a0,$s4
    move $a1,$s3
    jal inv_byte_substitution

    #Rounds - 1
    sub $s7, $s7, 1
for_loop:
    ble $s7, 0,end_for_loop

    move $a0, $s3
    mul $t0, $s7,16
    add $a1, $s2,$t0
    move $a2, $s6
    jal key_addition

    move $a0, $s6
    move $a1, $s5
    jal inv_mix_column

    move $a0, $s5
    move $a1, $s4
    jal inv_shift_rows

    move $a0,$s4
    move $a1,$s3
    jal inv_byte_substitution

    sub $s7, $s7, 1
    j for_loop
end_for_loop:

    move $a0, $s3
    move $a1, $s2 
    move $a2, $s1
    jal key_addition    

 	lw	$ra, 0($sp)
	lw	$s0, 4($sp)
	lw	$s1, 8($sp)
	lw	$s2, 12($sp)
	lw	$s3, 16($sp)
	lw	$s4, 20($sp)
	lw	$s5, 24($sp)
	lw	$s6, 28($sp)
	lw	$s7, 32($sp)
    add $sp, $sp, 100 

    jr $ra





.globl inv_byte_substitution
inv_byte_substitution:
	la	$t9, inv_sbox		# $t9 = inv_sbox = &inv_sbox[0]

	move	$t0, $0			# $t0 = unsigned int i = 0
ibs_for:
	bge	$t0, 16, ibs_done	# if (i >= 16), done

	add	$t1, $a0, $t0		# &in[i]
	lbu	$t1, 0($t1)		# in[i]

	add	$t2, $t9, $t1		# &inv_sbox[in[i]]
	lbu	$t2, 0($t2)		# inv_sbox[in[i]]

	add	$t3, $a1, $t0		# &out[i]
	sb	$t2, 0($t3)		# out[i] = inv_sbox[in[i]]

	add	$t0, $t0, 1		# i++
	j	ibs_for

ibs_done:
	jr	$ra



.globl key_addition
key_addition:
	move	$t0, $0			# $t0 = unsigned int i = 0
ka_for:
	bge	$t0, 16, ka_done 	# if (i >= 16), done

	add	$t1, $a0, $t0		# &in_one[i]
	lbu	$t1, 0($t1)		# in_one[i]

	add	$t2, $a1, $t0		# &in_two[i]
	lbu	$t2, 0($t2)		# in_two[i]

	xor	$t3, $t1, $t2		# in_one[i] ^ in_two[i]

	add	$t4, $a2, $t0		# &out[i]
	sb	$t3, 0($t4)		# out[i] = in_one[i] ^ in_two[i]

	add	$t0, $t0, 1		# i++
	j	ka_for

ka_done:
	jr	$ra


.globl inv_shift_rows
inv_shift_rows:
	#7 saved registers, 20 for stack
	sub	$sp, $sp, 36
	sw	$ra, 0($sp)
	sw	$s0, 4($sp)
	sw	$s1, 8($sp)
	sw	$s2, 12($sp)
	sw	$s3, 16($sp)

	#Assign M
	add	$s0, $sp, 20
	#Assign in
	move	$s1, $a0
	#assign out
	move	$s2, $a1

	move	$a0, $s1
	move	$a1, $s0
	jal	rearrange_matrix

	#Assign I
	move	$s3, $zero
for_loop_1:
	bge	$s3, 4, end_for

	li	$a1, 4
	sub	$a1, $a1, $s3

	mul	$t0, $s3, 4
	add	$t0, $s0, $t0

	lw	$a0, 0($t0)
	jal	circular_shift

	mul	$t0, $s3, 4
	add	$t0, $s0, $t0
	sw	$v0, 0($t0)

	add	$s3, $s3, 1
	j	for_loop_1
end_for:
	move	$a0, $s0
	move	$a1, $s2
	jal	rearrange_matrix



.globl inv_mix_column
inv_mix_column:
	sub	$sp, $sp, 16
	sw	$s0, 0($sp)
	sw	$s1, 4($sp)
	sw	$s2, 8($sp)
	sw	$s3, 12($sp)

	move	$s0, $zero
for_first:
	bge	$s0, 4, for_first_done
	move	$s1, $zero
for_second:
	bge	$s1, 4, for_second_done    

	#store where out[4*k+i] is 
	mul	$t0, $s0, 4    
	add	$t0, $t0, $s1
	add	$s3, $a1, $t0
	sb	$zero, 0($s3)

	move	$s2, $zero
for_third:
	bge	$s2, 4, for_third_done
	mul	$t0, $s2, 256     
	add	$t1, $s1, $s2
	rem	$t1, $t1, 4
	mul	$t2, $s0, 4
	add	$t2, $t2, $t1
	add	$t2, $t2, $a0

	lbu	$t2, 0($t2)

	add	$t0, $t0, $t2
	la	$t4, inv_mix
	add	$t0, $t0, $t4
	lbu	$t0, 0($t0)    

	lb	$t5, 0($s3)
	xor	$t5, $t5, $t0
	sb	$t5, 0($s3)

	add	$s2, $s2, 1
	j	for_third
for_third_done:
	add	$s1, $s1, 1
	j	for_second
for_second_done:
	add	$s0, $s0, 1
	j	for_first
for_first_done:
	lw	$s0, 0($sp)
	lw	$s1, 4($sp)
	lw	$s2, 8($sp)
	lw	$s3, 12($sp)
	add	$sp, $sp, 16
	jr	$ra

	lw	$ra, 0($sp)
	lw	$s0, 4($sp)
	lw	$s1, 8($sp)
	lw	$s2, 12($sp)
	lw	$s3, 16($sp)
	add	$sp, $sp, 36
	jr	$ra





.globl max_unique_n_substr
max_unique_n_substr:
	beq	$a0, $0, muns_abort 		# !in_str
	beq	$a1, $0, muns_abort		# !out_str
	beq	$a2, $0, muns_abort		# !n
	j	muns_do

muns_abort:
	jr	$ra

muns_do:
	sub	$sp, $sp, 36
	sw	$ra, 0($sp)
	sw	$s0, 4($sp)			# $s0 = char *in_str
	sw	$s1, 8($sp)			# $s1 = char *out_str
	sw	$s2, 12($sp)			# $s2 = int n
	sw	$s3, 16($sp)			# $s3 = char *max_marker
	sw	$s4, 20($sp)			# $s4 = unsigned int len_max
	sw	$s5, 24($sp)			# $s5 = unsigned int len_in_str
	sw	$s6, 28($sp)			# $s6 = unsigned int cur_pos
	sw	$s7, 32($sp)			# $s7 = int len_cur

	move	$s0, $a0
	move	$s1, $a1
	move	$s2, $a2

	move	$s3, $a0			# max_marker = in_str
	li	$s4, 0				# len_max = 0

	jal	my_strlen			# my_strlen(in_str)
	move	$s5, $v0			# len_in_str = my_strlen(in_str)

	li	$s6, 0				# cur_pos = 0
muns_for:
	bge	$s6, $s5, muns_for_end 		# if (cur_pos >= len_in_str), end

	add	$s7, $s0, $s6			# i = in_str + cur_pos

	move	$a0, $s7
	add	$a1, $s2, 1
	jal	nth_uniq_char			# nth_uniq_char(i, n + 1)

	ble	$v0, $s4, muns_for_cont		# if (len_cur <= len_max), continue
	move	$s4, $v0			# len_max = len_cur
	move	$s3, $s7			# max_marker = i

muns_for_cont:
	add	$s6, $s6, 1			# cur_pos++
	j	muns_for

muns_for_end:
	## Setup call to my_strncpy
	move	$a0, $s1
	move	$a1, $s3
	move	$a2, $s4

	lw      $ra, 0($sp)
	lw      $s0, 4($sp)
	lw      $s1, 8($sp)
	lw      $s2, 12($sp)
	lw      $s3, 16($sp)
	lw      $s4, 20($sp)
	lw      $s5, 24($sp)
	lw      $s6, 28($sp)
	lw      $s7, 32($sp)
	add	$sp, $sp, 36

	## Tail call
	j	my_strncpy			# my_strncpy(out_str, max_marker, len_max)



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
	beq	$a0, $0, nuc_abort 		# !in_str
	beq	$a1, $0, nuc_abort		# !n
	j	nuc_ok

nuc_abort:
	li	$v0, -1				# return -1
	jr	$ra

nuc_ok:
	la	$t0, uniq_chars			# $t0 = uniq_chars = &uniq_chars[0]
	lb	$t9, 0($a0)			# *in_str
	sb	$t9, 0($t0)			# uniq_chars[0] = *in_str

	li	$t1, 1				# $t1 = int uniq_so_far = 1
	li	$t2, 0				# $t2 = int position = 0
	add	$a0, $a0, 1			# in_str++

nuc_while:
	bge	$t1, $a1, nuc_while_end 	# if (uniq_so_far >= n), end
	lb	$t9, 0($a0)			# *in_str
	beq	$t9, $0, nuc_while_end		# if (*in_str == 0), end

	li	$t3, 1				# $t3 = char is_uniq = 1

	li	$t4, 0				# $t4 = int j = 0
nuc_for:
	bge	$t4, $t1, nuc_for_end

	add	$t9, $t0, $t4			# &uniq_chars[j]
	lb	$t9, 0($t9)			# uniq_chars[j]
	lb	$t8, 0($a0)			# *in_str
	bne	$t9, $t8, nuc_for_cont		# if (uniq_chars[j] != *in_str), skip
	li	$t3, 0
	j	nuc_for_end

nuc_for_cont:
	add	$t4, $t4, 1			# j++
	j	nuc_for

nuc_for_end:
	beq	$t3, $0, nuc_while_cont 	# if (is_uniq == 0), continue
	lb	$t9, 0($a0)			# *in_str
	add	$t8, $t0, $t1			# &uniq_chars[uniq_so_far]
	sb	$t9, 0($t8)			# uniq_chars[uniq_so_far] = *in_str
	add	$t1, $t1, 1			# uniq_so_far++

nuc_while_cont:
	add	$t2, $t2, 1			# position++
	add	$a0, $a0, 1			# in_str++
	j	nuc_while

nuc_while_end:
	bge	$t1, $a1, nuc_end 		# if (uniq_so_far >= n), skip
	add	$t2, $t2, 1			# position++

nuc_end:
	move	$v0, $t2			# return position
	jr	$ra

.globl my_strlen
my_strlen:
	move	$v0, $0			# $v0 = unsigned int count = 0
	bne	$a0, $0, ms_while	# if (in != NULL), skip
	jr	$ra			# return 0

ms_while:
	lb	$t0, 0($a0)		# $t0 = *in
	beq	$t0, $0, ms_done	# if (in == 0), done

	add	$v0, $v0, 1		# count++
	add	$a0, $a0, 1		# in++
	j	ms_while

ms_done:
	jr	$ra			# return count




.globl rearrange_matrix
rearrange_matrix:
	move	$t0, $zero
rm_for_loop: 
	bge	$t0, 4, end_for_loop

	#pointer to out
	mul	$t1, $t0, 4
	add	$t1, $t1, $a1

	sw	$zero, 0($t1)

	move	$t2, $zero
second_for_loop:
	#load in
	bge	$t2, 4, end_second_for_loop
	mul	$t3, $t2, 4  
	add	$t3, $t3, $t0
	add	$t3, $a0, $t3

	lbu	$t4, 0($t3)         
	mul	$t5, $t2 ,8
	sllv	$t4, $t4, $t5

	lw	$t5, 0($t1)
	or	$t5, $t5, $t4
	sw	$t5, 0($t1)

	add	$t2, $t2, 1
	j	second_for_loop

end_second_for_loop:
	add	$t0, $t0, 1
	j	rm_for_loop
end_for_loop:
	jr	$ra

