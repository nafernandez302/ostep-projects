#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>
#include <string.h>
#include <errno.h>
#define N 10000

void search_from_arg(char* buffer, size_t tam, FILE* fp, char* word){
    while(getline(&buffer, &tam, fp) != -1){
       bool founded = false;
       unsigned int j = 0;
       unsigned int buff_length = strlen(buffer);
       unsigned int wordlength = strlen(word);
       while(j<tam && !founded && j < buff_length)
        {
            unsigned int count = 0;
            while((count < wordlength) && (word[count] == buffer[j + count])){
                count++;
            }
            founded = (count == wordlength);
            if(!founded){
                j++;
            } 
        }
        if(founded){
            printf("%s", buffer);
         }
        tam = N;
    }
}

/*void search_from_stdin(char* buffer, unsigned int tam, FILE* fp, char* word)
{
  
}*/


int main(int argc, char* argv[]){
    if (argc < 2){
        printf("wgrep: searchterm [file ...]\n");
        exit(1);
    }
    size_t tam = N;
    char* buffer = malloc(N * sizeof(char));
    char* word = argv[1];
    FILE* fp = NULL;
    if (argc == 3){
        fp = fopen(argv[2], "r");
        if(fp == NULL){
            printf("wgrep: cannot open file\n");
            exit(1);
        }
        search_from_arg(buffer, tam, fp, word);
        fclose(fp);
    }
    else{
        search_from_arg(buffer, tam, stdin , word);
    }
    free(buffer);
    return 0;
}
