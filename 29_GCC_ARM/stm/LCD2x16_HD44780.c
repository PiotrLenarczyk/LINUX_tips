//LCD2x16_InitPins():
//	PC14	/* RS - Register select pin */
//	PC15	/* E - Enable pin */
//	PC0		/* D4 - Data 4 pin */
//	PC1		/* D5 - Data 5 pin */
//	PC2		/* D6 - Data 6 pin */
//	PC3		/* D7 - Data 7 pin */
#define		LCD2x16_RS_PIN				S14
#define		LCD2x16_E_PIN				S15
#define		LCD2x16_D4_PIN				S0
#define		LCD2x16_D5_PIN				S1
#define		LCD2x16_D6_PIN				S2
#define		LCD2x16_D7_PIN				S3
#define 	FIRST_LINE					0x0
#define		SECOND_LINE					0x40

u16 out4b;
void LCD2x16_setCmd( u16 inCmd )
{	out4b = (( inCmd >> 4 ) & 0xF);
	read16( GPIOC_ODR ) = ( u16 )( out4b | LCD2x16_E_PIN );
	wait_us( 1 );
	read16( GPIOC_ODR ) = ( u16 )( out4b  );
	wait_us( 50 );
		out4b = (( inCmd >> 0 ) & 0xF);
		read16( GPIOC_ODR ) = ( u16 )( out4b | LCD2x16_E_PIN );
		wait_us( 1 );
		read16( GPIOC_ODR ) = ( u16 )( out4b  );
		wait_us( 1600 );
};

void LCD2x16_setData( u16 inData )
{	out4b = (( inData >> 4 ) & 0xF);
	read16( GPIOC_ODR ) = ( u16 )( out4b | LCD2x16_E_PIN | LCD2x16_RS_PIN );
	wait_us( 1 );
	read16( GPIOC_ODR ) = ( u16 )( out4b | LCD2x16_RS_PIN );
	wait_us( 1 );
		out4b = (( inData >> 0 ) & 0xF);
		read16( GPIOC_ODR ) = ( u16 )( out4b | LCD2x16_E_PIN | LCD2x16_RS_PIN );
		wait_us( 1 );
		read16( GPIOC_ODR ) = ( u16 )( out4b | LCD2x16_RS_PIN );
		wait_us( 50 );
};

void LCD2x16_setPosition( u8 LCDposition )	//0x0 first line; 0x40 second line;
{	LCD2x16_setCmd( ( LCDposition & 0x7F ) + 0x80 );
};

void LCD2x16_setString( const void* inPtr, u8 LCDposition ) //LCDposition=0x0 - autoincement position
{	char* inStrPtr = ( char* )inPtr;
	if ( LCDposition != 0x0 )
		LCD2x16_setPosition( LCDposition );
	while( *inStrPtr != 0x0 )
		LCD2x16_setData( *inStrPtr++ );
};

void LCD2x16_reset( u8 setPosition )
{	LCD2x16_setCmd( 0x33 );	//4bit init part 
	LCD2x16_setCmd( 0x32 );	//4bit init 
	LCD2x16_setCmd( 0x28 ); //4bit mode; 2 lines; 5x7
	LCD2x16_setCmd( 0x0F ); //disp ON; cursor ON blink
	LCD2x16_setCmd( 0x01 ); //clear disp
	LCD2x16_setCmd( 0x06 );	//entry mode; inc position; no disp shift
	if ( setPosition != 0x0 )
		LCD2x16_setPosition( setPosition );
};

void LCD2x16_clear( void )
{	LCD2x16_reset( 0x0 );
};

void printf( char* fmt, ... )//float passed only by pointer
{	LCD2x16_reset( 0x0 );
	va_list ap;
	char *p, *strBuf;
	char buf[ 0x20 ];
	int ival;
	u32 uval;
	float* fval;
	va_start( ap, fmt );
	if ( *fmt == 0x0 ) //empty string
	{	va_end( ap );
		return;
	};
	for( p = fmt; *p; p++ )
	{	if ( *p == '\n' )
			{	LCD2x16_setPosition( SECOND_LINE );
				continue;
			};
		if ( *p != '%' )
		{	LCD2x16_setData( *p );
			continue;
		};
		switch ( *++p )
		{	case 'f':
				fval = va_arg( ap, float* );
				sprintf( buf, "%.2f", fval );
				LCD2x16_setString( buf, 0x0 );
				break;
			case 'u':
				uval = va_arg( ap, u32 );
				LCD2x16_setString( convert( uval, 10 ), 0x0 );
				break;
			case 'i':
			case 'd':
				ival = va_arg( ap, int );
				if ( ival < 0 )
				{	LCD2x16_setString( "-", 0x0 );
					ival = -ival;
					LCD2x16_setString( convert( ival, 10 ), 0x0 );
					break;
				}else
					LCD2x16_setString( convert( ival, 10 ), 0x0 );
				break;
			case 's':
				strBuf = va_arg( ap, char* );
				LCD2x16_setString( strBuf, 0x0 );
				break;
			case 'x':
			case 'X':
				strBuf = convert( va_arg( ap, unsigned ), 16 );
				LCD2x16_setString( strBuf, 0x0 );
				break;
			default:
				LCD2x16_setData( *p );
				break;
		};
	};
	va_end( ap );
};

void LCD2x16_InitPins( u8 withReset ) //4bit mode
{	bset32( RCC_AHBENR, 19 ); //GPIOC clock
	__DSB;
	read32( GPIOC_MODER ) = 0x0;
	or32( GPIOC_MODER, S0 | S2 | S4 | S6 | S28 | S30 ); //PC0 | PC1 | PC2 | PC3 | PC14 | PC15 output
	read32( GPIOC_ODR ) = 0x0;
	if ( withReset == 0x1 )
		LCD2x16_reset( 0x0 );
};
