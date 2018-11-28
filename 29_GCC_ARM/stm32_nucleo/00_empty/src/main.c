#define RAM_END 0x20003FFF
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
// malloc: _srbk() + necessary linker entries: _end;__HEAP_START)
//%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%%
typedef char* caddr_t;
#ifndef NULL
	#define NULL ( void* )RAM_END
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
#include "stdio.h"
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
typedef	volatile float vf;
#if defined STM32F411
	//====	STM32F411
	#define AHB1_RCC		0x40023800
	#define	RCC_AHB1ENR		0x40023830  
	//LED2 - PA5
	#define GPIOA_MODER 	0x40020000  
	#define GPIOA_PUPDR		0x4002000C 
	#define GPIOA_IDR		0x40020010
	#define GPIOA_ODR		0x40020014  
	//BUTTON1 - PC13
	#define GPIOC_MODER 	0x40020800 
	#define GPIOC_PUPDR		0x4002080C 
	#define GPIOC_IDR		0x40020810
	#define GPIOC_ODR		0x40020814  
#endif
#define	read8( addr )			*( u8* )addr
#define	read16( addr )			*( u16* )addr
#define	read32( addr )			*( u32* )addr
#define read64( addr )			*( u64* )addr
#define bset( addr, bitNo )		*( u32* )addr |= ( u32 )( 0x1 << bitNo );
#define	bres( addr, bitNo )		*( u32* )addr &= ( u32 )~( 0x1 << bitNo );
#define	or32( addr, mask )		*( u32* )addr |= ( u32 )( mask );
#define and32( addr, mask )		*( u32* )addr &= ( u32 )~( mask );
#define	__DSB()					__asm__( "DSB" );
#define	__ISB()					__asm__( "ISB" );
#define __BKPT()				__asm__( "BKPT" );
//====

int main( void );
void HardFaultHandler( void );
u32* vector_table[] __attribute__((section(".vector_table"))) =
{	( u32* )RAM_END,	//initial SP
	( u32* )main,		//Reset_Handler
	( u32* )HardFaultHandler, //NMI
	( u32* )HardFaultHandler, //HardFault
};

//globals
u32 i;

//functions
void wait ( u32 );
void blink( void );
void pushButton( void );
void HardFaultHandler( void ){ while( 1 ); };

//======================================================================
//								MAIN
//======================================================================
int main( void )
{	
	#define SCB_CPACR		0xE000ED88 //##FPU enable
	or32( SCB_CPACR, (3UL << 20) | (3UL << 22) );
	//enable CLK's
#if defined STM32F411
	read32( RCC_AHB1ENR ) |= ( 0x1 << 0x0 ) | ( 0x1 << 0x2 ); wait( 0xFFF );
#endif
	//PA5 output
	bset( GPIOA_MODER, 0xA );
	//PA5 pullUp
	bset( GPIOA_PUPDR, 0xA );

	float a = 14.1f;
	u32 b = a;
	__BKPT();

	while( 1 )
	{	
		blink();
		//pushButton();
	};
};
//======================================================================
//======================================================================
//======================================================================

void wait( u32 t )
{	for ( i = 0x0; i < t; i++ )
		i = i;
};

void blink( void )
{	bset( GPIOA_ODR, 0x5 );
	wait( 0xFFFFF );
	bres( GPIOA_ODR, 0x5 );
	wait( 0xFFFFF );
};

void pushButton( void )
{	if ( ( read16( GPIOC_IDR )  & ( 0x1 << 13 ) ) >> 13 == 0x0 )
	{	bset( GPIOA_ODR, 0x5 );
	}
	else
		bres( GPIOA_ODR, 0x5 );
};
