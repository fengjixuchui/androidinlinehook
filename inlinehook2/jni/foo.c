#include <stdio.h>

void goo(){
	printf("I'm hacker\n");
}

void foo(){
	__asm __volatile (
		"nop\n"
		"nop\n"
	);
	printf("I'm foo\n");
}
