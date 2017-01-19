#include<stdio.h>
#include<signal.h>
#include<unistd.h>
#include <setjmp.h>
#include <stdbool.h>


//Structures
struct memchunk {
	void *start;
	unsigned long length;
	int RW;
};
//Function Defs
int get_mem_layout (struct memchunk *chunk_list, int size);
void sig_handler(int sig);
int check_mem(unsigned long long i);
