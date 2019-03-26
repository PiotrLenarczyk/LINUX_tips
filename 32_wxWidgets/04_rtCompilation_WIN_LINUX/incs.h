#pragma once
#define INCS
//==============================================================
typedef	unsigned char				u8;
typedef	unsigned short				u16;
typedef	unsigned int 				u32;
typedef unsigned long 	  			u64;
//==============================================================
#include <cstdlib>
#include <cstdio>
#include <iostream>
#include <string>
using namespace std;
//==============================================================
#define	WINEXE	//optional string ".exe"
#define FILESIZE  					1024*1024*1024  //1MiB filesize
#define	CMDSIZE						2*1024
char buff[ FILESIZE ];
char sourceFileName[] = "srcMain.cpp";
char resultsFileName[] = "output.txt";
char modeStr[ CMDSIZE ];
char cmd[ CMDSIZE ];
char cmdRet[ CMDSIZE ];
char localPATH[ CMDSIZE ];

#define	GCC_OPT                 "-mtune=native -march=native -std=c++11 -O1 -pipe "
#define GCC_FLAGS               "-g -fmax-errors=1 "
//target hardware compiler specific - need to be initialized
char toolPATH[ CMDSIZE ];   //"C:\\MinGW\\bin\\"
char toolType[ CMDSIZE ];		//"arm-none-eabi" | ""
char preprocCMD[ CMDSIZE ];		//g++ -E main.c		//preprocess only
							//"g++"
							//toolType
							//WINEXE 
							//" -E "
							//GCC_OPT
							//GCC_FLAGS
							
							//C:\GNU_ARM_CORTEX\share\gcc-arm-none-eabi\samples\src\minimum
							//arm-none-eabi-gcc minimum.c ../../startup/startup_ARMCM0.S -mthumb 
							//-mcpu=cortex-m0 -D__STARTUP_CLEAR_BSS -D__START=main -Os -flto 
							//-ffunction-sections -fdata-sections --specs=nano.specs 
							//--specs=nosys.specs -L. -L../../ldscripts -T nokeep.ld 
							//-Wl,--gc-sections -Wl,-Map=minimum.map -g0 -Og -o "minimum_CM0.elf"
arm-none-eabi-objdump.exe -dS "minimum_CM0.elf"
char compileCMD[ CMDSIZE ];		//g++ -S main.c 	//C->assembly
char assembleCMD[ CMDSIZE ];	//objdump -S a.elf	//source + hexcode + disassembly
char sectionSizeCMD[ CMDSIZE ];	//size -tA --radix=16 a.elf
char symbolListCMD[ CMDSIZE ];	//nm a.elf
char elfToHexCMD[ CMDSIZE ];	//objcopy -Oihex a.elf a.hex 
//==============================================================
u32 PROGMODE = 0x0;
#define	PRINT_MODE( toBeFormated, ... )		//{ sprintf( modeStr, toBeFormated, ... ); };
	#define	PROG_PREPROC			0x1
	#define	PROG_PREPROC_STR		"Preproc"
	#define PROG_ASSEMBLE			0x2
	#define	PROG_ASSEMBLE_STR		"Assemble"
	#define	PROG_LINK				0x4
	#define PROG_LINK_STR			"Link"
	#define	PROG_DISASSEMBLE		0x8
	#define	PROG_DISASSEMBLE_STR	"Disassemble"
	#define	PROG_COMPILE			0x10
	#define	PROG_COMPILE_STR		"Compile"
int CS;
	#define	PROG_CS					0x101
	#define PROG_CS_STR				"Checksum"
u32 PROGSTATUS = 0x0;
	#define	PROG_NORMAL				0x1
	#define	PROG_LOOP				0x2
	#define	PROG_ERROR				(u32)(0xFFFFFFFF)
u32 CMDSTATUS = 0x0;
#define	PRINT_CMD_STATUS( toBeFormated, ... )		//{ sprintf( modeStr, toBeFormated, ... ); };
	#define	CMD_OK					0x1
	#define	CMD_ERR					0x0
u32	COMPILER_TYPE	= 0x0;
    #define COMPILER_UNINITIALIZED  0x0
    #define GCC_AMD64               0x100
    #define GCC_ARM                 0x101   //CM0+; CM4F
    #define SDCC                    0x200   //STM8
//==============================================================
//platform-dependend functions:
int executeSystem( char* cmd );
void variablesInit( void );
//platform-dependend variables in variablesInit():
//	localPATH
#define	IF_RUNCMD( comm )	                    strcpy( cmd, comm ); if ( executeSystem( cmd ) )
#define RUNCMD( comm )                          strcpy( cmd, comm ); executeSystem( cmd );
#define RUNCMD_COPY_RESULT( comm, destBuf )     IF_RUNCMD( "pwd" ){	strcpy( destBuf, cmdRet ); };
void genericVariablesInit( void )
    {   if (COMPILER_TYPE == COMPILER_UNINITIALIZED )   COMPILER_TYPE = GCC_AMD64;
        switch( COMPILER_TYPE )
        {   case GCC_AMD64:
                break;
            case GCC_ARM:
                break;
            case SDCC:
                break;                
            default:
                break;
        };
    };
#ifdef   __linux__
    #define popen    popen
    #define pclose   pclose
	void variablesInit( void )
	{   RUNCMD_COPY_RESULT( "pwd", localPATH );
        genericVariablesInit();
	};
#endif
#ifdef _WIN32
	#undef WINEXE
	#define	WINEXE	".exe"
    #define popen    _popen
    #define pclose   _pclose
    #include <windows.h>
	void variablesInit( void )
    {   memset( localPATH, 0x0, CMDSIZE );GetCurrentDirectory( CMDSIZE, ( wchar_t* )localPATH );
        genericVariablesInit();
    };
#endif
    char buffer[ CMDSIZE ];
	int executeSystem( char* cmd )
	{	FILE *fp;
		string cmdRetStr; cmdRetStr.reserve( CMDSIZE ); cmdRetStr = "";
		/* Open the command for reading. */
		fp = popen( cmd, "r");
		if (fp == NULL) 
		{	printf( "Failed to run command\n" );
			exit( PROG_ERROR );
		};

		/* Read the output a line at a time - output it. */
		while ( fgets( buffer, sizeof( buffer ) - 1, fp ) != NULL )
			cmdRetStr.append( buffer );
		strcpy( cmdRet, cmdRetStr.c_str() );
		/* close */
		pclose(fp);
		cmdRetStr.clear();

		return CMD_OK;
	};
//==============================================================
//target compiler-dependend functions:
void chooseCompilerTarget( u32 targetType )
{	return;
};
//==============================================================
int tmp1;

int fileCS( char* filename )
{	PROGMODE = PROG_CS;
	PRINT_MODE( "%s", PROG_CS_STR );
	FILE * pFile;
	int lSize = 0x0, result = 0x0, CS = 0x0, i = 0x0;
	char *buffer = buff;
	
	pFile = fopen ( filename, "rb" );
	if (pFile == NULL){ printf( "File \"%s\" open error!\n", filename ); exit( PROG_ERROR ); };
		// obtain file size:
		fseek (pFile , 0 , SEEK_END);
		lSize = ftell (pFile);
		rewind (pFile);
		if (lSize >= FILESIZE) {printf ("File too big \"%s\" error", filename); fclose(pFile); exit( PROG_ERROR ); }
		// copy the file into the buffer:
		result = fread (buffer, 1, lSize, pFile);
		if (result != lSize) {printf ("Reading file \"%s\" error", filename); fclose(pFile); exit( PROG_ERROR ); }
		for ( ; i < lSize; i++ )
			CS += *buffer++;
	fclose (pFile);
	return CS;
};

int mainMain( void )
{	printf( "mainMain()\n" );
	FILE * pFile;
	pFile = fopen ( sourceFileName, "w");	//file will be truncated and opened for write
	if (pFile!=NULL)
	{	fputs ("0123",pFile);
		fclose (pFile);
	}else
	{	printf( "File \"%s\" open error!\n", sourceFileName ); 
		exit( PROG_ERROR );
	};
	variablesInit();
printf( "%s\n", preprocCMD );
	CS = fileCS( sourceFileName );
	printf( "init CS: %i\n", CS );
	while( PROGSTATUS == PROG_LOOP )
	{	if ( fileCS( sourceFileName ) != CS )
		{	CS = fileCS( sourceFileName );
			printf( "recalc CS: %i\n", CS );
		};
	};
	
//exit(0);
	return 0;
};
