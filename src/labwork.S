  # labwork.S
  # Written 2015-2017 by F Lundevall
  # Skeleton file for IS1200/IS1500 lab 1.
  # The macros PUSH and POP are in the public domain.
  # Please add your own code at the end of the file.

  #
  # Please keep the two macros PUSH and POP unchanged
  #
.macro	PUSH reg
	addi	$sp,$sp,-4
	sw	\reg,0($sp)
.endm

.macro	POP reg
	lw	\reg,0($sp)
	addi	$sp,$sp,4
.endm
  #
  # Please add your own code below this line
  #

hexasc:
	andi	$a0,$a0,0xf
	addi	$t0,$0,9
	ble	$a0,$t0,hop
	nop #[delay-slot]
	addi	$v0,$a0,55 #[delay-slot]
	jr 	$ra
	nop
	hop:
		addi	$v0,$a0,48 #[delay-slot]
		jr	$ra
		nop

.global	delay
delay:
	addi $t0,$0,8827 #[delay-slot] 8827
	blez $a0,nomoredelay
	nop
	delayloop:
		addiu $t0,$t0,-1
		bne 	$t0,$0,delayloop
		nop #[delay-slot]
	addiu $a0,$a0,-1
	bne		$a0, $0,delay
	nop #[delay-slot]
	nomoredelay:
	jr $ra
	nop #[delay-slot]

.global enable_interrupt
enable_interrupt:
ei
jr $ra
nop
