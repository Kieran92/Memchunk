#include"memchunk.h"
static sigjmp_buf env;
/*

Kieran Boyle
1265888
kboyle
CMPUT 379

*/


/*
sig_handler simply handles the signal of a 
*/
void sig_handler(int sig){
	//printf("I get an interruption here!\n");

	signal(SIGSEGV,SIG_DFL);
	siglongjmp(env, 1);
}


/*
get_mem_layout returns how many chunks are in the memeory and sets
the value of chunklist for each new chunk (if there is room)

*/

int get_mem_layout (struct memchunk *chunk_list, int size){
	//variable declarations
	int count = 0;
	int no_chunks = 0;
	unsigned long long chunk_size = 0;
	int page_size = getpagesize();
	int page_count = 0; 
	int current_code = 100;
	unsigned long long i = 0;
	int code;
	void* pointer;
	unsigned long long start = i;
	unsigned long long end = (0xffffffff - page_size) + 1;
	//While loop goes through until I hit the value of end 
	//that is when I break out of the loop and return the number of chunks.

	while(1){
		//This is the first iteration of the program	
		if(i==0){
			code = check_mem(i);
			page_count++;
		}else{
			current_code = check_mem(i);
			
			if (current_code == code){
				//If the codes match, increment the number of
				//pages in the chunk
				page_count++;
			}else{
				//The codes don't match
				//increment number of chunks, calculate chunk
				no_chunks++;
				chunk_size = page_count*page_size;
				page_count = 1;
				if (count < size){
					//if there is enough room in the chunk
					//add a new chunk into the list
					//pointer = (void*)&start;
					chunk_list[count].start = start;
					chunk_list[count].length = chunk_size; 
					chunk_list[count].RW = code;
					start = i; 
				}
				//increase count and set new code
				count++;
				code = current_code;
			}

			if (i == end){
				//For the last chunk add it in 
				//and break out after setting the 
				//last chunk
				no_chunks++;
				if (count < size){
					//pointer = (void*)&start;
					chunk_size = page_count*page_size;
					chunk_list[count].start = start;
					chunk_list[count].length = chunk_size; 
					chunk_list[count].RW = code;
				}
	
				break;
			}
		}
		
		i+=page_size;
	
	}
	//return the number of chunks.
	return no_chunks;
}

/*
check_mem simply tries to cause a segfault when reading and writng from memory
it takes in an unsigned long. 
*/

int check_mem(unsigned long long i){
	signal(SIGSEGV, sig_handler);
	//keep track of the signals with these two values
	bool can_read = false;
	bool can_write = false;	
	int x = sigsetjmp(env,1);
	char* c, temp = 0;
	c = (char*)(long)i;

	if (x==0){
		temp = *c; //gives you read access
		can_read = true;
		*c = temp; //gives you write access
		can_write = true;
	}
	//check if flags have been triggered. 
	if (can_read && can_write){
		//There is a segfault when you attept to write
		return 1;
	}else if (can_read){
		//There is a segfault when you try to read meaning
		//the block is inaccessible so return -1
		return 0;
	}else{
		//chunk is unreadable
		return -1;
	}


}






