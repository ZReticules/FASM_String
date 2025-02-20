FORMAT PE64 Console

include "encoding\Win1251.inc"
include "win64a.inc"
include "String_fasm64.inc"

entry main

section ".code" readable writeable executable
	
	myStr String 7, 0, 0

	; bytes db "lol", 0

	myfstr fstr "%d"

	proc main
		cinvoke String_fromBytes, myStr, <"Hello, I am from bytes", 0>, -1
		cinvoke String_sprintf, myStr, myfstr, 10
		cinvoke String_print, myStr
		mov eax, 0
		ret
	endp

section ".idata" import data readable writeable
	
	library String_dll, "String_dll_64.dll"

	import String_dll,\
		String_print, 		"String_print",\
		String_getLpChars, 	"String_getLpChars",\
		String_flush, 		"String_flush",\
		String_alloc, 		"String_alloc",\
		String_realloc, 	"String_realloc",\
		String_free, 		"String_free",\
		String_fromBytes, 	"String_fromBytes",\
		String_addBytes, 	"String_addBytes",\
		String_fromString, 	"String_fromString",\
		String_addString, 	"String_addString",\
		String_slice, 		"String_slice",\
		String_input, 		"String_input",\
		String_fromByte, 	"String_fromByte",\
		String_addByte, 	"String_addByte",\
		String_fromNum, 	"String_fromNum",\
		String_addNum, 		"String_addNum",\
		String_sprintf, 	"String_sprintf",\
		fstr_dynamic, 		"fstr_dynamic",\
		fstr_free, 			"fstr_free"
