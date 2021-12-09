#include <stdio.h>
#include <string.h>

int main(int argc, char *argv[]){
    //FILE* fileName = fopen("/Users/anandrawat/Desktop/Sem\ 5/Data\ Structures/Notes/sample.txt", "r");
    FILE* fileName = fopen(argv[1], "r");
    char toStoreLine[1000];
    int entryColumn = 0;
    int entryRow = 0;
    int ignoreFirstLine = 1;
    int attack;
    int totalAttack = 0;
    while (fgets(toStoreLine,1000, fileName)){
        if (ignoreFirstLine){
            ignoreFirstLine = 0;
            continue;
        }
        entryRow++;
        char *pointerToLine, *pointerToOutput;
        pointerToLine = strdup(toStoreLine);
        entryColumn = 0;
        while ( (pointerToOutput = strsep(&pointerToLine,",")) != NULL){
            //if (entryColumn == 0)  printf("#");
            //else if (entryColumn == 1)  printf("Name: ");
            //else if (entryColumn == 2)  printf("Type 1: ");
            //else if (entryColumn == 3)  printf("Type 2: ");
            //else if (entryColumn == 4)  printf("Total: ");
            //else if (entryColumn == 5)  printf("HP: ");
            if (entryColumn == 6){
                sscanf(pointerToOutput,"%d",&attack);
                totalAttack = totalAttack + attack;
            }
            //else if (entryColumn == 7)  printf("Defense: ");
            //else if (entryColumn == 8)  printf("Special Attack: ");
            //else if (entryColumn == 9)  printf("Special Defense: ");
            //else if (entryColumn == 10) printf("Speed: ");
            //else if (entryColumn == 11) printf("Generation: ");
            //else if (entryColumn == 12) printf("Legendary: ");
            //else if (entryColumn == 13) printf("Pokedex Entry: ");
            //if (entryColumn > 12) printf("%s",pointerToOutput);
            //else printf("%s\n",pointerToOutput);
            entryColumn++;
        }
        //printf("\n");
    }
    float avgAttack = (float)totalAttack / entryRow * 1.0;
    printf("%f\n",avgAttack);
    fclose(fileName);    
    return 0;
}