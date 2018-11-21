#!/bin/bash  



TARGET='STM32F411' 	#{ STM32F411 STM32 }



#=======================================================================
if 	[ "$TARGET" = "STM32" ];then #generic arm arch 
	CORE="CM0+";		
else
	CORE="CM4F";
fi
LOC_PATH=`pwd`
OPENOCD_CFG_PATH=$LOC_PATH/..

if [ "$CORE" = "CM0+" ];then		 
	CC_PATH=~/armCM0+/arm-unknown-eabi/bin/
	TOOL=arm-unknown-eabi
	GCC_ARCH='-march=armv6-m -mcpu=cortex-m0plus -mthumb -mthumb-interwork -mlittle-endian'		
	GCC_FLOAT='-mfloat-abi=soft -fsingle-precision-constant' 		
	L_FILE='../stm32xxxx.ld' 	#2kRAM + 8kFLASH
elif [ "$CORE" = "CM4F" ];then
	CC_PATH=~/armCM4F/arm-unknown-eabihf/bin/
	TOOL=arm-unknown-eabihf
	GCC_ARCH='-march=armv7e-m -mcpu=cortex-m4 -mthumb -mthumb-interwork -mlittle-endian'		#	GENERAL PURPOUSE REGISTER FLOAT EMULATION		#CM4F	FLOAT COPROCESSOR
	GCC_FLOAT='-mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant' 					#'-mfloat-abi=soft -fsingle-precision-constant' 	#'-mfloat-abi=hard -mfpu=fpv4-sp-d16 -fsingle-precision-constant'
	L_FILE='../stm32_CM4F.ld'	#16kRAM + 64kFLASH
fi
CC="$CC_PATH$TOOL"-gcc
CPP="$CC_PATH$TOOL"-g++
GDB="$CC_PATH$TOOL"-gdb
SIZE="$CC_PATH$TOOL"-size
NM="$CC_PATH$TOOL"-nm
OCOPY="$CC_PATH$TOOL"-objcopy


#FLAGS:
GCC_GENERAL='-std=c11 -pipe -static'
GCC_OPT='-O1 -Wall'
GCC_FLAGS='-ffunction-sections -fdata-sections -fno-builtin'					
GCC_PREPROC='-DCUSTOM_NEW -DNO_EXCEPTIONS'
GCC_WARN='-Wno-parentheses'

L_FLAGS='-nostartfiles -nodefaultlibs -nostdlib -Wl,-gc-sections -specs=nano.specs -specs=nosys.specs' #'-u _printf_float' //->huge codefile enlarge!

INC='..'
SRC=''
BIN='bin'


FILENAME='main'
cp $SRC$FILENAME.c $SRC$FILENAME"Tmp.c"
sed -i 's/__INCLUDE_GDB.*/#include "gdb_debug.c"/' $SRC$FILENAME"Tmp.c" #temporary preprocessor file

echo""&&echo "========================"&&echo " GDB via C Preprocessor output:"&& echo "========================"										&&
$CC $GCC_GENERAL $GCC_OPT $GCC_ARCH $GCC_FLAGS $GCC_FLOAT $GCC_WARN $GCC_PREPROC -D$TARGET -DDEBUG_CUSTOM $GCC_DEBUG -I$INC -E $SRC$FILENAME"Tmp.c" -o $SRC$FILENAME.g 	&&
rm $SRC$FILENAME"Tmp.c"
GCC_DEBUG=''
if grep -e BKPT -e GDB_EXEC "$SRC$FILENAME.g"&>>/dev/null; then ##search source file for debug commands: __BKPT, and single "variadic" external macro __GDB(...)
	GCC_DEBUG='-O0 -g'
	COMM_GDB="sleep 0.1; wmctrl -a GDB; sudo $GDB -ex \"target remote localhost:3333\" \
			-ex \"set pagination off\" \
			-ex \"set output-radix 16\" -ex \"tui enable\" "
	if grep -q GDB_EXEC "$SRC$FILENAME.g"; then
		GDB_COMMAND=`grep 'GDB_EXEC' $SRC$FILENAME.g | sed 's/^.*\"\"//'`
		GDB_COMMAND=${GDB_COMMAND#*\"\"}
		GDB_COMMAND=${GDB_COMMAND%\";*}
		GDB_COMMAND=${GDB_COMMAND/\"}
		GDB_COMMAND=${GDB_COMMAND/\"}
		GDB_COMMAND=${GDB_COMMAND/;;}
		TOKENIZE="$GDB_COMMAND"
		IFS=';' tokens=( $TOKENIZE )
		for token in "${tokens[@]}"
		do
			COMM_GDB="$COMM_GDB"" -ex \"$token\" "
		done
		IFS=''
	else 
		COMM_GDB="$COMM_GDB"" -ex \"c\" "
	fi
	COMM_GDB="$COMM_GDB""$LOC_PATH/$BIN/main.elf"
	echo $COMM_GDB
fi
sudo killall xterm &>> /dev/null
clear 																																	&&
echo""&&echo "========================"&&echo " Compiler output:"&& echo "========================"										&&
	eval "$CC $GCC_GENERAL $GCC_OPT $GCC_ARCH $GCC_FLAGS $GCC_FLOAT $GCC_WARN $GCC_PREPROC -D$TARGET $GCC_DEBUG -I$INC -c $SRC$FILENAME.c -o $SRC$FILENAME.o" &&
echo""&&echo "========================"&&echo " Linker output:"&& echo "========================"										&&
	eval "$CPP $SRC$FILENAME.o -T$L_FILE $L_FLAGS -o $BIN/$FILENAME.elf"																		&&
echo""&&echo "========================"&&echo " Sections size:"&& echo "========================"										&&
	$SIZE -tA --radix=16 $BIN/$FILENAME.elf																								&&
echo""&&echo "========================"&&echo " Symbols list:"&& echo "========================"										&&
	$NM $BIN/$FILENAME.elf																												&&
echo""&&echo "========================"&&echo " EFL->HEX:"&& echo "========================"											&&
	$OCOPY -Oihex $BIN/$FILENAME.elf $BIN/$FILENAME.hex 																				&&
srec_cat $BIN/$FILENAME.hex -intel -o $BIN/$FILENAME.tihex -HEX_Dump && cat $BIN/$FILENAME.tihex && rm -f $BIN/$FILENAME.tihex&& echo "========================" &&
rm -f $SRC$FILENAME.o $SRC$FILENAME.g $SRC$FILENAME.e $SRC$FILENAME.lst																	&&


if [ ${#GCC_DEBUG} -ge 1 ]	#DEBUG
then
	echo""&&echo "========================"&&echo " Debugging:"&& echo "========================"										&&
	COMM_1="sleep 0.1 && sudo telnet localhost 4444"
	COMM_2="sudo openocd -f $OPENOCD_CFG_PATH/openocd.cfg -c init -c \"reset halt\" -c \"flash write_image erase $BIN/$FILENAME.elf\" -c \"reset halt\""
	######
	sudo xterm -u8 -bg black -fg green -fa 14 -T "OPENOCD" 	-e "$COMM_2;exec bash" &  	
	sudo xterm -maximized -u8 -bg black -fg green -fa 14 -T "GDB" 		-e "$COMM_GDB;exec bash" &  				
else						#RUN
	echo""&&echo "========================"&&echo " DEPLOY&RUN:"&& echo "========================"											&&
	sudo openocd -f $OPENOCD_CFG_PATH/openocd.cfg -c init -c "reset halt"\
	-c "flash write_image erase $LOC_PATH/$BIN/$FILENAME.elf" -c "reset" -c "shutdown"  #&>> /dev/null	
fi
#===============================================================================================================================================
# ASM list:
eval "$CC -Wa,-adhln $GCC_GENERAL $GCC_OPT $GCC_ARCH $GCC_FLAGS $GCC_FLOAT $GCC_WARN $GCC_PREPROC -D$TARGET $GCC_DEBUG -I$INC -g $SRC$FILENAME.c > $SRC$FILENAME.lst 2> /dev/null";
#===============================================================================================================================================
