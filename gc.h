// C GC utility functions & struct.
#ifndef _DAVELIB_C_GC_
#define _DAVELIB_C_GC_

typedef struct GC_	{

	int c;
	void** _;
} GC_;

extern volatile struct GC_* gc;

// The int parameter is a MAX value for the number of ptrs to store. Set a reasonable 
extern volatile struct GC_* initGC( int );
// Usage: g( ref )
// saves a copy of heap-allocated reference, and returns a copy of the reference.
extern void* g( void* );
extern int cleanUp(void);

// Will reset the DAVELIB GC 'gc' data structure reference to the default object created upon
// initializing DAVELIB GC with initGC(...)
extern int reset_gc_ptr();

// As with initGC( int ), the int parameter is the MAX num of ptrs. Use this function for generating
// more GC data structures.
extern volatile struct GC_* build_gc_struct( int );

#endif

