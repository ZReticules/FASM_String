#include "String.h"

int __main(){
	FASM_String_t myStr = {sizeof(void *) - 1, 0, 0};
	fstr *myFstr = fstr_dynamic("|%.*d|\n|%S|");
	String_input(&myStr);
	String_sprintf(&myStr, myFstr, myStr.len, 10, &myStr);
	String_print(&myStr);
	String_free(&myStr);
	fstr_free(myFstr);
	return 0;
}