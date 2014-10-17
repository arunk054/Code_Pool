/*
 * linkedlist.h
 *
 *
 *      Author: arunk
 */

#ifndef LINKEDLIST_H_
#define LINKEDLIST_H_

typedef struct list_node{
	unsigned short index;
	struct list_node *next;
}l_node;

l_node *list_insert_head( l_node *head, unsigned short index );

l_node *list_delete_head( l_node *head );

void free_list (l_node *head);
#endif /* LINKEDLIST_H_ */
