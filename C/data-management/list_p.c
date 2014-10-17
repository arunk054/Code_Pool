#include <stdio.h>
#include<stdlib.h>

typedef struct list_node_struct {
	int data;
	struct list_node_struct * next;

}list_node;

/*
 * Assumption : head pointer does not store any data, insead it stores the count of the list
 *
 */

int list_create(list_node *head){
	//head->data will store the number of elements in the list
	head->data=0;
	head->next=NULL;
	return 0;
}

list_node* create_node(int data, list_node* next){
	list_node *node = (list_node*)malloc(sizeof(list_node));
	node->data=data;
	node->next=next;
	return node;
}

int list_insert_position(list_node *head, int data, int position){
	list_node *start, *temp;
	int count;

	//invalid position, negative data, etc
	if (position < 0 || data < 0 || head == NULL)
		return -1;

	//Traverse the list
	start=head;
	count=0;
	while (count < position){
		start=start->next;
		//reached the end of the list ie the position is greater than size of list
		if (start==NULL){
			return -1;
		}
		count++;
	}

	//Now 'start' points to the element before position-1
	temp = start->next;
	start->next=create_node(data, temp);

	//increment the count in the list
	head->data++;
	return 0;
}

int list_insert_tail(list_node *head, int data){

	list_node *start;

	// negative data, etc
	if (data < 0 || head == NULL)
		return -1;

	//Traverse the list
	start=head;
	while(start->next != NULL) {
		start=start->next;
	}
	//Now start points to the last element ie tail;
	start->next=create_node(data,NULL);

	//increment count in head
	head->data++;
	return 0;
}

int list_delete_position (list_node *head, int position){

	list_node *start, *temp;
	int count;

	//invalid position, etc
	if (position < 0 || head == NULL)
		return -1;

	//Traverse the list
	start=head;
	count=0;
	while (count < position){
		start=start->next;
		//reached the end of the list ie the position is greater than size of list
		if (start==NULL){
			return -1;
		}
		count++;
	}

	//Now 'start' points to the element before position-1
	//If the element at the specified position is not present, then we cant delete it
	if (start->next==NULL) {
		return -1;
	}
	temp = start->next;
	start->next=temp->next;

	//decrement the count in the list
	head->data--;

	free(temp);
	return 0;
}

int list_delete_tail (list_node *head){

	list_node *start, *temp;

	// null, etc
	if (head == NULL)
		return -1;


	//no elements
	if (head->next == NULL){
		return -1;
	}

	//Traverse the list
	start=head;
	while(start->next->next != NULL) {
		start=start->next;
	}

	//Now 'start' points to the element before tail, so delete start->next
	temp = start->next;
	start->next=temp->next;

	//decrement the count in the list
	head->data--;

	free(temp);
	return 0;
}

int list_get_data(list_node *head, int position){

	list_node *start, *temp;
	int count;

	//invalid position, etc
	if (position < 0 || head == NULL)
		return -1;

	start=head;
	count=0;

	while (count < position){
		start=start->next;
		//reached the end of the list ie the position is greater than size of list
		if (start==NULL){
			return -1;
		}
		count++;
	}

	//Now 'start' points to the element before position-1
	//If the element at the specified position is not present, then we cant return it
	if (start->next==NULL) {
		return -1;
	}
	return start->next->data;

}

void list_display(list_node *head){

	list_node *start;

	start=head;
	while(start->next != NULL){
		start=start->next;
		printf("%d\n",start->data);
	}

	printf("\n");
}

int main(){
	list_node head;

	list_create(&head);

	list_insert_position(&head,10,0);
	list_insert_position(&head,11,0);
	list_insert_position(&head,12,0);
	list_insert_position(&head,13,0);
	list_display(&head);

	list_insert_tail(&head,14);
	list_display(&head);

	list_delete_tail(&head);
	list_display(&head);

	list_delete_position(&head,0);
	list_display(&head);

        printf("\n data at position 2 is %d\n\n",list_get_data(&head,2));


/*	list_insert_position(&head,5,0);
	list_insert_position(&head,6,1);
	list_insert_position(&head,7,0);
	list_insert_position(&head,2,2);
	list_insert_tail(&head,12);

	list_display(&head);

	list_delete_position(&head,0);
	list_delete_tail(&head);
	//list_delete_tail(&head);

	printf("\n");
	list_display(&head);

	printf("get data at %d  is %d\n",1,list_get_data(&head,1));
*/
	return 0;
}
