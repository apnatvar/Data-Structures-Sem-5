#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"


void tree_insert(Tree_Node** root, char data){
	if (*root == NULL){
		Tree_Node *root1 = (Tree_Node *) malloc(sizeof(Tree_Node));
		root1->data = data;
		root1->right = NULL;
		root1->left = NULL;
		*root = root1;
	}
	else if ((*root)->data > data){
		tree_insert(&((*root)->left), data);
	}
	else {
		tree_insert(&((*root)->right), data);
	}
    //TODO
}

Tree_Node* create_bst (char data[]){
		Tree_Node *root = (Tree_Node *) malloc(sizeof(Tree_Node));
		root->data = data[0];
		root->right = NULL;
		root->left = NULL;
		int i = 1;
		for (;data[i] != '\0';i++){
			tree_insert(&root, data[i]);
		}
		return root;
    // TODO
}
   
Tree_Node* tree_search(Tree_Node* root, char data){
	if (root != NULL){
		if (root->data == data){
			return root;
		}
		else if (root->data < data){
			return tree_search(root->right, data);
		}
		else {
			return tree_search(root->left, data);
		}
	}
	else return NULL;
    //TODO
}

void tree_print_sorted(Tree_Node* root){
	if (root != NULL){
		tree_print_sorted(root->left);
		printf("%c", root->data);
		tree_print_sorted(root->right);
	}
    //TODO
}

void tree_delete(Tree_Node* root){
     if (root != NULL){
		tree_delete(root->left);
		tree_delete(root->right);
		free(root);
	}
    //TODO
}
