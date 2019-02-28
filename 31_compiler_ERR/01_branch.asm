.data
	strEq:	.asciiz "Equal!\n"
	strNe:	.asciiz "Not equal!\n"
.text
	.globl main

main:
	li	$v0, 5			#read_int
	syscall
	move $t0, $v0		#store $t0

	li $v0, 5			#read_int
	syscall
	move $t1, $v0		#store $t1

	bne $t0, $t1, _printNe

_printEq:
	la $a0, strEq		#load address
	j _print			#jump

_printNe:
	la $a0, strNe
	j _print

_print:
	li $v0, 4		#print_str
	syscall

