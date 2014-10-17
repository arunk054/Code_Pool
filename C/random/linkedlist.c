/*
 * linkedlist.c
 *
 *
 *      Author: arunk
 */

#include "linkedlist.h"
#include <stdio.h>
#include <stdlib.h>


l_node *list_insert_head( l_node *head, unsigned short index ) {

	l_node *current;

	//No need to check if head is null, even if it is our next wil be nulll

	//First allocate memory to store index
	current = (l_node*)malloc(sizeof(l_node));
	current->index = index;
	//Our current node will become the head hence it's next is head
	current->next = head;

	return current;

}

l_node *list_delete_head( l_node *head ) {

	l_node *new_head;

	//Error checking, if head is null
	if (head == NULL) {
		return NULL;
	}

	//Once we delete head, the next element in head becomes the new head
	new_head = head->next;

	free(head);

	return new_head;
}

void free_list (l_node *head) {
	while (head != NULL) {
		head = list_delete_head(head);
	}
}
