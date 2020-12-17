//########################################################################
//#		GDB crib
//########################################################################
//#	monitor reset halt 
//#	b main  #break main
//#	b 119	#break line 119 
//#	b main.c:main	#break at file main.c at function main
//#	b 119 if ( i == 15 )	#break at line no 119, if i variable equals 15
//#	tbreak 119	#one-time-hit temporary breakpoint at line no. 119
//#	watch i		#watch - set breakpoint for each variable value change
//#	watch ( i == 15 ) #watchpoint - set breakpoint if variable i equals 15
//# break main.c:6 if i == 5 #set conditional breakpoint on file line
//#	c		#continue -> resume program execution
//#	s		#step -> single source line steps
//#	next	#single source line without steps
//#	step 4	#four source lines steps
//#	stepi 	#single instruction step with step-in-function
//#	nexti	#single source line step without step-in-function
//#	fin		#finish -> step out of a function
//#	u 121	#continue until line no 121 with temporary breakpoint
//#	where 	#program stopped at line no..
//#	list 	#list program source where it was stopped
//#	x 0x1 	#read memory at address 0x1
//#	set {int}0x1 = 0x11223344	#set memory addres 0x1 with int (4B) value 0x11223344
//# display a	#display a variable value each program stop
//#	p a		#print a -> value of a variable
//##	p &a	#print an address
//#	p a[0]	#print first a array elem
//#	p a[3]@5 #print five a array elems starting from fourth elem
//#	p *(unsigned*)0x0	#print unsigned value pointed by address 0x0
//#	bt		#backtrace -> print stack calls
//#	bt 3 full	#print last three stack calls with local variables values
//#	info target	#target connection details
//#	info locals	#view local variables
//#	info macro FOO	#view macro "FOO" value; #define FOO 1
//#	gcc -gdwarf-2 -g3 empty.c #debug macros with: { p FOO; info macro FOO }
//# finish #executes function until it finishes
//#	return #returns from current function  stack frame (optionally with value)
//#	info breakpoints #view all program breakpoints
//#	info source	#info about codefile
//#	info stack	#current instruction calls
//#	info program #target instruction address where program stops
//#	info all-registers
//#	layout next #tui next layout
//#		layout split
//#		layout regs
//#	Ctr+p 	#TUI previous cli command
//#	Ctr+n 	#TUI next cli command
//#	Alt+Enter	#TUI fullscreen
//#	directory ../DirectoryPath/ #include directories for searching for files with debug information
//# set cheduler-locking off #stop multithreading, and debug current thread
//########################################################################

#ifdef	DEBUG_CUSTOM
	#ifdef __GDB
		#undef __GDB
	#endif
	#define	__GDB( command )			;"//GDB_EXEC"""b __LINE__;c;STRINGIZE( command );;
#endif
