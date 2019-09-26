#!/bin/bash
#http://www.iwasz.pl/electronics/toolchain-for-cortex-m4/
#http://crosstool-ng.org/start
sudo aptitude install -y bison flex gperf texinfo gawk libtool libtool-bin automake libncurses5-dev libexpat-dev help2man
git clone https://github.com/crosstool-ng/crosstool-ng
cd crosstool-ng/ && ./bootstrap
./configure --prefix=`~/`
make -j`nproc` && sudo make install
mkdir -p ../staging && cd ../staging/ && ../crosstool-ng/ct-ng menuconfig 
#optionaly one can use preconfigured samples for final tuning:
#	./ct-ng list-samples 
#	./ct-ng arm-unknown-linux-gnueabi 
#	./ct-ng menuconfig 
########################################################################
#########   checked on Ubuntu 16.04/18.04 64b
########################################################################
#Paths and misc. options
#	Y: Try features marked as EXPERIMENTAL
#	Y: Debug crosstool-NG
#		Y:Save intermediate steps
#	N: Render the toolchain read-only
#	2: Number of parallel jobs ##nproc
#Target options:
#	Target architecture: arm
#	Default instruction set mode: thumb
#================================================
#			ALL TARGETS OPTIONS:
#https://gcc.gnu.org/onlinedocs/gcc/Submodel-Options.html#Submodel-Options
#	Architecture level: -march=XXXX
#================================================
#	Architecture level (-march): 			#CM0+
#						armv6-m				#CM0+
#	Emit assembly for CPU (-mtune): 		#CM0+
#						cortex-m0plus		#CM0+
#	Use specific FPU: "" ( none )			#CM0+
#	Floating point: software - no FPU		#CM0+
#================================================
#	Architecture level: armv7e-m			#CM4F
#	Emit assembly for CPU: cortex-m4		#CM4F
#	Use specific FPU:  fpv4-sp-d16			#CM4F
#	Floating point: hardware ( FPU )		#CM4F
#================================================
#	####basic MIPS arch for learning purposes:
#	Architecture level: mips1				#MIPS
#	Floating point: software - no FPU		#MIPS
#================================================
#	Target architecture: avr				#AVR
#	####default "avr" mcu cores access:		#AVR
#	####avr25; avr3; avr31; avr34; avr35; 	#AVR
#	####avr4; avr5; avr51; avr6; 			#AVR
#	####avrxmega2/4/5/6/7; avrtiny; msp8	#AVR
#   no avr-target specific configuration	#AVR
#C-library:									#AVR
#	C-library: avr-libc						#AVR
#================================================
#	Architecture level (-march): 			#x86-32
#						blank: i386			#x86-32
#						i586				#x86-32
#	Bitness:	32bit						#x86-32
#================================================
#Toolchain options:
#	Toolchain ID string: cm0plus
#	Tuple's vendor string: "" (  )
#Operating System:
#	Target OS: bare-metal
#Binary utilities
#	Version of binutils: 2.31.1
#C-library:
#	C-library: newlib
#	Version of newlib: 3.0.0
#	Y: Disable the syscalls supplied with newlib
#C compiler:
#	Show gcc versions from: Linaro
#	Version of gcc-linaro: 7.3
#	Y: C++
#Debug facilities:
#	Y: GDB
#		Version of gdb: 8.2
#		N: Enable python scripting
#Save config:
#	".config"
unset LD_LIBRARY_PATH 
../crosstool-ng/ct-ng build
#secondary terminal:
tail -f build.log
#================================================
#mv -f ~/x-tools ~/armCM0+					#CM0+
#================================================
#mv -f ~/x-tools ~/armCM4F					#CM4F
#================================================
