#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#define numberOfEntries 59 //closest prime number to number of entries
//can also choose a random large prime number for unkown number of entries

int numTerms;
int collisions;
float load;

typedef struct surnames surnames;
struct surnames{
    int key;
    int freq;
    char surname[20];
    surnames* next;
};

surnames* hashTableTop = NULL;

int hash(char* sampleName){
    int hash = 0;
    int numberOfChars = 0;
    while(*sampleName){
        if (*sampleName >= 'a' && *sampleName <= 'z')*sampleName = *sampleName - 32;
        hash = hash + *sampleName;
        sampleName++; 
        numberOfChars++;
    }
    hash = (hash + numberOfChars) % numberOfEntries;
    return hash;
}

void addNewName(char* sampleName, int hashValue){
    surnames* newNode = (surnames*) malloc(sizeof(surnames));
    newNode->key = hashValue;
    newNode->freq = 1;
    strcpy(newNode->surname,sampleName);
    newNode->next = hashTableTop;
    hashTableTop = newNode;
    numTerms++;
}

void checkAndAdd(char* sampleName){
    int hashValue = hash(sampleName);
    int flag = 1;
    if (hashTableTop != NULL){ // no values in hashtable hence new node must be added
        surnames* tempPointer = hashTableTop;
        while (tempPointer != NULL){ // will look for the same surname and return 0 if found.
            if (strcmp(tempPointer->surname, sampleName) == 0){
                tempPointer->freq++;
                flag = 0;
            }  
            tempPointer = tempPointer->next;
        }
        tempPointer = hashTableTop;
        while (tempPointer != NULL){ // if this loop is raeched, that surname does not exist in the hash table
            if (tempPointer->key == hashValue){ // search if duplicate key exists for differnet surname
                hashValue = (hashValue + 1) % numberOfEntries; // if it does exist, use linear probing to find next available hash value
                tempPointer = hashTableTop; // check for this new hash value from the top
                collisions++;
                continue;
            }
            tempPointer = tempPointer->next;
        }
    }
    if (flag)addNewName(sampleName, hashValue);
}

void sortList(){
    surnames* tempPointer;
    int flag = 1;
    int swapKey;
    int swapFreq;
    char swapSurname[20];
    while(flag){
        flag = 0;
        tempPointer = hashTableTop;
        while (tempPointer->next != NULL){
            if (tempPointer->key > tempPointer->next->key){
                flag = 1;

                swapKey = tempPointer->key;
                swapFreq = tempPointer->freq;
                strcpy(swapSurname,tempPointer->surname);

                tempPointer->key = tempPointer->next->key;
                tempPointer->freq = tempPointer->next->freq;
                strcpy(tempPointer->surname,tempPointer->next->surname);

                tempPointer->next->key = swapKey;
                tempPointer->next->freq = swapFreq;
                strcpy(tempPointer->next->surname,swapSurname);
                //can values be swapped in a better / faster way?
            }
            tempPointer = tempPointer->next;
        }
    }
}

void findName(char* sampleInput, char* actualInput){
    int hashValue = hash(sampleInput);
    surnames* tempPointer = hashTableTop;
    while(hashValue < tempPointer->key){
        hashValue--;
        tempPointer = tempPointer->next;
    }//at the end of this loop tempPointer will be pointing to the hash value of the input string
    //since we use linear probing to store values, the actual string may not be at that value and hence we have to go further
    while (tempPointer != NULL && strcmp(sampleInput,tempPointer->surname) != 0){
        tempPointer = tempPointer->next;
    }
    if (tempPointer != NULL)printf(">>> %s - %d \n", actualInput, tempPointer->freq);
    else printf(">>> %s - 0\n",actualInput); 
}

int main(int argc, char *argv[]){
    // FILE* fileName = fopen("/Users/anandrawat/Desktop/Sem\ 5/Data\ Structures/A1/names.csv","r");
    FILE* fileName = fopen(argv[1], "r");
    if (fileName == NULL){
        printf("File did not open");
        return 1;
    }
    printf("File %s loaded\n",argv[1]);
    numTerms = 0;
    collisions = 0;
    char storeFromFile[20];
    while (fgets(storeFromFile,20,fileName)){
        int length = strlen(storeFromFile);
        storeFromFile[length-1] = '\0';
        checkAndAdd(storeFromFile);
    }
    sortList();
    load = (float) numTerms / numberOfEntries;
    printf(" Capacity: %d\n", numberOfEntries);
    printf(" Num Terms: %d\n", numTerms);
    printf(" Collisions: %d\n", collisions);
    printf(" Load: %.6f\n", load);
    char inputString[20];
    char inputStringUpper[20];
    printf("Enter term to get frequency or type \"quit\" to escape\n");
    while(1){
        scanf("%[^\n]%*c", inputString);
        if (strcmp(inputString,"quit")==0)break;
        strcpy(inputStringUpper,inputString);
        findName(inputStringUpper,inputString);
        //printf("%s - %s\n",inputString,inputStringUpper);
    }
    return 0;
}

