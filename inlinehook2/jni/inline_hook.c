#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <sys/mman.h>

extern void foo();
extern void goo();

static void clearcache(char* begin, char *end)
{
	const int syscall = 0xf0002;
	__asm __volatile (
		"mov	 r0, %0\n"
		"mov	 r1, %1\n"
		"mov	 r7, %2\n"
		"mov     r2, #0x0\n"
		"svc     0x00000000\n"
		:
		:	"r" (begin), "r" (end), "r" (syscall)
		:	"r0", "r1", "r7"
		);
}

void do_hook(){
	unsigned int target_addr = (unsigned int)foo;
	
	mprotect((void*)(target_addr & ~4095), 0x1000, PROT_READ | PROT_WRITE | PROT_EXEC);
	
	*(unsigned int *)target_addr = 0xe51ff004;
	*(unsigned int *)(target_addr + 4) = (unsigned int)goo;
	
	clearcache((void*)target_addr, (void*)(target_addr + 4));
}

int main(int argc, char **argv){
	printf("--------------- Before hook --------------------\n");
	foo();
	printf("Hooking...");
	do_hook();
	printf("Done...\n");
	printf("--------------- After hook ---------------------\n");
	foo();
	return 0;
}