
/*
 * vfs_bst.c
 *
 *  Created on: Oct 21, 2009
 *      Author: Arun K
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "bst.h"

//This method is just for convention sake
b_node *bst_create() {
	return NULL;
}

b_node *bst_search_string( b_node *bst_root, char *string ){
	while(bst_root != NULL) {
		int cmp = strcmp(string, bst_root->string);
		if (cmp < 0) {
			bst_root = bst_root->left;
		} else if (cmp > 0) {
			bst_root = bst_root->right;
		}else {//implies we found the node
			return bst_root;
		}
	}
	return NULL;
}

/* Creates a new node based on given data and inserts into the BST. Returns 0 on success,
 * 1 in case of duplicate entry; the root argument gets updated */
int bst_insert ( b_node **bst_root_ptr, char *string, int value) {

	b_node *root;
	b_node *newNode;
	//This stores the address of the left or right pointer of the parent
	b_node **insertAt = NULL;
	int cmp;

	//Some error check, may be unnecessary
	if (bst_root_ptr == NULL) {
		return BST_ROOT_IS_NULL;
	}

	root = *bst_root_ptr;

	while (root != NULL) {
		cmp = strcmp(string, root->string);
		if (cmp < 0) {
			//This is the node into which we will store the new node
			insertAt = &(root->left);
			root = *insertAt;
		} else if (cmp > 0) {
			insertAt = &(root->right);
			root = *insertAt;
		} else {//Duplicate key
			return BST_DUPLICATE_KEY;
		}
	}

	//Allocate the memory to new node and populate the fields
	newNode = (b_node*)malloc(sizeof(b_node));
	newNode->left = NULL;
	newNode->right = NULL;
	newNode->value=value;
	newNode->string = (char*)malloc(sizeof(char)*strlen(string) + 1);
	strcpy(newNode->string, string);

	//We now need to assign the new node as the child of parent node
	//But before that we need to check if we infact have a root or not.
	if (*bst_root_ptr == NULL) {
		*bst_root_ptr = newNode;
	} else {
		*insertAt = newNode;
	}
	return BST_SUCCESS;

}


void print_inorder (b_node *root){
	if (root == NULL) {
		return;
	}
	print_inorder(root->left);
	printf("%s <%d>\n",root->string, root->value);
	print_inorder(root->right);
}

