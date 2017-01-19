#include<stdio.h>
#include"memchunk.h"
int main(){
	//Variable Declarations 
	int size = 16;
	int chunk_no = 0;
	unsigned long long data_size = 0;
	int i = 0;
	//printf("off to a start\n");
	struct memchunk chunk_list[size];
	chunk_no = get_mem_layout(chunk_list,size); 
	//Iterate through the chunklist
	for (i = 0; i < chunk_no; i += 1){
		printf("Block No. %d\n",i);
		printf("Start of chunk 0x%x\n", chunk_list[i].start);
		printf("length %lu\n",chunk_list[i].length);
		printf("status %d\n\n",chunk_list[i].RW);
		
		data_size += chunk_list[i].length;
	}
	//Print the output
	printf("this is the total amount of memory in use %llu\n",data_size);
	printf("The number of chunks is: %d\n",chunk_no);
	return 0;

}
