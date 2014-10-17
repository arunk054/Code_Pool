/*
 *Author : Arun K
 * Provides insert and search for strings, the underlying
 * datastructure cud be a bst.
 */

#include<stdio.h>
#include "bst.h"

static int addr_auto_incr;
static b_node *bst_root;

int dict_initialize(){
	addr_auto_incr=0;
	bst_root = bst_create();
	return 0;
}

//Returns the value in b_node
int dict_insert(char *string){
	int i;
	i = bst_insert(&bst_root,string,addr_auto_incr);
	addr_auto_incr++;
	return addr_auto_incr-1;
}

int dict_get_address(char *string){
	b_node *node;
	node = bst_search_string(bst_root,string);
	if (node== NULL)
		return -1;
	else
		return node->value;
}
int display_dict(){
	print_inorder(bst_root);
	return 0;
}
