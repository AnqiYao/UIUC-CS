# syscall constants
PRINT_STRING	= 4
PRINT_CHAR	= 11
PRINT_INT	= 1

# memory-mapped I/O
VELOCITY	= 0xffff0010
ANGLE		= 0xffff0014
ANGLE_CONTROL	= 0xffff0018

BOT_X		= 0xffff0020
BOT_Y		= 0xffff0024

TIMER		= 0xffff001c

REQUEST_JETSTREAM	= 0xffff00dc
REQUEST_STARCOIN	= 0xffff00e0

PRINT_INT_ADDR		= 0xffff0080
PRINT_FLOAT_ADDR	= 0xffff0084
PRINT_HEX_ADDR		= 0xffff0088

# interrupt constants
BONK_MASK	= 0x1000
BONK_ACK	= 0xffff0060

TIMER_MASK	= 0x8000
TIMER_ACK	= 0xffff006c

REQUEST_STARCOIN_INT_MASK	= 0x4000
REQUEST_STARCOIN_ACK		= 0xffff00e4

.data
# put your data things here
three:	.float	3.0
five:	.float	5.0
PI:	.float	3.141592
F180:	.float  180.0

.align 2
event_horizon_data: .space 90000
starcoin_data: .space 512
starcoin_flag: .space 1

.text
main:
	# put your code here :)
	li	$t4, BONK_MASK
	or	$t4, $t4, REQUEST_STARCOIN_INT_MASK		# STARCOIN interrupt enable bit
	or	$t4, $t4, TIMER_MASK
	or	$t4, $t4, 1
	mtc0	$t4, $12		# set interrupt mask (Status register)

	la $t0, event_horizon_data
	sw $t0, REQUEST_JETSTREAM

	
	lw $t1, BOT_X		#x-coord
	lw $t2, BOT_Y		#y-coord


	li $t3, 0
	sw $t3, VELOCITY		#VELOCITY

#call_interrupt:
	#la $t9, starcoin_data
	#sw $t9, REQUEST_STARCOIN	# request starcoin interrupt

start:
	lw $t1, BOT_X		#x-coord
	lw $t2, BOT_Y		#y-coord

	lw	$t9, TIMER		# read current time
	add	$t9, $t9, 20	# add 50 to current time
	sw	$t9, TIMER		# request timer interrupt in 50 cycles

	li $t3, 10
	sw $t3, VELOCITY		#VELOCITY
	bge $t1, 150, east
	j west

east:
	bge $t2, 150, southeast
	j northeast

west:
	bge $t2, 150, southwest
	j northwest

northeast:
	li $t3, 90	
	li $t4, 1
	sw $t3, ANGLE
	sw $t4, ANGLE_CONTROL

	lw $t1, BOT_X
	lw $t2, BOT_Y
	mul $t5, $t2, 300
	add $t5, $t5, $t1
	add $t5, $t5, $t0
	lb $t5, 0($t5)

	beq $t5, 1, set_angle
	j start

southeast:
	li $t3, 180
	li $t4, 1
	sw $t3, ANGLE
	sw $t4, ANGLE_CONTROL
	lw $t2, BOT_Y
	mul $t5, $t2, 300
	add $t5, $t5, $t1
	add $t5, $t5, $t0
	lb $t5, 0($t5)

	beq $t5, 1, set_angle
	j start

northwest:
	li $t3, 0
	li $t4, 1
	sw $t3, ANGLE
	sw $t4, ANGLE_CONTROL

	lw $t1, BOT_X
	lw $t2, BOT_Y
	mul $t5, $t2, 300
	add $t5, $t5, $t1
	add $t5, $t5, $t0
	lb $t5, 0($t5)

	beq $t5, 1, set_angle
	j start

southwest:
	li $t3, 270
	li $t4, 1
	sw $t3, ANGLE
	sw $t4, ANGLE_CONTROL

	lw $t1, BOT_X
	lw $t2, BOT_Y
	mul $t5, $t2, 300
	add $t5, $t5, $t1
	add $t5, $t5, $t0
	lb $t5, 0($t5)

	beq $t5, 1, set_angle
	j start

set_angle:
	lw $t3, ANGLE
	add $t3, $t3, 300
	bgt $t3, 360, minus

end_minus:
	li $t4, 1
	sw $t3, ANGLE
	sw $t4, ANGLE_CONTROL

	lw $t1, BOT_X
	lw $t2, BOT_Y
	mul $t5, $t2, 300
	add $t5, $t5, $t1
	add $t5, $t5, $t0
	lb $t5, 0($t5)

	beq $t5, 1, start
	j end_minus

minus:
	sub $t3, $t3, 360
	j end_minus


	#li	$t4, REQUEST_STARCOIN_INT_MASK		# STARCOIN interrupt enable bit
	#mtc0	$t4, $12		# set interrupt mask (Status register)

	# request starcoin interrupt
	#la $t0, starcoin_data
	#sw $t0, REQUEST_STARCOIN		# request starcoin interrupt in 50 cycles

	# note that we infinite loop to avoid stopping the simulation early
	#j	main	beq $t5, 0xffffffff, start
	j check



.kdata				# interrupt handler data (separated just for readability)
chunkIH:	.space 8	# space for two registers# request s	beq $t5, 0xffffffff, start
non_intrpt_str:	.asciiz "Non-interrupt exception\n"
unhandled_str:	.asciiz "Unhandled interrupt type\n"


.ktext 0x80000180
interrupt_handler:
.set noat
	move	$k1, $at		# Save $at
.set at
	la	$k0, chunkIH# request starcoin interrupt
	sw	$a0, 0($k0)		# Get some free registers
	sw	$a1, 4($k0)		# by storing them to a global variable

	mfc0	$k0, $13		# Get # request starcoin interruptCause register
	srl	$a0, $k0, 2
	and	$a0, $a0, 0xf		# ExcCode field
	bne	$a0, 0, non_intrpt

interrupt_dispatch:			# Interrupt:
	mfc0	$k0, $13		# Get Cause register, again
	beq	$k0, 0, done		# handled all outstanding interrupts

	# add dispatch for other interrupt types here.
	and	$a0, $k0, REQUEST_STARCOIN_INT_MASK	# is there a starcoin interrupt?
	bne	$a0, 0, starcoin_interrupt

	and	$a0, $k0, TIMER_MASK	# is there a timer interrupt?
	bne	$a0, 0, timer_interrupt
	
	and	$a0, $k0, BONK_MASK
	bne	$a0, 0, bonk_interrupt

	li	$v0, PRINT_STRING	# Unhandled interrupt types
	la	$a0, unhandled_str
	syscall
	j	done

timer_interrupt:
	sw	$a1, TIMER_ACK		# acknowledge interrupt

	la $t9, starcoin_data
	sw $t9, REQUEST_STARCOIN	# request starcoin interrupt

	j	interrupt_dispatch	# see if other interrupts are waiting

bonk_interrupt:
	sw $a1, BONK_ACK

	 
	li $t3, 10
	sw $t3, VELOCITY	

	lw $t3, BOT_X
	lw $t4, BOT_Y
	
	bgt $t3, 150, go_135
	bgt $t4, 150, go_315
	
	
	li $t5, 90
	sw $t5, ANGLE
	li $t5, 1
	sw $t5, ANGLE_CONTROL
	j interrupt_dispatch
go_135:
	bgt $t4, 150,	 go_225
	
	li $t5, 135
	sw $t5, ANGLE
	li $t5, 1
	sw $t5, ANGLE_CONTROL
	li $t5, 10
	sw $t5, VELOCITY	
	j interrupt_dispatch

go_315:
		
	li $t5, 315
	sw $t5, ANGLE
	li $t5, 1
	sw $t5, ANGLE_CONTROL
	li $t5, 10
	sw $t5, VELOCITY
	j interrupt_dispatch
go_225:
	
	li $t5, 225
	sw $t5, ANGLE
	li $t5, 1
	sw $t5, ANGLE_CONTROL
	li $t5, 10
	sw $t5, VELOCITY	
	j interrupt_dispatch

starcoin_interrupt:
	sw $a1, REQUEST_STARCOIN_ACK		# acknowledge interrupt
	la $t9, starcoin_data
	lh $t8, 0($t9)
	lh $t7, 2($t9)
	beq $t7, -1, interrupt_dispatch
	beq $t8, -1, interrupt_dispatch
	lw $t4, BOT_X
	lw $t9, BOT_Y
	li $t6, 10
	sw $t6, VELOCITY

need_move:
	lw $t4, BOT_X
	lw $t9, BOT_Y
	blt $t4, $t7, right
	bgt $t4, $t7, left
	blt $t9, $t8, down
	bgt $t9, $t8, up

	j go_back

right:
	li $t6, 0
	sw $t6, ANGLE
	li $t6, 1
	sw $t6, ANGLE_CONTROL
	j need_move

left:
	li $t6, 180
	sw $t6, ANGLE
	li $t6, 1
	sw $t6, ANGLE_CONTROL
	j need_move

up:
	li $t6, 270
	sw $t6, ANGLE
	li $t6, 1
	sw $t6, ANGLE_CONTROL
	j need_move

down:
	li $t6, 90
	sw $t6, ANGLE
	li $t6, 1
	sw $t6, ANGLE_CONTROL
	j need_move

	right1:
		li $t6, 0
		sw $t6, ANGLE
		li $t6, 1
		sw $t6, ANGLE_CONTROL
		j go_back

	left1:
		li $t6, 180
		sw $t6, ANGLE
		li $t6, 1
		sw $t6, ANGLE_CONTROL
		j go_back

	up1:
		li $t6, 270
		sw $t6, ANGLE
		li $t6, 1
		sw $t6, ANGLE_CONTROL
		j go_back

	down1:
		li $t6, 90
		sw $t6, ANGLE
		li $t6, 1
		sw $t6, ANGLE_CONTROL
		j go_back

go_back:
	lw $t4, BOT_X
	lw $t9, BOT_Y
	blt $t4, $t1, right1
	bgt $t4, $t1, left1
	blt $t9, $t2, down1
	bgt $t9, $t2, up1
	j interrupt_dispatch

non_intrpt:				# was some non-interrupt
	li	$v0, PRINT_STRING
	la	$a0, non_intrpt_str
	syscall				# print out an error message
		# fall through to done

done:
	la	$k0, chunkIH
	lw	$a0, 0($k0)		# Restore saved registers
	lw	$a1, 4($k0)
.set noat
	move	$at, $k1		# Restore $at
.set at
	eret



