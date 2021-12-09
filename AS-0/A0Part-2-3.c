#include <stdio.h>
int main(int argc, char *argv[]){
    //FILE* fileName = fopen("/Users/anandrawat/Desktop/Sem\ 5/Data\ Structures/Notes/sample2.txt", "r");
    FILE* fileName = fopen(argv[1], "r");
    int outChar = fgetc(fileName);
    int ignoreFirstLine = 1;
    while (outChar != EOF){
        if (ignoreFirstLine){
            //printf("%d",ignoreFirstLine);
            if (outChar == '\n')ignoreFirstLine = 0;
            outChar = fgetc(fileName);
            continue;
        }
        if (outChar == ','){
            printf(" \n");
        }
        else if (outChar == '\"'){
            outChar = fgetc(fileName);
            while (outChar != '\"'){
                printf("%c",outChar);
                outChar = fgetc(fileName);
            }
            printf("\n");
        }
        else printf("%c",outChar);
        outChar = fgetc(fileName);
    }
    fclose(fileName);
    printf("\n");
    return 0;
}