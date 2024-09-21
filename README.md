# README for DAVELIB's tiny helper utility for garbage collection of c heap-allocations.

# Most effective if the user remembers to pass allocated heap space to the helper utility on
# what is presumably a malloc() or calloc() call.

# Simplest way:

	void* ptr = malloc( num_bytes );
	g( ptr );

	// Similairly:

	char* ptr = (char*)g( malloc(num_bytes) );
	// g(..) returns a copy of the *reference* to the allocation on the heap by the malloc() call.

# The GC data structure is referenced by 'gc'.
# It is type-qualified as "volatile", which means you can safely assign it a new instance
# of a GC data structure without worrying about compiler-optimisations.
# Just remember if you ever instantiate your own extra GC data structures to keep track of them.

# You might, for example, do:

	typedef struct GC_* anotherGC;
	anotherGC = build_gc_struct( 128 );
	// if initGC(..) has already been called
	gc = anotherGC;

	g( malloc(100) );
	// That allocation pointer is now managed by gc object 'anotherGC'.

	// if you want to recover the default gc object created on initGC, simply do:
	// if (reset_gc_ptr())	{ /* The default 'gc' pointer reference was restored. */ }

