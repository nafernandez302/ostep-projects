#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define BYTES_COMPRESSION 5
#define N 1024
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))


void write_into_stdout(char* buffer, unsigned int size){
    assert(buffer!=NULL);
    unsigned int written_int = 0;
    unsigned int written_char = 0;
    unsigned int i = 0;
    unsigned int count, count_char;
    while(i < size && buffer[i] != '\0'){
        count = 1 ;
        count_char = buffer[i];
        while((buffer[i+count-1] == buffer[i+count]) && (i + count  < size)){
            count++;
        }
        //printf("%u\n", count);
        //printf("count_char: %c", count_char);
        written_int = fwrite(&count, sizeof(unsigned int), 1 , stdout);
        written_char = fwrite(&count_char, sizeof(char), 1 , stdout);
        if(written_int != 1){
            printf("Faile written int\n");
        }
        if(written_char != 1){
            printf("Failed written char");
        }
        //printf("written_int: %u \n", written_int);
        //printf("written_char: %u \n", written_char);
        i = i+count;
    }
}

int main(int argc, char* argv[]){

    // happy path: take one file, and returns file compressed
    // my example: ./wzip dst src -->return src compressed into dst

    FILE* src = NULL;


    //size_t bytes_long = BYTES_SIZE;
    //size_t max_size = N;
    char* buffer = malloc(N * sizeof(char));

    for(int i = 1; i<argc; i++){
        src = fopen(argv[i], "r");
        size_t readed = fread(buffer, sizeof(char), N, src);
        if(readed >0){
            write_into_stdout(buffer, readed);
        }
        fclose(src);
    }
    free(buffer);
    return 0;
}