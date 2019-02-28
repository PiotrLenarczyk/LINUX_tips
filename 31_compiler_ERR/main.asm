.text
.globl   main
main:
li $t0, 0x2			#$t0<-0x2
li $t1, 0x3			#$t1<-0x3
addu $t2, $t0, $t1 	#$t2<-ADD($t0,$t1)
