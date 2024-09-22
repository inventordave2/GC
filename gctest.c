// GC_TEST_C

#include <stdlib.h>
#include <stdio.h>
#include <string.h>

#include "gc.h"

int main( int argc, char** argv )	{

	volatile struct GC_* myGC = initGC( 5 );
	
	char* _;
	char c = 'A';
	
	int i;
	for( i=0; i< 5; i++ )	{
		
		_ = (char*)g( malloc(11) );

		if( _ == NULL )
			return 1;
		
		for( int a=0; a<10; a++ )	{
			
			_[a] = c;
			
			if( c=='Z' )
				c = 'A';
			else
				++c;
			
		}
		_[10] = '\0';
	}

	for( i=0; i<5; i++ )	{
		
		printf( "String %d:\t%s\n", i+1, myGC->_[i] );
	}
	
	printf( "\n" );
	
	int k = cleanUp();
	
	printf( "GC freed %d allocations.\n",  k);
	
	return 0;
}

