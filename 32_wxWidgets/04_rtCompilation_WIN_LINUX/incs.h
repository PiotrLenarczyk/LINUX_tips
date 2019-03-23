#pragma once
#define INCS
#include <cstdio>
#include <iostream>

int tmp1;



int mainMain( void )
{	printf( "mainMain()\n" );

	FILE * pFile;
	pFile = fopen ("myfile.txt","w");	//file will be truncated and opened for write
	if (pFile!=NULL)
	{	fputs ("0123",pFile);
		fclose (pFile);
	};
	exit(0);
	//return 0;
};




