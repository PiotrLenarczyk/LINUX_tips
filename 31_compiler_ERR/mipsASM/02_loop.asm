#	do
#		counter++; sum+=counter;
#	while(counter<n);

.text
	.globl main
main:
	li  $v0, 5				#read_int
	syscall
	move $t0, $v0			#n

	li $t1, 0				#counter
	li $t2, 0				#sum

_loop:
	addi $t1, $t1, 1		#counter++
	add $t2, $t2, $t1		#sum+=counter
	bne $t0, $t1, _loop
_loopDone:
	li $v0, 1				#print_int
	move $a0, $t2
	syscall


