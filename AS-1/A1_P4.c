#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define numberOfEntries 99991
int numTerms;
int collisions;
float load;

typedef struct people people;
struct people{
    int key;
    people* next;
    people* nextInChain;
    char personID[20];
    char depositionID[20];
    char surname[20];
    char forename[20];
    char age[3];
    char personType[20];
    char gender[20];
    char nationality[20];
    char religion[20];
    char occupation[20];
};
people* hashTableTop = NULL;
people* printThis = NULL;

int hash(char* sampleName){
    int hash = 0;
    while(*sampleName){
        if (*sampleName >= 'a' && *sampleName <= 'z')*sampleName = *sampleName - 32;
        hash = hash + *sampleName;
        sampleName++; 
    }
    hash = hash % numberOfEntries;
    return hash;
}

void addNode(char* dataSet){
    people* newNode = (people*) malloc(sizeof(people));
    sscanf(dataSet,"%s %s %s %s %s %s %s %s %s %s",newNode->personID,newNode->depositionID,newNode->surname,newNode->forename,newNode->age,newNode->personType,newNode->gender,newNode->nationality,newNode->religion,newNode->occupation);
    int hashValue = hash(newNode->surname);
    newNode->key = hashValue;
    newNode->nextInChain = NULL;
    people* chaining;
    if (hashTableTop == NULL){
        newNode->next = NULL;
        hashTableTop = newNode;
    }
    else if (hashTableTop->next == NULL){
        if (hashValue < hashTableTop->key){
            newNode->next = hashTableTop;
            hashTableTop = newNode;
        }
        else if (hashValue == hashTableTop->key){
            collisions++;
            chaining = hashTableTop;
            while(chaining->nextInChain!=NULL)chaining = chaining->nextInChain;
            chaining->nextInChain = newNode;
            newNode->next = NULL;
        }
        else{
            hashTableTop->next = newNode;
            newNode->next = NULL;
        }
    }
    else {
        people* tempPointer = hashTableTop;
        people* prevPointer = NULL;
        while(tempPointer != NULL){
            if (hashValue > tempPointer->key){
                prevPointer = tempPointer;
                tempPointer = tempPointer->next;
                if (tempPointer == NULL && hashValue > prevPointer->key){
                    prevPointer->next = newNode;
                    newNode->next = NULL;
                }
            }
            else if (hashValue == tempPointer->key){//collision
                collisions++;
                chaining = tempPointer;
                while(chaining->nextInChain!=NULL)chaining = chaining->nextInChain;
                chaining->nextInChain = newNode;
                newNode->next = NULL;
                tempPointer = NULL;
            }
            else {
                if (prevPointer == NULL){
                    newNode->next = hashTableTop;
                    hashTableTop = newNode;
                }
                else{
                prevPointer->next = newNode;
                newNode->next = tempPointer;
                }
                tempPointer = NULL;
            }
        }
    }
}

int printTheseValues(char* sampleInput){
    people* tempPointer = printThis;
    int flag = 1;
    int returnFlag = 1;
    while(tempPointer!=NULL){
        if (strcmp(tempPointer->surname, sampleInput) == 0){
            returnFlag = 0;
            if (flag){
                flag = 0;
                printf("Person ID Deposition ID Surname    Forename    Age   Person Type   Gender   Nationality   Religion   Occupation\n");
            }
            printf("%-9s %-13s %-10s %-11s %-5s %-13s %-8s %-13s %-10s %-13s\n",tempPointer->personID,tempPointer->depositionID,tempPointer->surname,tempPointer->forename,tempPointer->age,tempPointer->personType,tempPointer->gender,tempPointer->nationality,tempPointer->religion,tempPointer->occupation);
        }
        tempPointer = tempPointer->nextInChain;
    }
    return returnFlag;
}

void findName(char* sampleInput, char* actualInput){
    int hashValue = hash(sampleInput);
    people* tempPointer = hashTableTop;
    int flag = 1;
    while (tempPointer != NULL){
        if (tempPointer->key == hashValue){
            printThis = tempPointer;
            flag = printTheseValues(sampleInput);
            break;
        }
        else tempPointer = tempPointer->next;
    }
    if (flag){printf(">>> %s not in table\n",actualInput);}
}

int main(int argc, char *argv[]){
    // FILE* fileName = fopen("/Users/anandrawat/Desktop/Sem\ 5/Data\ Structures/A1/truncated.csv", "r");
    FILE* fileName = fopen(argv[1], "r");
    if (fileName == NULL){
        printf("File did not open");
        return 1;
    }
    printf("File %s loaded\n",argv[1]);
    int i;
    numTerms = 0;
    collisions = 0;
    char buffer[1000];
    fgets(buffer,1000, fileName);
    while (fgets(buffer,1000, fileName)) {
        for (i = 0; buffer[i]!='\n'; i++){
            if (buffer[i] == ' ') buffer[i] = '-';
            else if (buffer[i] == ',' || buffer[i] == '\"')buffer[i] = ' ';//processing data in a way that it is easy to separate
        }
        addNode(buffer);
        numTerms++;
    }
    
    load = (float) numTerms / numberOfEntries;
    printf(" Capacity: %d\n", numberOfEntries);
    printf(" Num Terms: %d\n", numTerms);
    printf(" Collisions: %d\n", collisions);
    printf(" Load: %.6f\n", load);
    char inputString[20];
    char inputStringModified[20];
    memset(inputStringModified,'\0',20);
    printf("Enter term to get frequency or type \"quit\" to escape\n");
    while(1){
        scanf("%[^\n]%*c", inputString);
        if (strcmp(inputString,"quit")==0)break;
        for (i = 0; inputString[i] != '\0'; i++){
            if (inputString[i] == ' ')inputStringModified[i] = '-';
            else inputStringModified[i] = inputString[i];
        }
        findName(inputStringModified,inputString);
        memset(inputStringModified,'\0',20);
    }
    fclose(fileName);    
    return 0;
}