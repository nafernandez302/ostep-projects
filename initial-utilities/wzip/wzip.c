#include <stdio.h>
#include <stdlib.h>

#define N 1024
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))


void write_into_stdout(char* buffer){
    unsigned int readed_int, readed_char = 0;
    readed_int = fwrite(buffer, sizeof(int), 1 , stdout);
    readed_char = fwrite(buffer, sizeof(char), 1 , stdout);
}

int main(int argc, char* argv[]){

    // happy path: take one file, and returns file compressed
    // my example: ./wzip dst src -->return src compressed into dst

    FILE* src = NULL;

    src = fopen(argv[1], "r");

    //size_t bytes_long = BYTES_SIZE;
    //size_t max_size = N;
    char* buffer = malloc(N * sizeof(char));

    size_t readed = fread(buffer, sizeof(char), N, src);

    write_into_stdout(buffer);


    free(buffer);
    fclose(src);
    return 0;
}