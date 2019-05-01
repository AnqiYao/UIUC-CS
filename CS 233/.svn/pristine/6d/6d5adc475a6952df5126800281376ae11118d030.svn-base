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
.align 2
event_horizon_data: .space 90000

.text
main:
	
	li $t0,	10
	sw $t0,	VELOCITY
	
	la $t0, event_horizon_data
	sw $t0, REQUEST_JETSTREAM


	lw $t1, BOT_X  # x axis  
	lw $t2, BOT_Y  # y axis 

start:
	ble $t1, 150, west
	j east
west:
	ble $t2, 150, northwest	
	j southwest 
east:
	ble $t2, 150, northeast
	j southeast


northwest:
	li $t3, 0
	sw $t3, ANGLE
	li $t4, 1
	sw $t4, ANGLE_CONTROL

	lw $t1, BOT_X  # x axis  
	lw $t2, BOT_Y  # y axis 

	mul $t5, $t2,	300
	add $t5, $t5,	$t1
	add $t5, $t5,	$t0
	lb  $t5, 0($t5)	
	
	bne $t5, 2, set_angle
	
	j start


southwest:
	li $t3, 270
	sw $t3, ANGLE
	li $t4, 1
	sw $t4, ANGLE_CONTROL

	lw $t1, BOT_X  # x axis  
	lw $t2, BOT_Y  # y axis 

	mul $t5, $t2,	300
	add $t5, $t5,	$t1
	add $t5, $t5,	$t0
	lb  $t5, 0($t5)	
	
	bne $t5, 2, set_angle
	
	j start


northeast:
	li $t3, 90
	sw $t3, ANGLE
	li $t4, 1
	sw $t4, ANGLE_CONTROL

	lw $t1, BOT_X  # x axis  
	lw $t2, BOT_Y  # y axis 

	mul $t5, $t2,	300
	add $t5, $t5,	$t1
	add $t5, $t5,	$t0
	lb  $t5, 0($t5)	
	
	bne $t5, 2, set_angle
	
	j start


southeast:
	li $t3, 180
	sw $t3, ANGLE
	li $t4, 1
	sw $t4, ANGLE_CONTROL

	lw $t1, BOT_X  # x axis  
	lw $t2, BOT_Y  # y axis 

	mul $t5, $t2,	300
	add $t5, $t5,	$t1
	add $t5, $t5,	$t0
	lb  $t5, 0($t5)	
	
	bne $t5, 2, set_angle
	
	j start



set_angle: 
	lw $t7, ANGLE
	add $t7, $t7, 270
	bgt $t7, 360, if
end_if:	
	sw $t7, ANGLE
	li $t6, 1
	sw $t6, ANGLE_CONTROL
	

	lw $t1, BOT_X #get x value
	lw $t2, BOT_Y #get y value
	mul $t3, $t2, 300
	add $t3, $t3, $t1
	add $t3, $t3, $t0
	lb $t4,	0($t3) #get the pixs of current point

	beq $t4, 2, start
	j	end_if

if:
	sub $t7, $t7, 360
	j end_if	

	

	
