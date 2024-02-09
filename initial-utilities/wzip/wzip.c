#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define BYTES_COMPRESSION 5
#define MAX_ARGS 100
#define N 4096
#define ARRAY_SIZE(arr) (sizeof(arr) / sizeof((arr)[0]))


int write_into_stdout(char* buffer, unsigned int size, char* last_char, int readed){
    assert(buffer!=NULL);
    unsigned int written_int = 0;
    unsigned int written_char = 0;
    unsigned int i = 0;
    unsigned int count, count_char;
    while(i < size && buffer[i] != '\0'){
        if((i == 0) && (*last_char == buffer[i]) && (readed!=0)){
            count = readed;
            count_char = *last_char;
        }
        else{
            count = 1;
            count_char = buffer[i];
        }
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
    *last_char = (char)count_char;
    return count;
}

int main(int argc, char* argv[]){

    // happy path: take one file, and returns file compressed
    // my example: ./wzip dst src -->return src compressed into dst

    FILE* src = NULL;
    FILE* dst = NULL;
    if(argc == 1){
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    char buffer[N];
    char current_char, prev_char;
    int count = 1;
    int last_readed;
    
    dst = fopen("dst", "w+");
    // Leo el primer archivo por separado
    src = fopen(argv[1], "r");
    if(src == NULL){
        printf("wgrep: cannot open file\n");
        exit(1);
    }
    size_t readed_prev = fread(&prev_char, 1, 1, src);
    int i = 0;
    while(fread(&current_char, 1, 1, src) > 0){
        //printf("rep number %d\n", i);
        if(current_char != prev_char){
            fwrite(&count, 4, 1, stdout);
            fwrite(&prev_char, 1, 1, stdout);
            count = 1;
            prev_char = current_char;
        }
        else{
            count++;
        }
        i++;
    }
    fwrite(&count, 4, 1, stdout);
    fwrite(&current_char, 1, 1, stdout);
    fclose(src);
    fclose(dst);
    return 0;
}