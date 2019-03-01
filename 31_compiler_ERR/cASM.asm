	.text
	.globl	main
	.globl	_exit
	.globl	_print_int
	.globl	_print_string
main:
	lui	$gp,4096
	jal	_main
_exit:
	ori	$v0,$0,10
	syscall
_print_int:
	ori	$v0,$0,1
	syscall
	jr	$ra
_print_string:
	ori	$v0,$0,4
	syscall
	jr	$ra
	.text
	.globl	_main
_0:
	addi	$t0,$fp,-8
	ori	$t1,$0,5
	sw	$t1,0($t0)
	or	$t0,$t1,$0
	ori	$t0,$0,0
	or	$v0,$t0,$0
_1:
	lw	$ra,-4($fp)
	or	$sp,$fp,$0
	lw	$fp,0($sp)
	addi	$sp,$sp,4
	jr	$ra
_main:
	addi	$sp,$sp,-16
	sw	$fp,12($sp)
	addi	$fp,$sp,12
	sw	$ra,-4($fp)
	j	_0
