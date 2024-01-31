#include <stdio.h>
#include <stdlib.h>

#define BYTES_SIZE 4
#define N 1024

int main(int argc, char* argv[]){

    // happy path: take one file, and returns file compressed
    // my example: ./wzip dst src

    FILE* src = NULL;
    FILE* dst = NULL;

    src = fopen(argv[1], "r");
    dst = fopen(argv[2], "rw");

    size_t bytes_long = BYTES_SIZE;
    size_t max_size = N;
    size_t readed = fwrite(src, max_size, bytes_long, dst);

    return 0;
}