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

.macro sendj

.macro sendk

.macro send0

  #
  # Please add your own code below this line
  #

.global waitforkeyboard
waitforkeyboard:
#enable pulldown
#set input on port
#wait for D- pull-up
#disable port

signalsleep: #waits exactly 53 cycles for use in between usb signalling cycles
	addi	$t0, $0, 15
	sleeploop:
	addi	$t0, $t0, -1
	blez	$t0,sleeploop
	nop
	jr		$ra
	nop

sendsync:
	sendk
	jal		signalsleep
	nop
	sendj
	jal		signalsleep
	nop
	sendk
	jal		signalsleep
	nop
	sendj
	jal		signalsleep
	nop
	sendk
	jal		signalsleep
	nop
	sendj
	jal		signalsleep
	nop
	sendk
	jal		signalsleep
	nop
	sendk
	jr		$ra
	nop
