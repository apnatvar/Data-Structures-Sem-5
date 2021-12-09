#include <stdio.h>
#include <string.h>
#include <stdlib.h>

typedef struct games games;
struct games{
    char title[35];
    char platform[20];
    int score;
    int releaseYear;
    games* next;
};

games* head = NULL;

int nextField( FILE *f, char *buf, int max ) {
	int i=0, end=0, quoted=0;
	for(;;) {	
		buf[i] = fgetc(f);
		if(buf[i]=='"') { quoted=!quoted; buf[i] = fgetc(f); }
		if(buf[i]==',' && !quoted) { break; }
		if(feof(f) || buf[i]=='\n') { end=1; break; } 
		if( i<max-1 ) { ++i; } 
	}
	buf[i] = 0;
	return end;
}

void fetchData(FILE *csv) {
	char buf[20];
    games* newNode = (games*) malloc(sizeof(games));                    
	nextField(csv, newNode->title, 35);  
	nextField(csv, newNode->platform, 20);
	nextField(csv, buf, 5);
	newNode->score = atoi(buf);
	nextField(csv, buf, 5);
	newNode->releaseYear = atoi(buf);
    if (newNode->score != 0){
            if (head == NULL){
            head = newNode;
            newNode->next = NULL;
        }
        else if (newNode->score >= head->score){
            newNode->next = head;
            head = newNode;
        }
        else{
            games* currentNode = head->next;
            games* prevNode = head;
            while (currentNode != NULL){
                if (newNode->score >= currentNode->score){
                    newNode->next = currentNode;
                    prevNode->next = newNode;
                    break;
                }
                currentNode = currentNode->next;
                prevNode = prevNode->next;
            }
            if (currentNode == NULL){
                prevNode->next = newNode;
                newNode->next = NULL;
            }
        }
    }
}

int main(int argc, char *argv[]){
    // FILE* fileName = fopen("/Users/anandrawat/Desktop/Sem\ 5/Data\ Structures/A2/t4_ign.csv", "r");
    FILE* fileName = fopen(argv[1], "r");
    while(!feof(fileName)){
        fetchData(fileName);
    }
    games* tempNode = head;
    int i = 10;
    for (; i; i--){
        printf("%*s %*s %*d %*d\n",35,tempNode->title,20,tempNode->platform,2,tempNode->score,4,tempNode->releaseYear);
        tempNode = tempNode->next;
    }
    return 0;
}
