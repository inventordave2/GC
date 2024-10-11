# README for DAVELIB's tiny helper utility for garbage collection of c heap-allocations.

# There is a simple example program in "gctest.c" to see it working in it's simplest use.
	make test


# Most effective if the user remembers to pass allocated heap space to the helper utility on
# what is presumably a malloc() or calloc() call.

# Simplest way:

	// At initialization:
	volatile struct GC* myGC = initGC( [int] );
	// The [int] parameter is the MAX number of allocations the GC should provide resources for.
	// Also, the return struct pointer doesn't need to be captured, but it is a reference to the
	// GC data structure itself.
	
	// then, pass all allocations through the GC function g( ... );
	
	void* ptr = malloc( num_bytes );
	g( ptr );

	// Similairly:

	char* ptr = (char*)g( malloc(num_bytes) );
	// g(..) returns a copy of the *reference* to the allocation on the heap by the malloc() call.

# The default Active GC data structure is generated on the initial call to initGC( int ).
# However, if you manage your code properly, you can create multiple GC contexts, using the
# helper functions, such as

	(struct GC*) build_gc_struct( int );
	getGC();
	setGC( struct GC* );
	
	// etc...
	
	
# Just remember if you ever instantiate your own extra GC data structures to keep track of them...
# You might, for example, do:

	struct GC* anotherGC;
	anotherGC = build_gc_struct( 128 );
	// if initGC(..) had already been called (even implicitly, at load-time)
	gc = anotherGC;

	g( malloc(100) );
	// That allocation pointer is now managed by gc object 'anotherGC'.

	// if you want to recover the default gc object created on initGC, simply do:
	// if (reset_gc_ptr())	{ /* The default 'gc' pointer reference was restored. */ }
	
# To do the GC clean-up, call:

	int v = cleanUp();
	
	Return value is the number of allocated heap references freed. I would suggest it would never be a value hgher than the MAX size given for the GC context when it was generated with fnc: build_gc_struct( int )

