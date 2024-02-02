#include <stdio.h>
#include <stdlib.h>
#include <assert.h>
#define BYTES_COMPRESSION 5
#define N 1024
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
    if(argc == 1){
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    //size_t bytes_long = BYTES_SIZE;
    //size_t max_size = N;
    char* buffer = malloc(N * sizeof(char));
    int last_readed;
    char last_char;
    
    // LECTURA DE ARCHVOS
    // arreglo de punteros a strings --> char**

    //Inicialización
    char** str_dir = malloc(N * sizeof(char*));
    for(int i = 0; i < N; ++i){
        str_dir[i] = malloc(N * sizeof(char)); //Buffers
    }


    for(int i = 1; i<argc; i++){
        src = fopen(argv[i], "r");
        if(src == NULL){
            printf("wgrep: cannot open file\n");
        }
        size_t readed = fread(buffer, sizeof(char), N, src);
        fclose(src);
    }
    free(buffer);
    return 0;
}