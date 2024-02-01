#include <stdio.h>
#include <stdlib.h>

#define BYTES_SIZE 4
#define N 1024
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))

int main(int argc, char* argv[]){

    // happy path: take one file, and returns file compressed
    // my example: ./wzip dst src -->return src compressed into dst

    FILE* src = NULL;
    FILE* dst = NULL;

    src = fopen(argv[1], "r");
    dst = fopen(argv[2], "w+");

    size_t bytes_long = BYTES_SIZE;
    size_t max_size = N;
    char* buffer = malloc(N * sizeof(char));

    size_t readed = fread(buffer, sizeof(char), ARRAY_SIZE(buffer), src);

    printf("readed: %lu\n", readed);
    return 0;
}