#!/bin/bash
#http://www.iwasz.pl/electronics/toolchain-for-cortex-m4/
sudo aptitude install -y bison flex gperf texinfo gawk libtool libtool-bin automake libncurses5-dev libexpat-dev help2man
git clone https://github.com/crosstool-ng/crosstool-ng
cd crosstool-ng/ && ./bootstrap
./configure --prefix=`~/`
make -j`nproc` && sudo make install
mkdir -p ../staging && cd ../staging/ && ../crosstool-ng/ct-ng menuconfig 
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
#	Architecture level: armv6-m				#CM0+
#	Emit assembly for CPU: cortex-m0plus	#CM0+
#	Use specific FPU: "" ( none )			#CM0+
#	Floating point: software - no FPU		#CM0+
#================================================
#	Architecture level: armv7e-m			#CM4F
#	Emit assembly for CPU: cortex-m4		#CM4F
#	Use specific FPU:  fpv4-sp-d16			#CM4F
#	Floating point: hardware ( FPU )		#CM4F
#================================================
#Toolchain options:
#	Toolchain ID string: cm0plus
#	Tuple's vendor string: "" (  )
#Operating System:
#	Target OS: bare-metal
#Binary utilities
#	Version of binutils: 2.31.1
#C-library:
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
unset LD_LIBRARY_PATH 
../crosstool-ng/ct-ng build
#secondary terminal:
tail -f build.log
#================================================
#mv -f ~/x-tools ~/armCM0+					#CM0+
#================================================
#mv -f ~/x-tools ~/armCM4F					#CM4F
#================================================
