/*
 * vfs_bst.h
 *
 *  Created on: Oct 21, 2009
 *      Author: Arun k
 */

#ifndef BST_H_
#define BST_H_


#define BST_SUCCESS 0
//It was '2' earlier, but devsquare expects this to be 1.
#define BST_KEY_NOT_FOUND 1

#define BST_ROOT_IS_NULL -1
#define BST_DUPLICATE_KEY 1

typedef struct bst_node
{
	struct bst_node *left;
	struct bst_node *right;
	char *string;
	int value;
}b_node;


b_node *bst_create();
/*Creates the bst, returns the root b_node*/

b_node *bst_search_string( b_node *bst_root, char *string );

/*searches the BST on the basis of fullpath and returns the searched node*/
int bst_insert ( b_node **bst_root_ptr, char *string, int value);


/* deletes the bst node and returns root */
/*Prints the bst*/
void print_inorder(b_node *bst_root);


#endif /* BST_H_ */
