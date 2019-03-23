#pragma once
#define INCS
#include <cstdio>
#include <iostream>


//==============================================================
//==============================================================
#define FILESIZE  		1024*1024*1024  //1MiB filesize
char buff[ FILESIZE ];
char sourceFileName[] = "srcMain.cpp";
//==============================================================
//==============================================================
int tmp1;

int fileCS( char* filename )
{	FILE * pFile;
	int lSize = 0x0, result = 0x0, CS = 0x0, i = 0x0;
	char *buffer = buff;
	
	pFile = fopen ( filename, "rb" );
	if (pFile == NULL){ printf( "File \"%s\" open error!\n", filename ); return -1; };
		// obtain file size:
		fseek (pFile , 0 , SEEK_END);
		lSize = ftell (pFile);
		rewind (pFile);
		// copy the file into the buffer:
		result = fread (buffer, 1, lSize, pFile);
		if (result != lSize) {printf ("Reading file \"%s\" error", filename); return -1;}
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
	};
	
	int CS = fileCS( sourceFileName );
	printf( "init CS: %i\n", CS );
	while( 1 )
	{	if ( fileCS( sourceFileName ) != CS )
		{	CS = fileCS( sourceFileName );
			printf( "recalc CS: %i\n", CS );
		};
	};
	
	exit(0);
	//return 0;
};




