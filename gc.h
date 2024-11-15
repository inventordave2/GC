// C GC utility functions & struct.

#ifndef _DAVELIB_C_GC_
#define _DAVELIB_C_GC_

typedef struct GC	{

	void** _;
	int c;
	int v;

} GC;

// The int parameter is a MAX value for the number of ptrs to store. Set a reasonable 
extern volatile struct GC* initGC( int );

// Returns a reference to the Active GC data structure.
extern volatile struct GC* getGC();

// Sets the Active GC context. This is also done implicitly on a load-time call to fnc: initGC(int).
// Returns 1 on SUCCESS, 0 on FAILURE.
// It will fail if the GC* structure is not initialised properly. Use fnc: build_gc_struct( int ) to initialize a GC structure.
extern int setGC( volatile struct GC* );

// Saves a copy of heap-allocated reference, and returns a copy of the reference.
// Usage: g( ref )
extern void* g( void* );


// Example config for temptating custom g() 
// Helper functions.
#ifndef TYPE_REF 
#define TYPE_REF struct GC
#ifdef TYPE_SIZE
#undef TYPE_SIZE
#endif
#define TYPE_SIZE sizeof( struct GC )
#endif

#define LG g

// Typically, the argument value passed
// for variable 'i' would be 1, as in
// allocate space for 1 object of the
// type *in this call*,
// but as long as you know how many
// contiguous type-slots (the gc 
// doesn't have to worry about it,
// the local OS memory manager tracks
// the lengths of the buffers it allocated
// from the Process Heap),
// without over-running the buffer,
// you can make use of all the space
// allocated.
TYPE_REF * LG##TYPE_REF ( int i ) {
    return (TYPE_REF *) g( calloc(TYPE_SIZE,i) );
}


// This char* type-helper almost always
// useful, so available by default.
// Do not use above TYPE_REF macro
// with TYPE_REF char, clash problems
// with named entities.
// with this Helper, specifically, you
// are expected to have allocated the
// buffer yourself, so for example:
//
// char* _ = gcchar( malloc(1024) );
// would allocate and return a 1k char buffer.
extern char* gcchar( void* );


// Helper to free any GC contexts you have initialised with fnc:
// GC_* build_gc_struct(int);
extern int freeGC( volatile struct GC* gc );

// This only cleans up the Active GC context. If you have made multiple GC data structures, they will need to be
// freed seperately, using fnc: freeGC(...) 
extern int cleanUp(void);

// Returns 1 if there is space left in the Active GC to add a reference. 0 if there is no more space.
extern int gc_status();

// resizes either the GC reference passed as Arg 1, or the default GC object if NULL is passed.
// Arg 2 [int] is the new size.
extern int realloc_gc( volatile struct GC* _, int c );

// Will reset the Active GC structure reference to the default object created upon initializing DAVELIB GC with initGC(...).
// Returns 1 on success, or 0 on failure. It will fail if initGC(...) has not been called at least once during the process lifetime.
extern int reset_gc_ptr();

// As with initGC( int ), the int parameter is the MAX num of ptrs. Use this function for generating
// more GC data structures.
extern volatile struct GC* build_gc_struct( int );

#endif

