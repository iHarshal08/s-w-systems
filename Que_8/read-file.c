#include<stdio.h>
#include<stdlib.h>
int main(int argc, char *argv[]){
    FILE *file;
    char line[1024];
    if(argc != 2){
        printf("usage: ./read-file source.txt\n");
        return 1;
    }

    file = fopen(argv[1], "r");
    if (file == NULL){
        perror("Error Opening file");
        return 1;
    }

    while(fgets(line, sizeof(line), file) != NULL)
        printf("%s", line);
    
    fclose(file);
    return 0;
}