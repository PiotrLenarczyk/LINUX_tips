#include "stdlib.h"
#include "stdarg.h"

#include "stm32xxxx_regs.c"
#include "defaults.c" //next line must be present
__INCLUDE_GDB
//====
int main( void );
void HardFaultHandler( void );
u32* vector_table[] __attribute__((section(".vector_table"))) =
{	( u32* )RAM_END,			//initial SP
	( u32* )main,				//Reset_Handler
	( u32* )HardFaultHandler, 	//NMI
	( u32* )HardFaultHandler 	//HardFault
};

//globals
u32 i;

//functions
void HardFaultHandler( void ){ while( 1 ); };

//======================================================================
//								MAIN
//======================================================================
int main( void )
{	i = 0x12;
	SysClk( HSI_INTERNAL_CLK, CPU_HSI_16MHz );
	__FPU_ENABLE 
	//enable CLK's
#if defined STM32F411
	//LED2 - PA5; BUTTON1 - PC13
	//GPIOA | GPIOC enable
	bsetN8( RCC_AHB1ENR, 0x0, 0x2 ); __DSB;
#endif
	//PA5 output
	bset32( GPIOA_MODER, 0xA );
	//PA5 pullUp
	bset32( GPIOA_PUPDR, 0xA );
	bset16( GPIOA_ODR, 0x5 ); //LED on
	__GDB( x GPIOA_ODR; p i );	//trivial GDB arguments passing via temporary compilation
	while( 1 )
	{	not16( GPIOA_ODR );
		wait_ms( 500 );
	};
};
//======================================================================
//======================================================================
//======================================================================
