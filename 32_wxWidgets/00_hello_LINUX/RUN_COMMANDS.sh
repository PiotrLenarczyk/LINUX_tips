#!/bin/bash
GCC_OPT='-mtune=native -march=native -std=gnu++11 -Ofast -pipe'
GCC_FLOAT='-Wdouble-promotion -fsingle-precision-constant'
GCC_FLAGS='-fmax-errors=3'
#GCC_WX="`wx-config --cxxflags` `wx-config --libs`"
GCC_WX="-I C:\wxWidgets-3.1.2\include\wx\  -I C:\wxWidgets-3.1.2\include\ -I C:\wxWidgets-3.1.2\include\wx\msw\ "
LIBS=''
touch a.out && rm a.out && clear &&g++ -o a.out $GCC_OPT $GCC_FLAGS $GCC_FLOAT $GCC_WX main.cpp $LIBS && ./a.out
rm -f a.out
