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

int hash1(char* sampleName){
    int hash = 0;
    while(*sampleName){
        if (*sampleName >= 'a' && *sampleName <= 'z')*sampleName = *sampleName - 32;
        hash = (hash + *sampleName) % numberOfEntries;
        sampleName++; 
    }
    return hash;
}

int hash3(char* sampleName){
    int hash = 0;
    while (*sampleName){
        hash = 1 + ((hash + *sampleName) % (numberOfEntries-1));
        sampleName++;
    }
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
    int hashValue = hash1(sampleName);
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
                hashValue = (hashValue + hash3(sampleName)) % numberOfEntries; // if it does exist, use linear probing to find next available hash value
                tempPointer = hashTableTop;
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
                //can values be swapped in a easier / faster way?
            }
            tempPointer = tempPointer->next;
        }
    }
}

void findName(char* sampleInput, char* actualInput){
    int hashValue = hash1(sampleInput);
    //printf("%s\n",sampleInput);
    surnames* tempPointer = hashTableTop;
    int flag = 1;
    int i = 0;
    while (i < numberOfEntries && flag){
        i++;
        //printf("%d - %d\n",hashValue,i);
        while (tempPointer != NULL){
            if (tempPointer->key == hashValue){
                if (strcmp(tempPointer->surname,sampleInput) == 0){
                    printf(">>> %s - %d \n", actualInput, tempPointer->freq);
                    flag = 0;
                    break;
                }
                //printf("%d - %s\n",strcmp(tempPointer->surname,sampleInput),tempPointer->surname);
            }
            tempPointer = tempPointer->next;
        }
        hashValue = (hashValue + hash3(sampleInput)) % numberOfEntries;
        tempPointer = hashTableTop;
    }
    if (flag)printf(">>> %s - 0\n",actualInput); 
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
        storeFromFile[length-1] = '\0';//removing last character and replacing it with end string
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
    memset(inputStringUpper,'\0',20);
    int i = 0;
    printf("Enter term to get frequency or type \"quit\" to escape\n");
    while(1){
        scanf("%[^\n]%*c", inputString);
        if (strcmp(inputString,"quit")==0)break;
        for (i = 0; inputString[i] != '\0'; i++){
            if (inputString[i] >= 'a' && inputString[i] <= 'z')inputStringUpper[i] = inputString[i] - 32;
            else inputStringUpper[i] = inputString[i];
        }
        //printf("%s - %s\n",inputString,inputStringUpper);
        findName(inputStringUpper,inputString);
        memset(inputStringUpper,'\0',20);
    }
    return 0;
}

