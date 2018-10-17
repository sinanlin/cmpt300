#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>


#define BUFFER_SIZE  10
int buff[BUFFER_SIZE];






int main(int argc, char* argv[])
{
	int count = 0;



for(count = 0; count< 13; count++){
		printf("%d\n", count%BUFFER_SIZE);
	}







	return 0;
}
