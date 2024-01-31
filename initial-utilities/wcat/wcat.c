#include <stdio.h>
#include <stdlib.h>
#define N 1024

int main(int argc, char* argv[]){
	int size = 102;
	char buffer[size];
	int current = 1;
	while(argc > current){
		FILE *fp = fopen(argv[current], "r");
		if (fp == NULL) {
   	    printf("wcat: cannot open file %s\n", argv[current]);
            exit(1);
		}
		while(fgets(buffer, size , fp)){
			printf("%s", buffer);
		}
		printf("\n");
		fclose(fp);
		current++;
	}
	return 0;
}