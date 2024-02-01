#include <stdio.h>
#include <stdlib.h>

#define BYTES_SIZE 4
#define N 1024
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int main(int argc, char* argv[]){

    // happy path: take one file, and returns file compressed
    // my example: ./wzip dst src -->return src compressed into dst

    FILE* src = NULL;

    src = fopen(argv[1], "r");

    //size_t bytes_long = BYTES_SIZE;
    //size_t max_size = N;
    char* buffer = malloc(N * sizeof(char));

    size_t readed = fread(buffer, sizeof(char), N, src);

    size_t written = fwrite(buffer, sizeof(char), N, stdout);
    printf("readed: %lu\n", readed);
    printf("written: %lu\n", written);

    fclose(src);
    return 0;
}