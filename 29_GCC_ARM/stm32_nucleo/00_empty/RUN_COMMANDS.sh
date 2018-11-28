#!/bin/bash  
#https://istarc.wordpress.com/2014/07/21/stm32f4-build-your-toolchain-from-scratch/
#https://embdev.net/topic/linker-error-undefined-reference-to-_sbrk
#######################################################################
# A method - host system compilation ( done at Lubuntu 18.04 64bit )
#######################################################################
# build_arm_tools.sh configuration:
#			#export BINUTILS=binutils-2.25
#			#export GCC=gcc-7.3.0
#			#export NEWLIB=newlib-2.1.0
#			#export NEWLIB_NANO=newlib-nano-2.1.0
#			#export GDB=gdb-8.1
#	#	sudo apt-get install build-essential flex bison libgmp3-dev libmpfr-dev libncurses5-dev libmpc-dev autoconf texinfo libtool libftdi-dev libusb-1.0-0-dev zlib1g zlib1g-dev python-yaml
#	#	sudo apt-get install -y openocd ncurses-dev build-essential git libgmp-dev libmpfr-dev libmpc-dev zlib1g-dev
#	#	sudo ./build_arm_tools.sh
# 
# build GCC with newlib error ( some older compilers f.e. 5.1.0 ):
# 	sudo vim ~/arm/src/gcc-5.1.0/gcc/cp/cfns.h 
#			comment GNU_INLINE l:125
# comment done steps and rerun
#######################################################################
# B method - trivial virtual machine compilation
#######################################################################
#	#VBox->Ubuntu14.04_64bit 
#	build_arm_tools.sh configuration:
#			#export BINUTILS=binutils-2.25
#			#export GCC=gcc-4.9.2
#			#export NEWLIB=newlib-2.1.0
#			#export NEWLIB_NANO=newlib-nano-2.1.0
#			#export GDB=gdb-7.7
#	#	sudo apt-get install aptitude openssh-server git && sudo ufw allow 22
#	#	sudo apt-get install build-essential flex bison libgmp3-dev libmpfr-dev libncurses5-dev libmpc-dev autoconf texinfo libtool libftdi-dev libusb-1.0-0-dev zlib1g zlib1g-dev python-yaml               
#	#	sudo apt-get install -y openocd ncurses-dev build-essential git libgmp-dev libmpfr-dev libmpc-dev zlib1g-dev && sudo apt-get purge -y binutils-arm-none-eabi gcc-arm-none-eabi gdb-arm-none-eabi libnewlib-arm-none-eabi
#	#	sudo chmod +x build_arm_tools.sh && sudo ./build_arm_tools.sh
#	#	mkdir /hostHomeFolder/arm
#	#	sudo rsync -uvr VBoxGuestHomeFolder/arm user@IPAddr_v4:/hostHomeFolder/arm
#	#### find missing dependencies:
#	#sudo ln -s /usr/lib/x86_64-linux-gnu/libmpfr.so.6 /usr/lib/x86_64-linux-gnu/libmpfr.so.4
#	#sudo cp ~/arm/libexec/gcc/arm-none-eabi/4.9.2/liblto_plugin.so.0.0.0 ~/arm/libexec/gcc/arm-none-eabi/4.9.2/liblto_plugin.so
LOC_PATH=`pwd`
CC_PATH=~/arm/bin/
CC="$CC_PATH"arm-none-eabi-gcc
CPP="$CC_PATH"arm-none-eabi-g++
GDB="$CC_PATH"arm-none-eabi-gdb
SIZE="$CC_PATH"arm-none-eabi-size
NM="$CC_PATH"arm-none-eabi-nm
OCOPY="$CC_PATH"arm-none-eabi-objcopy

#FLAGS:
GCC_GENERAL='-std=c11 -c -pipe -static'
GCC_OPT='-O1 -Wall' #'-O1 -Wall'
GCC_ARCH='-march=armv7e-m -mcpu=cortex-m4 -mthumb -mthumb-interwork -mlittle-endian'
GCC_FLAGS='-ffunction-sections -fdata-sections -fno-builtin'				#		GENERAL PURPOUSE REGISTER FLOAT EMULATION	#	FLOAT COPROCESSOR	
GCC_FLOAT='-mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant' #'-mfloat-abi=softfp -fsingle-precision-constant' #'-mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant'
GCC_PREPROC='-DCUSTOM_NEW -DNO_EXCEPTIONS'
GCC_WARN='-Wno-parentheses'
GCC_DEBUG='' #'-O0 -g' for debug enable

L_FILE='stm32_CM4F.ld'
L_FLAGS='-nostartfiles -nodefaultlibs -nostdlib -Wl,-gc-sections -specs=nano.specs -specs=nosys.specs -u _printf_float' #huge codefile enlarge!

INC='inc'
SRC='src/'
BIN='bin'

TARGET='STM32F411'
FILENAME='main'
clear 																																	&&
echo""&&echo "========================"&&echo " Compiler output:"&& echo "========================"										&&
	$CC $GCC_GENERAL $GCC_OPT $GCC_ARCH $GCC_FLAGS $GCC_FLOAT $GCC_WARN $GCC_PREPROC -D$TARGET $GCC_DEBUG -I$INC $SRC$FILENAME.c -o $SRC$FILENAME.o 	&&
echo""&&echo "========================"&&echo " Linker output:"&& echo "========================"										&&
	$CPP $SRC$FILENAME.o $GCC_OPT $GCC_ARCH $GCC_FLOAT -T$L_FILE $L_FLAGS 	-o $BIN/$FILENAME.elf										&&
echo""&&echo "========================"&&echo " Sections size:"&& echo "========================"										&&
	$SIZE -tA --radix=16 $BIN/$FILENAME.elf																								&&
echo""&&echo "========================"&&echo " Symbols list:"&& echo "========================"										&&
	$NM $BIN/$FILENAME.elf																												&&
echo""&&echo "========================"&&echo " EFL->HEX:"&& echo "========================"											&&
	$OCOPY -Oihex $BIN/$FILENAME.elf $BIN/$FILENAME.hex 																				&&
srec_cat $BIN/$FILENAME.hex -intel -o $BIN/$FILENAME.tihex -HEX_Dump && cat $BIN/$FILENAME.tihex && rm -f $BIN/$FILENAME.tihex&& echo "========================"

if [ ${#GCC_DEBUG} -ge 1 ]	#DEBUG
then
	sudo killall -I lxterminal																											&&
	echo""&&echo "========================"&&echo " Debugging:"&& echo "========================"										&&
	COMM_1="sleep 2 && sudo telnet localhost 4444"
	COMM_2="sudo openocd -f openocd.cfg -c init -c \"halt\" -c \"flash write_image erase $BIN/$FILENAME.elf\" -c \"reset halt\""
	COMM_3="sleep 1 && wmctrl -a GDB && sudo $GDB -ex \"target remote localhost:3333\" -ex \"tui enable\" -ex \"c\" $LOC_PATH/$BIN/main.elf"
	######
	#sudo lxterminal -t "TELNET" 	-e "$COMM_1" 				&
	sudo lxterminal -t "OPENOCD" 	-e "$COMM_2" 				& 
	sudo lxterminal -t "GDB" 		-e "$COMM_3" 				&
	exec bash						
	######
	#sudo killall -I gnome-terminal
	##sudo gnome-terminal -x sh -c "$COMM_1;bash" 							&
	#sudo gnome-terminal -x sh -c "$COMM_2;bash " 							& 
	#sudo gnome-terminal -x sh -c "$COMM_3;bash" 							&
	#exec bash
########################################################################
#		GDB crib
########################################################################
#	monitor reset halt 
#	b main  #break main
#	b 119	#break line 119 
#	c		#continue -> resume program execution
#	s		#step -> single source line steps
#	next	#single source line without steps
#	step 4	#four source lines steps
#	stepi 	#single instruction step with step-in-function
#	nexti	#single source line step without step-in-function
#	fin		#finish -> step out of a function
#	u 121	#continue until line no 121 with temporary breakpoint
#	where 	#program stopped at line no..
#	list 	#list program source where it was stopped
#	x 0x1 	#read memory at address 0x1
#	p a		#print a -> value of a variable
#	p &a	#print a address
#	p *(unsigned*)0x0	#print unsigned value pointed by address 0x0
#	bt		#backtrace -> print stack calls
#	bt 3 full	#print last three stack calls with local variables values
#	info target	#target connection details
#	info source	#info about codefile
#	info stack	#current instruction calls
#	info program #target instruction address where program stops
#	info all-registers
#	layout next #tui next layout
#		layout split
#		layout regs
########################################################################
else						#RUN
	echo""&&echo "========================"&&echo " DEPLOY&RUN:"&& echo "========================"											&&
	sudo openocd -f openocd.cfg -c init -c "halt" -c "flash write_image erase $BIN/$FILENAME.elf" -c "reset" -c "shutdown"  #&>> /dev/null	
fi
touch $SRC$FILENAME.o && rm $SRC$FILENAME.o																									&&
echo ""
