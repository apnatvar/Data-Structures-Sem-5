#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bstdb.h"

typedef struct Books Books;
struct Books{
    int doc_id;
    Books *left;
    Books *right;
	int word_count;
	char name[100];
    int height;
};
Books* root;
int globalWordCount;
char globalName[100];
int accidentalDuplicates;
int numberOfNodes;
int traversed;
int balancedBST;
//self added functions start here 
void countNodes(Books*temp){
	if (temp != NULL){
	countNodes(temp->right);
	countNodes(temp->left);
	numberOfNodes++;
	}
}

Books* searchNode(Books* temp, int doc_id){
	if (temp != NULL){
	traversed++;
		if (temp->doc_id == doc_id){
			return temp;
		}
		else if (temp->doc_id < doc_id){
			return searchNode(temp->right,doc_id);
		}
		else if (temp->doc_id > doc_id){
			return searchNode(temp->left,doc_id);
		}
	}
	return temp;
}

void freeMem(Books* temp){
	if (temp != NULL){
	freeMem(temp->right);
	freeMem(temp->left);
	free(temp);
	}
}
//end here
//functions from here
int max(int a, int b);

int height(Books *N){
    if (N == NULL)return 0;
    return N->height;
}

int max(int a, int b){
    return (a > b)? a : b;
}
    
Books* newNode(int doc_id){
    Books* node = (Books*)malloc(sizeof(Books));
    node->doc_id   = doc_id;
    node->left   = NULL;
    node->right  = NULL;
    node->height = 1; 
	node->word_count = globalWordCount;
	strcpy(node->name, globalName);
    return(node);
}

Books *rightRotate(Books *y){
    Books *x = y->left;
    Books *T2 = x->right;
    
    x->right = y;
    y->left = T2;
    
    y->height = max(height(y->left), height(y->right))+1;
    x->height = max(height(x->left), height(x->right))+1;
    
    return x;
}

Books *leftRotate(Books *x){
    Books *y = x->right;
    Books *T2 = y->left;
    
    y->left = x;
    x->right = T2;
    
    x->height = max(height(x->left), height(x->right))+1;
    y->height = max(height(y->left), height(y->right))+1;
    return y;
}

int getBalance(Books *N){
    if (N == NULL)return 0;
    return height(N->left) - height(N->right);
}

Books* insert(Books* node, int doc_id){
    if (node == NULL)
        return(newNode(doc_id));
    if (doc_id < node->doc_id)
        node->left  = insert(node->left, doc_id);
    else if (doc_id > node->doc_id)
        node->right = insert(node->right, doc_id);
    else{
		accidentalDuplicates = 1;
        return node;
	}
    node->height = 1 + max(height(node->left),height(node->right));
    int balance = getBalance(node);
		balancedBST = 0;

    if (balance > 1 && doc_id < node->left->doc_id)
        return rightRotate(node);
    
    if (balance < -1 && doc_id > node->right->doc_id)
        return leftRotate(node);
    
    if (balance > 1 && doc_id > node->left->doc_id)
    {
        node->left =  leftRotate(node->left);
        return rightRotate(node);
    }
    if (balance < -1 && doc_id < node->right->doc_id)
    {
        node->right = rightRotate(node->right);
        return leftRotate(node);
    }
	balancedBST = 1;
	return node;
}
//to here were referenced from geeksforgeeks.com under AVL trees

int bstdb_init ( void ) {
	if (1){
	root = NULL;
	globalWordCount = 0;
	accidentalDuplicates = 0;
	numberOfNodes = 0;
	traversed = 0;
	balancedBST = 0;
	return 1;}
	return 0;
}

int
bstdb_add ( char *name, int word_count ) {
	if (1){
	strcpy(globalName,name);
	globalWordCount = word_count;
	static int giveBookID = 1;
	int tempID = giveBookID;
	root = insert(root, tempID);
	giveBookID = giveBookID + 1;
	return tempID;
	}
	else return -1;
}

int
bstdb_get_word_count ( int doc_id ) {
	Books* temp = searchNode(root, doc_id);
	if (temp == NULL){
		return -1;
	}
	else {
		return temp->word_count;
	}
}

char*
bstdb_get_name ( int doc_id ) {
	Books* temp = searchNode(root, doc_id);
	if (temp == NULL){
		return NULL;
	}
	else {
		return temp->name;
	}
}

void
bstdb_stat ( void ) {
	if (balancedBST)printf("Balanced\n");
	else printf("Unbalanced\n");
	float avgTraversed = traversed / 22092.0;
	printf("Total Nodes traversed: %d\n", traversed);
	printf("Average Number of Nodes traversed: %f\n", avgTraversed);
	countNodes(root);
	printf("Number of Nodes in the BST are %d\n", numberOfNodes);
	if (accidentalDuplicates)printf("Duplicate DOC IDs present\n");
	else printf("Duplicates absent\n");
}

void bstdb_quit ( void ) {
	freeMem(root);
}
