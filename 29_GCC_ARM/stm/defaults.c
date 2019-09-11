#if !( defined STM32 )
	#define RAM_END 0x20003FFF	//16kiB of RAM
#else
	#define RAM_END 0x200007FF //generic STM32 with 2kiB of RAM
#endif
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// malloc: _srbk() + necessary linker entries: _end;__HEAP_START)
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
typedef char* caddr_t;
#ifndef NULL
	#define NULL ( void* )( RAM_END + 1 )
#endif
extern int  __HEAP_START;
caddr_t _sbrk ( int incr )
{	static unsigned char *heap = NULL;
	unsigned char *prev_heap;
	if ( heap == NULL )
		heap = ( unsigned char * )&__HEAP_START;
	prev_heap = heap;
	heap += incr;
	return ( caddr_t ) prev_heap;
};//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
//====
typedef unsigned char byte;
typedef unsigned char u8;
typedef unsigned short u16;
typedef unsigned u32;
typedef long unsigned u64;
typedef volatile unsigned char vu8;
typedef volatile unsigned short vu16;
typedef volatile unsigned vu32;
typedef volatile long unsigned vu64;
typedef volatile float vf;
//====
#ifdef	__GNUC__
	#define	asm	__asm__
#else	
	#define	asm	asm
#endif
#define	S0											0x00000001	//set bit
#define	S1											0x00000002
#define	S2											0x00000004
#define	S3											0x00000008
#define	S4											0x00000010
#define	S5											0x00000020
#define	S6											0x00000040
#define	S7											0x00000080
#define	S8											0x00000100
#define	S9											0x00000200
#define	S10											0x00000400
#define	S11											0x00000800
#define	S12											0x00001000
#define	S13											0x00002000
#define	S14											0x00004000
#define	S15											0x00008000
#define	S16											0x00010000
#define	S17											0x00020000
#define	S18											0x00040000
#define	S19											0x00080000
#define	S20											0x00100000
#define	S21											0x00200000
#define	S22											0x00400000
#define	S23											0x00800000
#define	S24											0x01000000
#define	S25											0x02000000
#define	S26											0x04000000
#define	S27											0x08000000
#define	S28											0x10000000
#define	S29											0x20000000
#define	S30											0x40000000
#define	S31											0x80000000
#define	RS0											0xFFFFFFFE	//RSeset bit
#define	RS1											0xFFFFFFFD
#define	RS2											0xFFFFFFFB
#define	RS3											0xFFFFFFF7
#define	RS4											0xFFFFFFEF
#define	RS5											0xFFFFFFDF
#define	RS6											0xFFFFFFBF
#define	RS7											0xFFFFFF7F
#define	RS8											0xFFFFFEFF
#define	RS9											0xFFFFFDFF
#define	RS10										0xFFFFFBFF
#define	RS11										0xFFFFF7FF
#define	RS12										0xFFFFEFFF
#define	RS13										0xFFFFDFFF
#define	RS14										0xFFFFBFFF
#define	RS15										0xFFFF7FFF
#define	RS16										0xFFFEFFFF
#define	RS17										0xFFFDFFFF
#define	RS18										0xFFFBFFFF
#define	RS19										0xFFF7FFFF
#define	RS20										0xFFEFFFFF
#define	RS21										0xFFDFFFFF
#define	RS22										0xFFBFFFFF
#define	RS23										0xFF7FFFFF
#define	RS24										0xFEFFFFFF
#define	RS25										0xFDFFFFFF
#define	RS26										0xFBFFFFFF
#define	RS27										0xF7FFFFFF
#define	RS28										0xEFFFFFFF
#define	RS29										0xDFFFFFFF
#define	RS30										0xBFFFFFFF
#define	RS31										0x7FFFFFFF
#define	Z0											0x00000000	//zeros for reading
#define	Z1											0x00000000
#define	Z2											0x00000000
#define	Z3											0x00000000
#define	Z4											0x00000000
#define	Z5											0x00000000
#define	Z6											0x00000000
#define	Z7											0x00000000
#define	Z8											0x00000000
#define	Z9											0x00000000
#define	Z10											0x00000000
#define	Z11											0x00000000
#define	Z12											0x00000000
#define	Z13											0x00000000
#define	Z14											0x00000000
#define	Z15											0x00000000
#define	Z16											0x00000000
#define	Z17											0x00000000
#define	Z18											0x00000000
#define	Z19											0x00000000
#define	Z20											0x00000000
#define	Z21											0x00000000
#define	Z22											0x00000000
#define	Z23											0x00000000
#define	Z24											0x00000000
#define	Z25											0x00000000
#define	Z26											0x00000000
#define	Z27											0x00000000
#define	Z28											0x00000000
#define	Z29											0x00000000
#define	Z30											0x00000000
#define	Z31											0x00000000

#define STRINGIZE( arg )							#arg
#define CONCATENATE( arg1, arg2 ) 					arg1##arg2
#define	SEQ_0( x )						
#define	SEQ_1( x )									x;
#define	SEQ_2( x )									x; SEQ_1( x )
#define	SEQ_3( x )									x; SEQ_2( x )
#define	SEQ_4( x )									x; SEQ_3( x )
#define	SEQ_5( x )									x; SEQ_4( x )
#define	SEQ_6( x )									x; SEQ_5( x )
#define	SEQ_7( x )									x; SEQ_6( x )
#define	SEQ_8( x )									x; SEQ_7( x )
#define	SEQ_9( x )									x; SEQ_8( x )
#define	SEQ_10( x )									x; SEQ_9( x )
#define	SEQ_11( x )									x; SEQ_10( x )
#define	SEQ_12( x )									x; SEQ_11( x )
#define	SEQ_13( x )									x; SEQ_12( x )
#define	SEQ_14( x )									x; SEQ_13( x )
#define	SEQ_15( x )									x; SEQ_14( x )
#define	SEQ_16( x )									x; SEQ_15( x )
#define	SEQ_17( x )									x; SEQ_16( x )
#define	SEQ_18( x )									x; SEQ_17( x )
#define	SEQ_19( x )									x; SEQ_18( x )
#define	SEQ_20( x )									x; SEQ_19( x )
#define	SEQ_21( x )									x; SEQ_20( x )
#define	SEQ_22( x )									x; SEQ_21( x )
#define	SEQ_23( x )									x; SEQ_22( x )
#define	SEQ_24( x )									x; SEQ_23( x )
#define	SEQ_25( x )									x; SEQ_24( x )
#define	SEQ_26( x )									x; SEQ_25( x )
#define	SEQ_27( x )									x; SEQ_26( x )
#define	SEQ_28( x )									x; SEQ_27( x )
#define	SEQ_29( x )									x; SEQ_28( x )
#define	SEQ_30( x )									x; SEQ_29( x )
#define	SEQ_31( x )									x; SEQ_30( x )
#define	SEQ_32( x )									x; SEQ_31( x )
#define DEPLOY( N, instruct ) 						CONCATENATE( SEQ_, N )( instruct );	//instruct;instruct;

#define	 S_1( x )									x(  1 );			//S-semicolon separated number-argument macros
#define	 S_2( x )									x(  2 ); S_1( x )
#define	 S_3( x )									x(  3 ); S_2( x )
#define	 S_4( x )									x(  4 ); S_3( x )
#define	 S_5( x )									x(  5 ); S_4( x )
#define	 S_6( x )									x(  6 ); S_5( x )
#define	 S_7( x )									x(  7 ); S_6( x )
#define	 S_8( x )									x(  8 ); S_7( x )
#define	 S_9( x )									x(  9 ); S_8( x )
#define	S_10( x )									x( 10 ); S_9( x )
#define	S_11( x )									x( 11 ); S_10( x )
#define	S_12( x )									x( 12 ); S_11( x )
#define	S_13( x )									x( 13 ); S_12( x )
#define	S_14( x )									x( 14 ); S_13( x )
#define	S_15( x )									x( 15 ); S_14( x )
#define	S_16( x )									x( 16 ); S_15( x )
#define	S_17( x )									x( 17 ); S_16( x )
#define	S_18( x )									x( 18 ); S_17( x )
#define	S_19( x )									x( 19 ); S_18( x )
#define	S_20( x )									x( 20 ); S_19( x )
#define	S_21( x )									x( 21 ); S_20( x )
#define	S_22( x )									x( 22 ); S_21( x )
#define	S_23( x )									x( 23 ); S_22( x )
#define	S_24( x )									x( 24 ); S_23( x )
#define	S_25( x )									x( 25 ); S_24( x )
#define	S_26( x )									x( 26 ); S_25( x )
#define	S_27( x )									x( 27 ); S_26( x )
#define	S_28( x )									x( 28 ); S_27( x )
#define	S_29( x )									x( 29 ); S_28( x )
#define	S_30( x )									x( 30 ); S_29( x )
#define	S_31( x )									x( 31 ); S_30( x )
#define	S_32( x )									x( 32 ); S_31( x )
#define	 C_1( x )									x(  1 ) 			//C-comma separated number-argument macros
#define	 C_2( x )									x(  2 ), C_1( x )
#define	 C_3( x )									x(  3 ), C_2( x )
#define	 C_4( x )									x(  4 ), C_3( x )
#define	 C_5( x )									x(  5 ), C_4( x )
#define	 C_6( x )									x(  6 ), C_5( x )
#define	 C_7( x )									x(  7 ), C_6( x )
#define	 C_8( x )									x(  8 ), C_7( x )
#define	 C_9( x )									x(  9 ), C_8( x )
#define	C_10( x )									x( 10 ), C_9( x )
#define	C_11( x )									x( 11 ), C_10( x )
#define	C_12( x )									x( 12 ), C_11( x )
#define	C_13( x )									x( 13 ), C_12( x )
#define	C_14( x )									x( 14 ), C_13( x )
#define	C_15( x )									x( 15 ), C_14( x )
#define	C_16( x )									x( 16 ), C_15( x )
#define	C_17( x )									x( 17 ), C_16( x )
#define	C_18( x )									x( 18 ), C_17( x )
#define	C_19( x )									x( 19 ), C_18( x )
#define	C_20( x )									x( 20 ), C_19( x )
#define	C_21( x )									x( 21 ), C_20( x )
#define	C_22( x )									x( 22 ), C_21( x )
#define	C_23( x )									x( 23 ), C_22( x )
#define	C_24( x )									x( 24 ), C_23( x )
#define	C_25( x )									x( 25 ), C_24( x )
#define	C_26( x )									x( 26 ), C_25( x )
#define	C_27( x )									x( 27 ), C_26( x )
#define	C_28( x )									x( 28 ), C_27( x )
#define	C_29( x )									x( 29 ), C_28( x )
#define	C_30( x )									x( 30 ), C_29( x )
#define	C_31( x )									x( 31 ), C_30( x )
#define	C_32( x )									x( 32 ), C_31( x )
#define	 CST_1( ARG1, x )							x( ARG1,  1 ) 			//C-comma separated TWO-ARGS number-argument macros
#define	 CST_2( ARG1, x )							x( ARG1,  2 ),  CST_1( ARG1, x )
#define	 CST_3( ARG1, x )							x( ARG1,  3 ),  CST_2( ARG1, x )
#define	 CST_4( ARG1, x )							x( ARG1,  4 ),  CST_3( ARG1, x )
#define	 CST_5( ARG1, x )							x( ARG1,  4 ),  CST_4( ARG1, x )
#define	 CST_6( ARG1, x )							x( ARG1,  5 ),  CST_5( ARG1, x )
#define	 CST_7( ARG1, x )							x( ARG1,  6 ),  CST_6( ARG1, x )
#define	 CST_8( ARG1, x )							x( ARG1,  7 ),  CST_7( ARG1, x )
#define	 CST_9( ARG1, x )							x( ARG1,  8 ),  CST_8( ARG1, x )
#define	CST_10( ARG1, x )							x( ARG1,  9 ),  CST_9( ARG1, x )
#define	CST_11( ARG1, x )							x( ARG1, 10 ), CST_10( ARG1, x )
#define	CST_12( ARG1, x )							x( ARG1, 11 ), CST_11( ARG1, x )
#define	CST_13( ARG1, x )							x( ARG1, 12 ), CST_12( ARG1, x )
#define	CST_14( ARG1, x )							x( ARG1, 13 ), CST_13( ARG1, x )
#define	CST_15( ARG1, x )							x( ARG1, 14 ), CST_14( ARG1, x )
#define	CST_16( ARG1, x )							x( ARG1, 15 ), CST_15( ARG1, x )
#define	CST_17( ARG1, x )							x( ARG1, 16 ), CST_16( ARG1, x )
#define	CST_18( ARG1, x )							x( ARG1, 17 ), CST_17( ARG1, x )
#define	CST_19( ARG1, x )							x( ARG1, 18 ), CST_18( ARG1, x )
#define	CST_20( ARG1, x )							x( ARG1, 19 ), CST_19( ARG1, x )
#define	CST_21( ARG1, x )							x( ARG1, 20 ), CST_20( ARG1, x )
#define	CST_22( ARG1, x )							x( ARG1, 21 ), CST_21( ARG1, x )
#define	CST_23( ARG1, x )							x( ARG1, 22 ), CST_22( ARG1, x )
#define	CST_24( ARG1, x )							x( ARG1, 23 ), CST_23( ARG1, x )
#define	CST_25( ARG1, x )							x( ARG1, 24 ), CST_24( ARG1, x )
#define	CST_26( ARG1, x )							x( ARG1, 25 ), CST_25( ARG1, x )
#define	CST_27( ARG1, x )							x( ARG1, 26 ), CST_26( ARG1, x )
#define	CST_28( ARG1, x )							x( ARG1, 27 ), CST_27( ARG1, x )
#define	CST_29( ARG1, x )							x( ARG1, 28 ), CST_28( ARG1, x )
#define	CST_30( ARG1, x )							x( ARG1, 29 ), CST_29( ARG1, x )
#define	CST_31( ARG1, x )							x( ARG1, 30 ), CST_30( ARG1, x )
#define	CST_32( ARG1, x )							x( ARG1, 31 ), CST_31( ARG1, x )
#define UNROLL_N( N, macroDef )						CONCATENATE( S_, N )( macroDef );	//macroDef(1);macroDef(2);
#define VEC_UNROLL_N( N, macroDef )					CONCATENATE( C_, N )( macroDef )	//macroDef(1),macroDef(2),
#define	VEC_UNROLL_ARG1_N( N, ARG1, macroDef )		CONCATENATE( CST_, N )( ARG1, macroDef )//macroDef(ARG1,1),macroDef(ARG1,2),

#define	LOOP_0( x )						
#define	LOOP_1( x )									x
#define	LOOP_2( x )									x LOOP_1( x )
#define	LOOP_3( x )									x LOOP_2( x )
#define	LOOP_4( x )									x LOOP_3( x )
#define	LOOP_5( x )									x LOOP_4( x )
#define	LOOP_6( x )									x LOOP_5( x )
#define	LOOP_7( x )									x LOOP_6( x )
#define	LOOP_8( x )									x LOOP_7( x )
#define	LOOP_9( x )									x LOOP_8( x )
#define	LOOP_10( x )								x LOOP_9( x )
#define	LOOP_11( x )								x LOOP_10( x )
#define	LOOP_12( x )								x LOOP_11( x )
#define	LOOP_13( x )								x LOOP_12( x )
#define	LOOP_14( x )								x LOOP_13( x )
#define	LOOP_15( x )								x LOOP_14( x )
#define	LOOP_16( x )								x LOOP_15( x )
#define	LOOP_17( x )								x LOOP_16( x )
#define	LOOP_18( x )								x LOOP_17( x )
#define	LOOP_19( x )								x LOOP_18( x )
#define	LOOP_20( x )								x LOOP_19( x )
#define	LOOP_21( x )								x LOOP_20( x )
#define	LOOP_22( x )								x LOOP_21( x )
#define	LOOP_23( x )								x LOOP_22( x )
#define	LOOP_24( x )								x LOOP_23( x )
#define	LOOP_25( x )								x LOOP_24( x )
#define	LOOP_26( x )								x LOOP_25( x )
#define	LOOP_27( x )								x LOOP_26( x )
#define	LOOP_28( x )								x LOOP_27( x )
#define	LOOP_29( x )								x LOOP_28( x )
#define	LOOP_30( x )								x LOOP_29( x )
#define	LOOP_31( x )								x LOOP_30( x )
#define	LOOP_32( x )								x LOOP_31( x )
#define	POW( val, order )							1 LOOP_##order( *(val) ) //pow(x,3) = x*x*x
#define	POWF( val, order )							1.0f LOOP_##order( *(val) )	//pow(float f, 3)=f*f*f

#define POLY_1( macroName, val, N, coef, ... ) 			macroName( val, 0, coef )
#define POLY_2( macroName, val, N, coef, ... )			macroName( val, 1, coef ) POLY_1( macroName, val, coef, __VA_ARGS__ )
#define POLY_3( macroName, val, N, coef, ... )			macroName( val, 2, coef ) POLY_2( macroName, val, coef, __VA_ARGS__ )
#define POLY_4( macroName, val, N, coef, ... )			macroName( val, 3, coef ) POLY_3( macroName, val, coef, __VA_ARGS__ )
#define POLY_5( macroName, val, N, coef, ... )			macroName( val, 4, coef ) POLY_4( macroName, val, coef, __VA_ARGS__ )
#define POLY_6( macroName, val, N, coef, ... )			macroName( val, 5, coef ) POLY_5( macroName, val, coef, __VA_ARGS__ )
#define POLY_7( macroName, val, N, coef, ... )			macroName( val, 6, coef ) POLY_6( macroName, val, coef, __VA_ARGS__ )
#define POLY_8( macroName, val, N, coef, ... )			macroName( val, 7, coef ) POLY_7( macroName, val, coef, __VA_ARGS__ )
#define POLY_9( macroName, val, N, coef, ... )			macroName( val, 8, coef ) POLY_8( macroName, val, coef, __VA_ARGS__ )
#define POLY_10( macroName, val, N, coef, ... )			macroName( val, 9, coef ) POLY_9( macroName, val, coef, __VA_ARGS__ )
#define POLY_11( macroName, val, N, coef, ... )			macroName( val, 10, coef ) POLY_10( macroName, val, coef, __VA_ARGS__ )
#define POLY_12( macroName, val, N, coef, ... )			macroName( val, 11, coef ) POLY_11( macroName, val, coef, __VA_ARGS__ )
#define POLY_13( macroName, val, N, coef, ... )			macroName( val, 12, coef ) POLY_12( macroName, val, coef, __VA_ARGS__ )
#define POLY_14( macroName, val, N, coef, ... )			macroName( val, 13, coef ) POLY_13( macroName, val, coef, __VA_ARGS__ )
#define POLY_15( macroName, val, N, coef, ... )			macroName( val, 14, coef ) POLY_14( macroName, val, coef, __VA_ARGS__ )
#define POLY_16( macroName, val, N, coef, ... )			macroName( val, 15, coef ) POLY_15( macroName, val, coef, __VA_ARGS__ )
#define POLY_17( macroName, val, N, coef, ... )			macroName( val, 16, coef ) POLY_16( macroName, val, coef, __VA_ARGS__ )
#define POLY_18( macroName, val, N, coef, ... )			macroName( val, 17, coef ) POLY_17( macroName, val, coef, __VA_ARGS__ )
#define POLY_19( macroName, val, N, coef, ... )			macroName( val, 18, coef ) POLY_18( macroName, val, coef, __VA_ARGS__ )
#define POLY_20( macroName, val, N, coef, ... )			macroName( val, 19, coef ) POLY_19( macroName, val, coef, __VA_ARGS__ )
#define POLY_21( macroName, val, N, coef, ... )			macroName( val, 20, coef ) POLY_20( macroName, val, coef, __VA_ARGS__ )
#define POLY_22( macroName, val, N, coef, ... )			macroName( val, 21, coef ) POLY_21( macroName, val, coef, __VA_ARGS__ )
#define POLY_23( macroName, val, N, coef, ... )			macroName( val, 22, coef ) POLY_22( macroName, val, coef, __VA_ARGS__ )
#define POLY_24( macroName, val, N, coef, ... )			macroName( val, 23, coef ) POLY_23( macroName, val, coef, __VA_ARGS__ )
#define POLY_25( macroName, val, N, coef, ... )			macroName( val, 24, coef ) POLY_24( macroName, val, coef, __VA_ARGS__ )
#define POLY_26( macroName, val, N, coef, ... )			macroName( val, 25, coef ) POLY_25( macroName, val, coef, __VA_ARGS__ )
#define POLY_27( macroName, val, N, coef, ... )			macroName( val, 26, coef ) POLY_26( macroName, val, coef, __VA_ARGS__ )
#define POLY_28( macroName, val, N, coef, ... )			macroName( val, 27, coef ) POLY_27( macroName, val, coef, __VA_ARGS__ )
#define POLY_29( macroName, val, N, coef, ... )			macroName( val, 28, coef ) POLY_28( macroName, val, coef, __VA_ARGS__ )
#define POLY_30( macroName, val, N, coef, ... )			macroName( val, 29, coef ) POLY_29( macroName, val, coef, __VA_ARGS__ )
#define POLY_31( macroName, val, N, coef, ... )			macroName( val, 30, coef ) POLY_30( macroName, val, coef, __VA_ARGS__ )
#define POLY_32( macroName, val, N, coef, ... )			macroName( val, 31, coef ) POLY_31( macroName, val, coef, __VA_ARGS__ )
#define	_POLY( expBase, powOrd, coef )						+ ( coef ) * ( POW( expBase, powOrd ) )
#define POLY_CUMMULATIVE_( N, macroName, expBase, ... )		CONCATENATE( POLY_, N )( macroName, expBase, N, __VA_ARGS__ )
#define POLY_CUMMULATIVE( expBase, macroName, ... ) 		POLY_CUMMULATIVE_( COUNT( __VA_ARGS__ ), macroName, expBase, __VA_ARGS__ )
#define	POLYNOMIAL( expBase, ... )							0x0 + POLY_CUMMULATIVE( expBase, _POLY, __VA_ARGS__ ); //at least frist order; POLYNOMIAL( x, -3, +2, +1 ) = -3*pow(x,2) +2*pow(x,1) +1

#define COUNT( ... ) 			COUNT_( __VA_ARGS__, COUNT_RSEQ_N() )
#define COUNT_( ... )			COUNT_ARG_N( __VA_ARGS__ )
#define COUNT_ARG_N( 										\
		  _1, _2, _3, _4, _5, _6, _7, _8, _9,_10, 			\
		 _11,_12,_13,_14,_15,_16,_17,_18,_19,_20, 			\
		 _21,_22,_23,_24,_25,_26,_27,_28,_29,_30, 			\
		 _31,_32,_33,_34,_35,_36,_37,_38,_39,_40, 			\
		 _41,_42,_43,_44,_45,_46,_47,_48,_49,_50, 			\
		 _51,_52,_53,_54,_55,_56,_57,_58,_59,_60, 			\
		 _61,_62,_63,_64,_65,_66,_67,_68,_69,_70, 			\
		 _71,_72,_73,_74,_75,_76,_77,_78,_79,_80, 			\
		 _81,_82,_83,_84,_85,_86,_87,_88,_89,_90, 			\
		 _91,_92,_93,_94,_95,_96,_97,_98,_99,_100, 			\
		 _101,_102,_103,_104,_105,_106,_107,_108,_109,_110, \
		 _111,_112,_113,_114,_115,_116,_117,_118,_119,_120, \
		 _121,_122,_123,_124,_125, 					N,...) 	N
#define COUNT_RSEQ_N() 										\
								124, 123, 122, 121, 120, 	\
		 119, 118, 117, 116, 115, 114, 113, 112, 111, 110, 	\
		 109, 108, 107, 106, 105, 104, 103, 102, 101, 100, 	\
		  99,  98,  97,  96,  95,  94,  93,  92,  91,  90, 	\
		  89,  88,  87,  86,  85,  84,  83,  82,  81,  80, 	\
		  79,  78,  77,  76,  75,  74,  73,  72,  71,  70, 	\
		  69,  68,  67,  66,  65,  64,  63,  62,  61,  60, 	\
		  59,  58,  57,  56,  55,  54,  53,  52,  51,  50, 	\
		  49,  48,  47,  46,  45,  44,  43,  42,  41,  40, 	\
		  39,  38,  37,  36,  35,  34,  33,  32,  31,  30, 	\
		  29,  28,  27,  26,  25,  24,  23,  22,  21,  20, 	\
		  19,  18,  17,  16,  15,  14,  13,  12,  11,  10, 	\
		   9,   8,   7,   6,   5,   4,   3,   2,   1,   0
//==============================================================================================
#define FE_CUMMULATIVE_1( macroName, x, ... ) 		macroName( x )
#define FE_CUMMULATIVE_2( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_1( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_3( macroName, x, ... )  		macroName( x ) FE_CUMMULATIVE_2( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_4( macroName, x, ... ) 		macroName( x ) FE_CUMMULATIVE_3( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_5( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_4( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_6( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_5( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_7( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_6( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_8( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_7( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_9( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_8( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_10( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_9( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_11( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_10( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_12( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_11( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_13( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_12( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_14( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_13( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_15( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_14( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_16( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_15( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_17( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_16( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_18( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_17( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_19( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_18( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_20( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_19( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_21( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_20( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_22( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_21( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_23( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_22( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_24( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_23( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_25( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_24( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_26( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_25( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_27( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_26( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_28( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_27( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_29( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_28( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_30( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_29( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_31( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_30( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_32( macroName, x, ... )		macroName( x ) FE_CUMMULATIVE_31( macroName,  __VA_ARGS__ )
#define FE_CUMMULATIVE_( N, macroName, ... )		CONCATENATE( FE_CUMMULATIVE_, N )( macroName, __VA_ARGS__ )
#define FOR_EACH_CUMMUlATIVE( macroName, ... ) 		FE_CUMMULATIVE_( COUNT( __VA_ARGS__ ), macroName, __VA_ARGS__ ) //variadic: macroDef(1) macroDef(2) ...

#define	 CST_V_1( macroName, ARG1, x, ... )			macroName( ARG1, 1, x );
#define	 CST_V_2( macroName, ARG1, x, ... )			macroName( ARG1, 2, x );  CST_V_1( macroName, ARG1, __VA_ARGS__ );
#define	 CST_V_3( macroName, ARG1, x, ... )			macroName( ARG1, 3, x );  CST_V_2( macroName, ARG1, __VA_ARGS__ );
#define	 CST_V_4( macroName, ARG1, x, ... )			macroName( ARG1, 4, x );  CST_V_3( macroName, ARG1, __VA_ARGS__ );
#define	 CST_V_5( macroName, ARG1, x, ... )			macroName( ARG1, 5, x );  CST_V_4( macroName, ARG1, __VA_ARGS__ );
#define	 CST_V_6( macroName, ARG1, x, ... )			macroName( ARG1, 6, x );  CST_V_5( macroName, ARG1, __VA_ARGS__ );
#define	 CST_V_7( macroName, ARG1, x, ... )			macroName( ARG1, 7, x );  CST_V_6( macroName, ARG1, __VA_ARGS__ );
#define	 CST_V_8( macroName, ARG1, x, ... )			macroName( ARG1, 8, x );  CST_V_7( macroName, ARG1, __VA_ARGS__ );
#define	 CST_V_9( macroName, ARG1, x, ... )			macroName( ARG1, 9, x );  CST_V_8( macroName, ARG1, __VA_ARGS__ );
#define CST_V_10( macroName, ARG1, x, ... )			macroName( ARG1, 10, x ); CST_V_9( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_11( macroName, ARG1, x, ... )			macroName( ARG1, 11, x );CST_V_10( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_12( macroName, ARG1, x, ... )			macroName( ARG1, 12, x );CST_V_11( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_13( macroName, ARG1, x, ... )			macroName( ARG1, 13, x );CST_V_12( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_14( macroName, ARG1, x, ... )			macroName( ARG1, 14, x );CST_V_13( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_15( macroName, ARG1, x, ... )			macroName( ARG1, 15, x );CST_V_14( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_16( macroName, ARG1, x, ... )			macroName( ARG1, 16, x );CST_V_15( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_17( macroName, ARG1, x, ... )			macroName( ARG1, 17, x );CST_V_16( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_18( macroName, ARG1, x, ... )			macroName( ARG1, 18, x );CST_V_17( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_19( macroName, ARG1, x, ... )			macroName( ARG1, 19, x );CST_V_18( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_20( macroName, ARG1, x, ... )			macroName( ARG1, 20, x );CST_V_19( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_21( macroName, ARG1, x, ... )			macroName( ARG1, 21, x );CST_V_20( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_22( macroName, ARG1, x, ... )			macroName( ARG1, 22, x );CST_V_21( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_23( macroName, ARG1, x, ... )			macroName( ARG1, 23, x );CST_V_22( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_24( macroName, ARG1, x, ... )			macroName( ARG1, 24, x );CST_V_23( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_25( macroName, ARG1, x, ... )			macroName( ARG1, 25, x );CST_V_24( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_26( macroName, ARG1, x, ... )			macroName( ARG1, 26, x );CST_V_25( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_27( macroName, ARG1, x, ... )			macroName( ARG1, 27, x );CST_V_26( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_28( macroName, ARG1, x, ... )			macroName( ARG1, 28, x );CST_V_27( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_29( macroName, ARG1, x, ... )			macroName( ARG1, 29, x );CST_V_28( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_30( macroName, ARG1, x, ... )			macroName( ARG1, 30, x );CST_V_29( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_31( macroName, ARG1, x, ... )			macroName( ARG1, 31, x );CST_V_30( macroName, ARG1, __VA_ARGS__ );
#define	CST_V_32( macroName, ARG1, x, ... )			macroName( ARG1, 32, x );CST_V_31( macroName, ARG1, __VA_ARGS__ );
#define FE_ARG1_( N, macroName, ARG1, ... )			CONCATENATE( CST_V_, N )( macroName, ARG1, __VA_ARGS__ )
#define FE_ARG1( macroName, ARG1, ... ) 			FE_ARG1_( COUNT( __VA_ARGS__ ), macroName, ARG1, __VA_ARGS__ ) //variadic: macroDef(ARG1,2,param2) macroDef(ARG1,1, param1) ...
//============================================================================================
//------------------------	VARIABLE HANDLERS ------------------------------------------------
//============================================================================================
#define	VARNAME_STRING( A )							( (A), STRINGIZE(A) )
#define	CONCAT_VARNAME_STRING( A, NO )				( VARNAME_STRING( CONCATENATE( A, NO ) ) )
#define CONCAT_VAR_ASSIGN( VARNAME, VARNO, VAL )	CONCATENATE( VARNAME, VARNO ) = (VAL);//VARNAMEVARNO=VAL;
#define	VEC_UNROLL_VARNAMES_N( N, VARNAME )			CONCATENATE( CST_, N )( VARNAME, CONCAT_VARNAME_STRING )//*string names*/"VARNAME1","VARNAME2",
#define	VEC_UNROLL_VARVALS_N( N, VARNAME )			CONCATENATE( CST_, N )( VARNAME, CONCATENATE )///*values*/VARNAME1,VARNAME2,
#define	GENERATE_VARS_N( N, TYPE, VARNAME )			TYPE CONCATENATE( CST_, N )( VARNAME, CONCATENATE ) ;	//TYPE VARNAME1, VARNAME2, VARNAME3;
#define	VAR_ASSIGN( VARNAME, ... )					FE_ARG1_(  COUNT( __VA_ARGS__ ), CONCAT_VAR_ASSIGN, VARNAME, __VA_ARGS__ ); //VARNAME3=param1; VARNAME2=param2, VARNAME1=param3; 
#define	GENERATE_ASSIGN_VAR( TYPE, VARNAME, ... )	GENERATE_VARS_N( COUNT( __VA_ARGS__ ), TYPE, VARNAME );/*u32 a1=15, a2=7; GENERATE_ASSIGN_VAR( u32, a, 15, 7 ); */	\
													VAR_ASSIGN( VARNAME, __VA_ARGS__ ); //TYPE VARNAME1, VARNAME2, VARNAME3; VARNAME3=param1; VARNAME2=param2; VARNAME3=param1;
//============================================================================================
//--------------------------------------------------------------------------------------------
//------------------------	MACRO KERNELS ----------------------------------------------------
//--------------------------------------------------------------------------------------------
#define	_BOR( val )									| ( 0x1 << val ) 		//bit number or
#define	_BAND( val )								& ( 0x1 << val )		//bit number and
#define	_BANDNOT( val )								& ( ~( 0x1 << val ) )	//bit number and not
//--------------------------------------------------------------------------------------------
#define	ASM( instruction )							asm( STRINGIZE( instruction ) );
#define CAST( destPtr )								( destPtr )( const void* )
#define FUNC_ADDR( funcPtr )						( u32 )( void* )funcPtr
#define	read8( addr )								*( (  u8* )( addr ) )
#define	read16( addr )								*( ( u16* )( addr ) )
#define	read32( addr )								*( ( u32* )( addr ) )
#define read64( addr )								*( ( u64* )( addr ) )
#define	readN8( addr, size, arr_u8_Ptr )			{ for ( u32 i = 0x0; i < size; i+=1 ) *( (  u8* )( ( arr_u8_Ptr ) + i ) ) = *( (  u8* )( ( addr ) + i ) ); };
#define	readN16( addr, size, arr_u8_Ptr )			{ for ( u32 i = 0x0; i < size; i+=2 ) *( ( u16* )( ( arr_u8_Ptr ) + i ) ) = *( ( u16* )( ( addr ) + i ) ); };
#define	readN32( addr, size, arr_u8_Ptr )			{ for ( u32 i = 0x0; i < size; i+=4 ) *( ( u32* )( ( arr_u8_Ptr ) + i ) ) = *( ( u32* )( ( addr ) + i ) ); };
#define	readN64( addr, size, arr_u8_Ptr )			{ for ( u32 i = 0x0; i < size; i+=8 ) *( ( u64* )( ( arr_u8_Ptr ) + i ) ) = *( ( u64* )( ( addr ) + i ) ); }; //use only with 64b registers
#define	write8( addr, val )							*( (  u8* )( addr ) ) = (  u8 )( val );
#define	write16( addr, val )						*( ( u16* )( addr ) ) = ( u16 )( val );
#define	write32( addr, val )						*( ( u32* )( addr ) ) = ( u32 )( val );
#define write64( addr, val )						*( ( u64* )( addr ) ) = ( u64 )( val );
#define	write8IncPtr( addrPtr, val )				*( (  u8* )( addrPtr++ ) ) = (  u8 )( val );
#define	write16IncPtr( addrPtr, val )				*( ( u16* )( addrPtr++ ) ) = ( u16 )( val );
#define	write32IncPtr( addrPtr, val )				*( ( u32* )( addrPtr++ ) ) = ( u32 )( val );
#define	write64IncPtr( addrPtr, val )				*( ( u64* )( addrPtr++ ) ) = ( u64 )( val );
#define	writeN8( addr, size, arr_u8_Ptr )			{ for ( u32 i = 0x0; i < size; i+=1 ) *( (  u8* )( ( addr ) + i ) ) = *( (  u8* )( ( arr_u8_Ptr ) + i ) ); };
#define	writeN16( addr, size, arr_u8_Ptr )			{ for ( u32 i = 0x0; i < size; i+=2 ) *( ( u16* )( ( addr ) + i ) ) = *( ( u16* )( ( arr_u8_Ptr ) + i ) ); };
#define	writeN32( addr, size, arr_u8_Ptr )			{ for ( u32 i = 0x0; i < size; i+=4 ) *( ( u32* )( ( addr ) + i ) ) = *( ( u32* )( ( arr_u8_Ptr ) + i ) ); };
#define	writeN64( addr, size, arr_u8_Ptr )			{ for ( u32 i = 0x0; i < size; i+=8 ) *( ( u64* )( ( addr ) + i ) ) = *( ( u64* )( ( arr_u8_Ptr ) + i ) ); }; //use only with 64b registers
#define memset8( addrPtr, val, size )				{ u32 t;  u8* tPtr; tPtr = (  u8* )( void* )( addrPtr ); for ( t = 0x0; t < (size); t += 1 ) *tPtr++ = ( val ); };
#define memset16( addrPtr, val, size )				{ u32 t; u16* tPtr; tPtr = ( u16* )( void* )( addrPtr ); for ( t = 0x0; t < (size); t += 2 ) *tPtr++ = ( val ); };
#define memset32( addrPtr, val, size )				{ u32 t; u32* tPtr; tPtr = ( u32* )( void* )( addrPtr ); for ( t = 0x0; t < (size); t += 4 ) *tPtr++ = ( val ); };
#define memset64( addrPtr, val, size )				{ u32 t; u64* tPtr; tPtr = ( u64* )( void* )( addrPtr ); for ( t = 0x0; t < (size); t += 8 ) *tPtr++ = ( val ); };
#define	or8( addr, mask )							*( (  u8* )( addr ) ) |= (  u8 )( mask );
#define	or16( addr, mask )							*( ( u16* )( addr ) ) |= ( u16 )( mask );
#define	or32( addr, mask )							*( ( u32* )( addr ) ) |= ( u32 )( mask );
#define	or64( addr, mask )							*( ( u64* )( addr ) ) |= ( u64 )( mask );
#define	borN8( ... )								(  u8 )( 0x0 FOR_EACH_CUMMUlATIVE( _BOR, __VA_ARGS__ ) )
#define	borN16( ... )								( u16 )( 0x0 FOR_EACH_CUMMUlATIVE( _BOR, __VA_ARGS__ ) )
#define	borN32( ... )								( u32 )( 0x0 FOR_EACH_CUMMUlATIVE( _BOR, __VA_ARGS__ ) )
#define	borN64( ... )								( u64 )( 0x0 FOR_EACH_CUMMUlATIVE( _BOR, __VA_ARGS__ ) )
#define and8( addr, mask ) 							*( (  u8* )( addr ) ) &= (  u8 )( mask );
#define and16( addr, mask ) 						*( ( u16* )( addr ) ) &= ( u16 )( mask );
#define and32( addr, mask ) 						*( ( u32* )( addr ) ) &= ( u32 )( mask );
#define and64( addr, mask ) 						*( ( u64* )( addr ) ) &= ( u64 )( mask );
#define andNot8( addr, mask )						*( (  u8* )( addr ) ) &= (  u8 )~( mask );
#define andNot16( addr, mask )						*( ( u16* )( addr ) ) &= ( u16 )~( mask );
#define andNot32( addr, mask )						*( ( u32* )( addr ) ) &= ( u32 )~( mask );
#define andNot64( addr, mask )						*( ( u64* )( addr ) ) &= ( u64 )~( mask );
#define	bandNotN8( ... )							(  u8 )( 0x000000FF FOR_EACH_CUMMUlATIVE( _BANDNOT, __VA_ARGS__ ) )
#define	bandNotN16( ... )							( u16 )( 0x0000FFFF FOR_EACH_CUMMUlATIVE( _BANDNOT, __VA_ARGS__ ) )
#define	bandNotN32( ... )							( u32 )( 0xFFFFFFFF FOR_EACH_CUMMUlATIVE( _BANDNOT, __VA_ARGS__ ) )
#define	bandNotN64( ... )							( u64 )( 0xFFFFFFFFFFFFFFFF FOR_EACH_CUMMUlATIVE( _BANDNOT, __VA_ARGS__ ) )
#define not8( addr )								*( (  u8* )( addr ) ) =  ~( *( (  u8* )( addr ) ) );
#define not16( addr )								*( ( u16* )( addr ) ) =  ~( *( ( u16* )( addr ) ) );
#define not32( addr )								*( ( u32* )( addr ) ) =  ~( *( ( u32* )( addr ) ) );
#define not64( addr )								*( ( u64* )( addr ) ) =  ~( *( ( u64* )( addr ) ) );
#define	set8( addr )								*( (  u8* )( addr ) ) = (  u8 )0xFF;
#define	set16( addr )								*( ( u16* )( addr ) ) = ( u16 )0xFFFF;
#define	set32( addr )								*( ( u32* )( addr ) ) = ( u32 )0xFFFFFFFF;
#define	set64( addr )								*( ( u64* )( addr ) ) = ( u64 )0xFFFFFFFFFFFFFFFF;
#define	res8( addr )								*( (  u8* )( addr ) ) = (  u8 )0x0;
#define	res16( addr )								*( ( u16* )( addr ) ) = ( u16 )0x0;
#define	res32( addr )								*( ( u32* )( addr ) ) = ( u32 )0x0;
#define	res64( addr )								*( ( u64* )( addr ) ) = ( u64 )0x0;
#define bset8( addr, bitNo )						*( (  u8* )( addr ) ) |= (  u8 )( 0x1 << ( bitNo ) ); asm( "NOP" ); asm( "NOP" ); asm( "NOP" );
#define bset16( addr, bitNo )						*( ( u16* )( addr ) ) |= ( u16 )( 0x1 << ( bitNo ) ); asm( "NOP" ); asm( "NOP" ); asm( "NOP" );
#define bset32( addr, bitNo )						*( ( u32* )( addr ) ) |= ( u32 )( 0x1 << ( bitNo ) ); asm( "NOP" ); asm( "NOP" ); asm( "NOP" );	
#define bset64( addr, bitNo )						*( ( u64* )( addr ) ) |= ( u64 )( 0x1 << ( bitNo ) ); asm( "NOP" ); asm( "NOP" ); asm( "NOP" );	
#define	bsetN8( addr, ... )							*( (  u8* )( addr ) ) |= ( 0x0 FOR_EACH_CUMMUlATIVE( _BOR, __VA_ARGS__ ) );
#define	bsetN16( addr, ... )						*( ( u16* )( addr ) ) |= ( 0x0 FOR_EACH_CUMMUlATIVE( _BOR, __VA_ARGS__ ) );
#define	bsetN32( addr, ... )						*( ( u32* )( addr ) ) |= ( 0x0 FOR_EACH_CUMMUlATIVE( _BOR, __VA_ARGS__ ) );
#define	bsetN64( addr, ... )						*( ( u64* )( addr ) ) |= ( 0x0 FOR_EACH_CUMMUlATIVE( _BOR, __VA_ARGS__ ) );
#define	bres8( addr, bitNo )						*( (  u8* )( addr ) ) &= (  u8 )~( 0x1 << ( bitNo ) ); asm( "NOP" );	//execution time of bres macro equals to bset
#define	bres16( addr, bitNo )						*( ( u16* )( addr ) ) &= ( u16 )~( 0x1 << ( bitNo ) ); asm( "NOP" );	//execution time of bres macro equals to bset
#define	bres32( addr, bitNo )						*( ( u32* )( addr ) ) &= ( u32 )~( 0x1 << ( bitNo ) ); asm( "NOP" );	//execution time of bres macro equals to bset
#define	bres64( addr, bitNo )						*( ( u64* )( addr ) ) &= ( u64 )~( 0x1 << ( bitNo ) ); asm( "NOP" );	//execution time of bres macro equals to bset
#define	bresN8( addr, ... )							*( (  u8* )( addr ) ) &= ( 0xFFFFFFFF FOR_EACH_CUMMUlATIVE( _BANDNOT, __VA_ARGS__ ) );
#define	bresN16( addr, ... )						*( ( u16* )( addr ) ) &= ( 0xFFFFFFFF FOR_EACH_CUMMUlATIVE( _BANDNOT, __VA_ARGS__ ) );
#define	bresN32( addr, ... )						*( ( u32* )( addr ) ) &= ( 0xFFFFFFFF FOR_EACH_CUMMUlATIVE( _BANDNOT, __VA_ARGS__ ) );
#define	bresN64( addr, ... )						*( ( u64* )( addr ) ) &= ( 0xFFFFFFFF FOR_EACH_CUMMUlATIVE( _BANDNOT, __VA_ARGS__ ) );
#define	waitBset8( addr, bitNo )					while( (*( (  u8* )( addr ) ) & (  u8 )( 0x1 << ( bitNo ) )) != (  u8 )( 0x1 << ( bitNo ) ) );
#define	waitBset16( addr, bitNo )					while( (*( ( u16* )( addr ) ) & ( u16 )( 0x1 << ( bitNo ) )) != ( u16 )( 0x1 << ( bitNo ) ) );
#define	waitBset32( addr, bitNo )					while( (*( ( u32* )( addr ) ) & ( u32 )( 0x1 << ( bitNo ) )) != ( u32 )( 0x1 << ( bitNo ) ) );
#define	waitBset64( addr, bitNo )					while( (*( ( u64* )( addr ) ) & ( u64 )( 0x1 << ( bitNo ) )) != ( u64 )( 0x1 << ( bitNo ) ) );
#define	waitBres8( addr, bitNo )					while( (*( (  u8* )( addr ) ) & (  u8 )( 0x1 << ( bitNo ) )) != (  u8 )0x0 );
#define	waitBres16( addr, bitNo )					while( (*( ( u16* )( addr ) ) & ( u16 )( 0x1 << ( bitNo ) )) != ( u16 )0x0 );
#define	waitBres32( addr, bitNo )					while( (*( ( u32* )( addr ) ) & ( u32 )( 0x1 << ( bitNo ) )) != ( u32 )0x0 );
#define	waitBres64( addr, bitNo )					while( (*( ( u64* )( addr ) ) & ( u64 )( 0x1 << ( bitNo ) )) != ( u64 )0x0 );
#define bval8( addr, bitNo )						( ( *(  u8* )( addr ) >> ( bitNo ) ) & 0x1 )
#define bval16( addr, bitNo )						( ( *( u16* )( addr ) >> ( bitNo ) ) & 0x1 )
#define bval32( addr, bitNo )						( ( *( u32* )( addr ) >> ( bitNo ) ) & 0x1 )
#define bval64( addr, bitNo )						( ( *( u64* )( addr ) >> ( bitNo ) ) & 0x1 )
//bit negations:
#define	bnot8( addr, bitNo )						read8( addr ) = ( ( ~( read8( addr ) & ( 0x1 << bitNo ) ) ) & ( 0x1 << bitNo ) | \
																		( read8( addr ) & ( ~( 0x1 << bitNo ) ) ) )
#define	bnot16( addr, bitNo )						read16( addr ) = ( ( ~( read16( addr ) & ( 0x1 << bitNo ) ) ) & ( 0x1 << bitNo ) | \
																		( read16( addr ) & ( ~( 0x1 << bitNo ) ) ) )											
#define	bnot32( addr, bitNo )						read32( addr ) = ( ( ~( read32( addr ) & ( 0x1 << bitNo ) ) ) & ( 0x1 << bitNo ) | \
																		( read32( addr ) & ( ~( 0x1 << bitNo ) ) ) )
#define	bnot64( addr, bitNo )						read64( addr ) = ( ( ~( read64( addr ) & ( 0x1 << bitNo ) ) ) & ( 0x1 << bitNo ) | \
																		( read64( addr ) & ( ~( 0x1 << bitNo ) ) ) )					
#define	bnotN8( addr, ... )							read8( addr ) = ( ( ~( read8( addr ) & ( borN8( __VA_ARGS__ ) ) ) ) & ( borN8( __VA_ARGS__ ) ) | \
																		( read8( addr ) & ( ~( borN8( __VA_ARGS__ ) ) ) ) )
#define	bnotN16( addr, ... )						read16( addr ) = ( ( ~( read16( addr ) & ( borN16( __VA_ARGS__ ) ) ) ) & ( borN16( __VA_ARGS__ ) ) | \
																		( read16( addr ) & ( ~( borN16( __VA_ARGS__ ) ) ) ) )													
#define	bnotN32( addr, ... )						read32( addr ) = ( ( ~( read32( addr ) & ( borN32( __VA_ARGS__ ) ) ) ) & ( borN32( __VA_ARGS__ ) ) | \
																		( read32( addr ) & ( ~( borN32( __VA_ARGS__ ) ) ) ) )
#define	bnotN64( addr, ... )						read64( addr ) = ( ( ~( read64( addr ) & ( borN64( __VA_ARGS__ ) ) ) ) & ( borN64( __VA_ARGS__ ) ) | \
																		( read64( addr ) & ( ~( borN64( __VA_ARGS__ ) ) ) ) )
//timeout'ed procedures
#define	waitBsetTimeout8( addr, bitNo, timeout )			{ int t; t = (timeout); while(( (*( (  u8* )( addr ) ) & (  u8 )( 0x1 << ( bitNo ) )) != (  u8 )( 0x1 << ( bitNo ) ) ) && ( t-- )); };
#define	waitBsetTimeout16( addr, bitNo, timeout )			{ int t; t = (timeout); while(( (*( ( u16* )( addr ) ) & ( u16 )( 0x1 << ( bitNo ) )) != ( u16 )( 0x1 << ( bitNo ) ) ) && ( t-- )); };
#define	waitBsetTimeout32( addr, bitNo, timeout )			{ int t; t = (timeout); while(( (*( ( u32* )( addr ) ) & ( u32 )( 0x1 << ( bitNo ) )) != ( u32 )( 0x1 << ( bitNo ) ) ) && ( t-- )); };
#define	waitBsetTimeout64( addr, bitNo, timeout )			{ int t; t = (timeout); while(( (*( ( u64* )( addr ) ) & ( u64 )( 0x1 << ( bitNo ) )) != ( u64 )( 0x1 << ( bitNo ) ) ) && ( t-- )); };
#define	waitBresTimeout8( addr, bitNo, timeout )			{ int t; t = (timeout); while(( (*( (  u8* )( addr ) ) & (  u8 )( 0x1 << ( bitNo ) )) != (  u8 )0x0 ) && ( t-- )); };
#define	waitBresTimeout16( addr, bitNo, timeout )			{ int t; t = (timeout); while(( (*( ( u16* )( addr ) ) & ( u16 )( 0x1 << ( bitNo ) )) != ( u16 )0x0 ) && ( t-- )); };
#define	waitBresTimeout32( addr, bitNo, timeout )			{ int t; t = (timeout); while(( (*( ( u32* )( addr ) ) & ( u32 )( 0x1 << ( bitNo ) )) != ( u32 )0x0 ) && ( t-- )); };
#define	waitBresTimeout64( addr, bitNo, timeout )			{ int t; t = (timeout); while(( (*( ( u64* )( addr ) ) & ( u64 )( 0x1 << ( bitNo ) )) != ( u64 )0x0 ) && ( t-- )); };
//32bit Read Modify Write's
#define	rmw( addr, bitNo, bitVal )					*( ( u32* )( addr ) ) &= CONCATENATE( RS, bitNo ); *( ( u32* )( addr ) ) |= ( bitVal << bitNo );
#define	rmw2b( addr,  mask_2b, mask_shift )			*( ( u32* )( addr ) ) = ( *( ( u32* )( addr ) ) & ( u32 )( ~(    0x3 << ( mask_shift ) ) ) ) | ( u32 )(  ( mask_2b ) << ( mask_shift ) );
#define	rmw3b( addr,  mask_3b, mask_shift )			*( ( u32* )( addr ) ) = ( *( ( u32* )( addr ) ) & ( u32 )( ~(    0x7 << ( mask_shift ) ) ) ) | ( u32 )(  ( mask_3b ) << ( mask_shift ) );
#define	rmw4b( addr,  mask_4b, mask_shift )			*( ( u32* )( addr ) ) = ( *( ( u32* )( addr ) ) & ( u32 )( ~(    0xF << ( mask_shift ) ) ) ) | ( u32 )(  ( mask_4b ) << ( mask_shift ) );
#define	rmw5b( addr,  mask_5b, mask_shift )			*( ( u32* )( addr ) ) = ( *( ( u32* )( addr ) ) & ( u32 )( ~(   0x1F << ( mask_shift ) ) ) ) | ( u32 )(  ( mask_5b ) << ( mask_shift ) );
#define	rmw6b( addr,  mask_6b, mask_shift )			*( ( u32* )( addr ) ) = ( *( ( u32* )( addr ) ) & ( u32 )( ~(   0x3F << ( mask_shift ) ) ) ) | ( u32 )(  ( mask_6b ) << ( mask_shift ) );
#define	rmw7b( addr,  mask_7b, mask_shift )			*( ( u32* )( addr ) ) = ( *( ( u32* )( addr ) ) & ( u32 )( ~(   0x7F << ( mask_shift ) ) ) ) | ( u32 )(  ( mask_7b ) << ( mask_shift ) );
#define	rmw8b( addr,  mask_8b, mask_shift )			*( ( u32* )( addr ) ) = ( *( ( u32* )( addr ) ) & ( u32 )( ~(   0xFF << ( mask_shift ) ) ) ) | ( u32 )(  ( mask_8b ) << ( mask_shift ) );
#define	rmw9b( addr,  mask_9b, mask_shift )			*( ( u32* )( addr ) ) = ( *( ( u32* )( addr ) ) & ( u32 )( ~(  0x1FF << ( mask_shift ) ) ) ) | ( u32 )(  ( mask_9b ) << ( mask_shift ) );
#define	rmw10b( addr, mask_10b, mask_shift )		*( ( u32* )( addr ) ) = ( *( ( u32* )( addr ) ) & ( u32 )( ~(  0x3FF << ( mask_shift ) ) ) ) | ( u32 )( ( mask_10b ) << ( mask_shift ) );
#define	rmw11b( addr, mask_11b, mask_shift )		*( ( u32* )( addr ) ) = ( *( ( u32* )( addr ) ) & ( u32 )( ~(  0x7FF << ( mask_shift ) ) ) ) | ( u32 )( ( mask_11b ) << ( mask_shift ) );
#define	rmw12b( addr, mask_12b, mask_shift )		*( ( u32* )( addr ) ) = ( *( ( u32* )( addr ) ) & ( u32 )( ~(  0xFFF << ( mask_shift ) ) ) ) | ( u32 )( ( mask_12b ) << ( mask_shift ) );
#define	rmw13b( addr, mask_13b, mask_shift )		*( ( u32* )( addr ) ) = ( *( ( u32* )( addr ) ) & ( u32 )( ~( 0x1FFF << ( mask_shift ) ) ) ) | ( u32 )( ( mask_13b ) << ( mask_shift ) );
#define	rmw14b( addr, mask_14b, mask_shift )		*( ( u32* )( addr ) ) = ( *( ( u32* )( addr ) ) & ( u32 )( ~( 0x3FFF << ( mask_shift ) ) ) ) | ( u32 )( ( mask_14b ) << ( mask_shift ) );
#define	rmw15b( addr, mask_15b, mask_shift )		*( ( u32* )( addr ) ) = ( *( ( u32* )( addr ) ) & ( u32 )( ~( 0x7FFF << ( mask_shift ) ) ) ) | ( u32 )( ( mask_15b ) << ( mask_shift ) );
#define	rmw16b( addr, mask_16b, mask_shift )		*( ( u32* )( addr ) ) = ( *( ( u32* )( addr ) ) & ( u32 )( ~( 0xFFFF << ( mask_shift ) ) ) ) | ( u32 )( ( mask_16b ) << ( mask_shift ) );
#define	WAIT_ENABLE									{ vu32 i; i = 0xFF; while( i-- ); };
#define	SIZE( arr )									( ( u32 )( sizeof( arr ) / sizeof( arr[ 0 ] ) ) )
#define COPY( destArr, srcArr )						{ while( *destArr++ = *srcArr++ ); };
#define	COPY8_N( destPtr, srcPtr, N )				{ u32 i; i = ( N ); while( i-- ) *( (  u8* )( destPtr++ ) ) = *( (  u8* )( srcPtr++ ) ); };
#define	COPY16_N( destPtr, srcPtr, N )				{ u32 i; i = ( N ); while( i-- ) *( ( u16* )( destPtr++ ) ) = *( ( u16* )( srcPtr++ ) ); };
#define	COPY32_N( destPtr, srcPtr, N )				{ u32 i; i = ( N ); while( i-- ) *( ( u32* )( destPtr++ ) ) = *( ( u32* )( srcPtr++ ) ); };
#define	COPY64_N( destPtr, srcPtr, N )				{ u32 i; i = ( N ); while( i-- ) *( ( u64* )( destPtr++ ) ) = *( ( u64* )( srcPtr++ ) ); };
#define	__NOP										asm( "NOP" );
#define	__WFE										asm( "WFE" );
#define	__WFI										asm( "WFI" );
#define	__DSB										asm( "DSB" ); //wait clock-enable
#define	__ISB										asm( "ISB" );
#define __BKPT										asm( "BKPT #0" );
#define	__INCLUDE_GDB								//dummy replacement define for __GDB(...) macro
#define	__GDB(...)									//declaration at gdb_debug.c for conditional preprocessing - single usage of macro per source file!
#define	__FPU_ENABLE								or32( SCB_CPACR, (3UL << 20) | (3UL << 22) ); //cortex-Mx generic addr
#define	BB_PERIPH_BASE								0x40000000	//single bit
#define BB_PERIPH_ALIAS								0x42000000	//4B corresponding to single bit
#define	BB_ADDR( addr, bitNo )						BB_PERIPH_ALIAS + (( ( addr ) - BB_PERIPH_BASE) * 0x20) + ( ( bitNo ) * 0x4 );
#define	BBset( BBaliasAddr )						*( ( u32* )( BBaliasAddr ) ) = 0x1;
#define	BBres( BBaliasAddr )						*( ( u32* )( BBaliasAddr ) ) = 0x0;
//====	CLK
int SysTick_Config( u32 systicks ) 	//1s resolution up to 16MHz clock
{	if ( systicks  > 0xFFFFFF ) 	//24bit resolution timer
		return -1;
	read32( SYST_CSR )  = ( 0x1 << 0x2 );						//CPU clock source
	read32( SYST_RVR )  = systicks;								//reload value
	read32( SYST_CVR )  = 0x0;									//reset current value
	read32( SYST_CSR ) |=  ( 0x1 << 0x1 ) | ( 0x1 << 0x0 );  	//Systick Handler | enable
	return 0;
};
u32 SYSCLK;
#if 													defined STM32F411
	#define	HSI_INTERNAL_CLK	0x1
	#define	HSE_EXTERNAL_CLK	0x2
	#define	HSI_FREQ			16000000 	//~16MHz after calibration
	#define	HSE_FREQ			16000000 	//16MHz
	#define	CPU_HSI_16MHz		0x01		// no waitStates!
	u32 SysClk( u8 clkSrc, u32 cpuFreq )
	{	SYSCLK = HSI_FREQ;
		switch ( cpuFreq )
		{	default:
				break;
			case CPU_HSI_16MHz:	
				SYSCLK = 16000000;
				break;	
		};
		return SYSCLK;
	};
#endif


u32 d_i, d_us;
void wait_us( u32 t )
{	d_us = t * ( SYSCLK / ( 1000000 * 3 ) ); //3clks poor accuracy
	while( d_us-- );
};

void wait_ms( u32 t )
{	for ( d_i = 0x0; d_i < t; d_i++ ) wait_us( 1000 );
};

//======================================================================
//============================ stdio.h =================================
//======================================================================
char Representation[] 	__attribute__((section(".text#")))
						= "0123456789ABCDEF";
char buffer[50], *bufferPtr;
char *convert(unsigned int num, unsigned int base) 
{ 	bufferPtr = &buffer[49]; 
	*bufferPtr = '\0'; 
	do 
	{ 	*--bufferPtr = Representation[num % base]; 
		num /= base; 
	}while(num != 0); 
	return bufferPtr; 
};

unsigned strlen( char* buf )
{	unsigned n = 0x0;
	while( *buf++ )
		n++;
	return n;
};

char *fBuffPtr, *fBuffConv;
char* ftoa( float f, int precision )
{	int l, mul = 0x1;
	while( precision-- )
		mul *= 0xA;
	fBuffPtr = &buffer[ 0 ];
	l = ( int )f;
	if ( l < 0 )
	{	*fBuffPtr++ = '-';
		l = -l;
		f = -f;
	};
	fBuffConv = convert( l, 10 );
	while ( *fBuffPtr++ = *fBuffConv++ ); 
	fBuffPtr--;
	*fBuffPtr++ = '.';
	l = ( f - (float)( l ) ) * ( float )mul;
	fBuffConv = convert( l, 10 );
	while ( *fBuffPtr++ = *fBuffConv++ );
	*fBuffPtr = '\0';
	return &buffer[ 0 ];
};
char* cPtr, *rPtr;
char* itoa( int val, char *str, int base  )
{	if ( val < 0x0 )
	{	*str++ = '-';
		val = -val;
	};
	cPtr = convert( val, base );
	rPtr = cPtr;
	while( *str++ = *cPtr++ );
	return rPtr;
};

void sprintf( char* buf, char *c, ... )	//float must be passed via pointer!!!
{  	char* tmpPtr;
	unsigned fPrecision = 0x2;
	int iTmp;
	iTmp=0x0;
    va_list lst;
    va_start( lst, c );
    while( *c != '\0' )
    { 	if( *c != '%' )
        {   *buf++ = *c++;
            if ( *c == '\0' ) *buf = '\0';
            continue;
        };
        c++;if( *c == '\0' ) { *buf = '\0'; break; };
format:
		switch( *c )
		{	default: 
				buf++;
				break;
			case 's':
				tmpPtr = va_arg( lst, char* );
				while( *buf++ = *tmpPtr++ );
				break;
			case 'c': 
				*buf++ = ( char )va_arg( lst, int );
				break;
			case '.':
				fPrecision = *++c - '0';
				c++;
				goto format;
				break;
			case 'f':
				tmpPtr = ftoa( *va_arg( lst, float* ), fPrecision );//only float pointer
				while( *buf++ = *tmpPtr++ );
				fPrecision = 0x2;
				break;
			case 'p':
			case 'u':
				tmpPtr = convert( va_arg( lst, unsigned ), 10 );
				while( *buf++ = *tmpPtr++ );
				break;
			case 'd':
			case 'i':
				iTmp = ( int )va_arg( lst, int );
				if ( iTmp < 0 ) { *buf++ = '-';iTmp = -iTmp; };
				tmpPtr = convert( iTmp, 10 );
				while( *buf++ = *tmpPtr++ );
				break;
			case 'x':
			case 'X':
				tmpPtr = convert( va_arg( lst, unsigned ), 16 );
				while( *buf++ = *tmpPtr++ );
				break;
		}; //switch (*c)
		buf--;
		c++;
    };//while(*c!=0x0)
    *++buf = 0x0;
    va_end( lst );
};
//======================================================================
//======================================================================
//======================================================================
//=======================================================================================
//definitions of memory handling functions:
int   memcmp( void *ptr1, void *ptr2, unsigned int num );
void* memset( void *ptr, int value, unsigned int num ) ;
void* memcpy( void *destinationPtr, void *sourcePtr, unsigned int num );
void* memmove( void *destinationPtr, void *sourcePtr, unsigned int num );
void* memchr( void *ptr, int value, unsigned int num );
//=======================================================================================
//all variables are global
#define MEMMOVE_BUFSIZE	0x10
#define CHARACTER_MASK	0xFFFFFF00
#define memPtr_i1	memPtr_iDst
#define memPtr_i2	memPtr_iSrc
#define memPtr_c1	memPtr_cDst
#define memPtr_c2	memPtr_cSrc
#define mem_i		mem_valueInt
unsigned int 	*memPtr_iSrc, *memPtr_iDst,
				mem_noInts, mem_valueInt;
unsigned char 	*memPtr_cSrc, *memPtr_cDst, *memPtr_buf,
				mem_buf[ MEMMOVE_BUFSIZE ];

//=======================================================================================
int memcmp( void *ptr1, void *ptr2, unsigned int num )
{	memPtr_i1 = (unsigned int*)ptr1;
	memPtr_i2 = (unsigned int*)ptr2;
	mem_noInts = num >> 2; //divide by 4
	while (mem_noInts > 0)
	{	if (*memPtr_i1 != *memPtr_i2)
		{	memPtr_c1 = (unsigned char *)memPtr_i1;
			memPtr_c2 = (unsigned char *)memPtr_i2;
			for ( mem_i = 0x0; mem_i < sizeof( int ); mem_i++ )
			{	if ( *(memPtr_c1 + mem_i) != *(memPtr_c2 + mem_i) )
					return ( (int)*(memPtr_c1 + mem_i) - (int)*(memPtr_c2 + mem_i) );
			};
		};
		mem_noInts--;
		memPtr_i1++;
		memPtr_i2++;
	};
	mem_noInts = num >> 2; //divide by 4
	num -= mem_noInts << 0x2; //reduce num of int number
	if ( mem_noInts > 0x1 ) //if (mem_noInts > 1)
	{	--memPtr_i1;
		--memPtr_i2;
	};
	//byte comparision of unaligned rest
	memPtr_c1 = (unsigned char *)memPtr_i1;
	memPtr_c2 = (unsigned char *)memPtr_i2;
	while (num > 0)
	{	if (*memPtr_c1 != *memPtr_c2)
			return (*memPtr_c1 - *memPtr_c2);
		num--;
		memPtr_c1++;
		memPtr_c2++;
	};
	return 0;
};

//=======================================================================================
void* memset( void *ptr, int value, unsigned int num )
{	memPtr_i1 = (unsigned int*)ptr;
	mem_noInts = num >> 0x2;
	//====(value &= 0xFF) || (value &= 0xFFFFFFFF)====
	if ( (value & CHARACTER_MASK) == 0x0 ) //set int size with character
	{	mem_valueInt  = (unsigned int)value << 0x00;
		mem_valueInt |= (unsigned int)value << 0x08;
		mem_valueInt |= (unsigned int)value << 0x10;
		mem_valueInt |= (unsigned int)value << 0x18;
	};
	while( mem_noInts-- )
		*memPtr_i1++ = mem_valueInt;
	mem_noInts = num >> 0x2;
	num -= mem_noInts << 0x2;	//reduce num of ints size number
	if ( mem_noInts > 0x1 ) 	//if (mem_noInts > 1)
		memPtr_i1--;
	//byte memory set with value of unaligned rest
	memPtr_c1 = (unsigned char *)memPtr_i1;
	while( num-- )
		*memPtr_c1++ = (unsigned char)value;
	return ptr;
};

//=======================================================================================
void* memcpy( void *destinationPtr, void *sourcePtr, unsigned int num )
{	memPtr_iDst = (unsigned int *)destinationPtr;
	memPtr_iSrc = (unsigned int *)sourcePtr;
	mem_noInts = num >> 0x2; //divide by 4
	while( mem_noInts-- )
		*memPtr_iDst++ = *memPtr_iSrc++;
	mem_noInts = num >> 0x2;
	num -= mem_noInts << 0x2;	//reduce num of ints size number
	if ( mem_noInts > 0x1 ) 	//if (mem_noInts > 1)
	{	memPtr_iDst--;
		memPtr_iSrc--;
	};
	//byte memory move
	memPtr_cSrc = (unsigned char *)memPtr_iSrc;
	memPtr_cDst = (unsigned char *)memPtr_iDst;
	while( num-- )
		*memPtr_cDst++ = *memPtr_cSrc++;
	return destinationPtr;
};

//=======================================================================================
void* memmove( void *destinationPtr, void *sourcePtr, unsigned int num )
{	if ( num > MEMMOVE_BUFSIZE )	//num<MEMMOVE_BUFSIZE
		return (void*)-1;
	memPtr_buf = mem_buf;
	memPtr_cSrc = (unsigned char *)sourcePtr;
	memPtr_iDst = (unsigned int *)destinationPtr;
	memPtr_iSrc = (unsigned int *)sourcePtr;
	mem_noInts = num;
	//get data into memmove buffer
	while( mem_noInts-- )
		*memPtr_buf++ = *memPtr_cSrc++;
	//copuy into dst from buffer via intPtr
	memPtr_iSrc = (unsigned int *)mem_buf;
	mem_noInts = num >> 0x2; //divide by 4
	while( mem_noInts-- )
		*memPtr_iDst++ = *memPtr_iSrc++;
	mem_noInts = num >> 0x2;
	num -= mem_noInts << 0x2;	//reduce num of ints size number
	if ( (num >> 0x2) > 0x1 ) 	//if (mem_noInts > 1)
	{	memPtr_iDst--;
		memPtr_iSrc--;
	};
	//byte memory move
	memPtr_cSrc = (unsigned char *)memPtr_iSrc;
	memPtr_cDst = (unsigned char *)memPtr_iDst;
	while( num-- )
		*memPtr_cDst++ = *memPtr_cSrc++;
	return destinationPtr;
};

//=======================================================================================
void* memchr( void *ptr, int value, unsigned int num )
{	memPtr_cSrc = (unsigned char *)ptr;
	mem_noInts = num;
	mem_i = 0x0;
	while( (mem_noInts--) && (*memPtr_cSrc++ != (unsigned char)value) )
		mem_i++;
	if ( mem_i == num )
		return 0x0;
	return (void*)--memPtr_cSrc;
};
//======================================================================
//======================================================================
//======================================================================
