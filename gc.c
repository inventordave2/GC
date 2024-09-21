// GC_C

#include <stdlib.h>
#include "gc.h"

volatile struct GC_* gc;
static volatile struct GC_* gc_bkp;
static int z = 0;

volatile struct GC_* initGC( int c )	{

	if( z!=0 )
		if( gc->_!=NULL )
			free( gc->_ );

	gc = build_gc_struct( c );

	if( z==0 )	{

		gc_bkp = gc;
		z = 1;
	}

	return gc;
}
void* g( void* ref )	{

	static int i = 0;
	gc->_[i++] = ref;

	return ref;
}
int cleanUp( )	{

	int i=0, j=0;

	while( i<(gc->c) )	{

		if( gc->_[i]==NULL )	{

			++j;
			continue;
		}

		free( gc->_[i] );

		++i, ++j;
	}

	return j;
}

int reset_gc_ptr()	{

	if( z!=0 )
		gc = (volatile struct GC_*) gc_bkp;


	return (int)z;
}
volatile struct GC_* build_gc_struct( int c )	{

	volatile struct GC_* gc;

	gc->_ = (void**)calloc( c,sizeof(void*) );

	if( gc->_ == NULL )
		c = 0;

	gc->c = c;

	return gc;
}

