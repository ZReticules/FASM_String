@module String

	include "fstr.inc"
	include "fstr.fasm"

	struct String
	    __size  dd ?
	    len     dd ?
	    union
	        __lpChars   dptr ?
	        __chars     db pointer.size dup(?)
	    ends

	    print       dm this:inline
	    getLpChars  dm this:inline
	    flush       dm this:inline

	    alloc       dm this
	    realloc     dm this
	    free        dm this
	    fromBytes   dm this
	    addBytes    dm this
	    fromString  dm this
	    addString   dm this
	    fromByte    dm this
	    addByte     dm this
	    fromNum     dm this
	    addNum      dm this
	    slice       dm this
	    input       dm this
	    sprintf     dm this
	ends

	include "String.fasm"

@endm