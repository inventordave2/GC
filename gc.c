// GC_C

#include <stdlib.h>
#include "gc.h"

static volatile struct GC* gc;
static volatile struct GC* gc_bkp;
static int z = 0;
static int _entry = 1;

volatile struct GC* initGC( int c )	{

	if( !_entry )	{
		
		if( gc->_!=NULL )	{
			
			free( gc->_ );
		}
		free( (struct GC*) gc );
	}
	
	gc = build_gc_struct( c );

	if( _entry==1 )	{
		
		gc_bkp = (volatile struct GC*)malloc( sizeof(struct GC) );
		*gc_bkp = *gc;
		_entry=0;
	}

	return (volatile struct GC*) gc;
}
volatile struct GC* build_gc_struct( int c )	{

	volatile struct GC* gc = (volatile struct GC*)malloc( sizeof(volatile struct GC) );

	gc->_ = (void**)calloc( c,sizeof(void*) );

	if( gc->_ == NULL )
		c = 0;

	gc->c = c;
	gc->v = 0;
	
	return gc;
}

volatile struct GC* getGC()	{

	return gc;
}
int setGC( volatile struct GC* _ )	{

	if( _->_ != NULL )	{
		
		gc =  _;
		return 1;
	}
	
	return 0;
}
int freeGC( volatile struct GC* gc )	{
	
	if( gc==NULL )
		return 0;
	
	if( gc->_!=NULL )
		free( gc->_ );
	
	free( (struct GC*) gc );
	
	return 1;
}

void* g( void* ref )	{

	if( gc->c > gc->v )
		gc->_[gc->v++] = ref;
	else	{
		
		return NULL;
	}
	
	//--z;
	
	return ref;
}

char* gcchar( void* ref )	{

	return (char*) g( ref );
}

int gc_status()	{

	return (gc->v < gc->c);
}
int reset_gc_ptr( )	{

	if( !_entry )	{
		*gc = *gc_bkp;
		return 1;
	}

	return 0;
}
int realloc_gc( volatile struct GC* gc_, int c2 )	{
	
	if( gc_ == NULL )
		gc_ = gc;
	
	int c = gc_->c;
	
	if( c2 == c )
		return 0;

	int t;
	if ( c2 < c )
		t = c2;
	else
		t = c;

	void** _ = (void**)malloc( sizeof(void*) * c );
	
	int i;
	
	for( i=0; i < t; i++ )
		_[i] = gc_->_[i];
	
	free( gc_->_ );

	gc_->_ = (void**)malloc( sizeof(void*) * c2 );
	
	for( i=0; i < t; i++ )
		gc_->_[i] = _[i];
	
	if( i < c )	{
	
		free( _ );
		return -1; 
	}
	
	for( ; i < c2; i++ )
		gc_->_[i] = (void*)calloc( 1, sizeof(void*) );
	
	gc_->c = i;
	gc_->v = 0;
	
	free( _ );
	
	return +1;
}

int cleanUp( )	{

	int i=0, j=0;

	while( i<(gc->c) )	{

		if( gc->_[i]==NULL )	{

			++i;
			continue;
		}

		free( gc->_[i] );

		++i, ++j;
	}

	free( (struct GC*) gc );
	
	return j;
}

