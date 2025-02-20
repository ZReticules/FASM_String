#include "stdio.h"
#include "String.hpp"

int __main(){
	// printf("lol");
	// __asm__("int3");
	// consteval int a = 0;
	// a += 1;
	FASM_String myStr = "1234567890", myStr2 = "OOps";
	// myStr2 = myStr[{0, -1}];
	myStr.sprintf(FASM_Fstr("%S"), &myStr2);
	// myStr2.slice(myStr, 0, -1);
	// myStr += myStr2;
	// myStr.print();
	// myStr.from("lol");
	myStr.print();
	// myStr += 10;
	return 0;
}