/*
	Q2:write an implementation of a priority queue
	that holds up to 1000 elements, which may have up to 10 priority
	levels associated with them. Give a reference application that uses
	this implementation

    Author : Arun K
*/

/*
 * The priority queue is implemented using a data structure similar to open hashing,
 * Here we have an array of 10 buckets, each bucket contains the elements of a particular priority.
 * In each of this bucket we have a head and a tail pointer to retrieve and add elements respectively.
 * The datastructure also consists of a count variable - to keep track of total the number of elements present,
 * An index variable to point to the highest priority bucket at a given instant.
 * The data type of the element is kept as void*, which could be anything depending on the application
 */

#include<stdio.h>
#include<stdlib.h>
#include "priority_queue.h"

//This allocates memory and populates the variables in the structure, returns 0 on success
//Allowing the user to specify the max priority levels and max elements adds more flexibility.
//Using char allows to have upto 256 priorities, 0==> Highest priority
int initialize_priority_queue(Priority_Queue **queue, unsigned char max_priorities, int max_elements) {
	Priority_Queue *temp_queue;
	int i;

	if (queue == NULL)
		return -1;
	//Allocate memory first
	*queue = (Priority_Queue*)malloc(sizeof(Priority_Queue));
	temp_queue = *queue;//temporary variable for convenience
	//Populate the structure
	temp_queue->max_elements = max_elements;
	temp_queue->max_priorities = max_priorities;
	temp_queue->count = 0;
	temp_queue->highest_priority_index = 0;
	temp_queue->p_buckets = (Priority_Bucket*)malloc(sizeof(Priority_Bucket)*max_priorities);
	//All buckets are empty initially, hence point to null
	for (i = 0; i < max_priorities; ++i) {
		temp_queue->p_buckets[i].head=NULL;
		temp_queue->p_buckets[i].tail=NULL;
	}
	return 0;
}

//This is the standard enqueue operation,
//Using char allows to have upto 256 priorities, 0==> Highest priority
int insert_into_queue(Priority_Queue *queue, void *data, unsigned char priority) {
	Element_Node *node;
	Element_Node *temp;

	//First do error checking
	if (queue == NULL)
		return -1;
	//Check if queue is fullor an invaid priority
	if(queue->count == queue->max_elements)
		return ERROR_MAX_SIZE_REACHED;
	if(priority >= queue->max_priorities)
		return ERROR_INVALID_PRIORITY;

	//Allocate memory for the new node
	node = (Element_Node*)malloc(sizeof(Element_Node));
	node->data = data;
	node->next = NULL;
	//We now insert at the tail of the queue corresponding to priority level
	temp = queue->p_buckets[priority].tail;
	if (temp == NULL) {
		queue->p_buckets[priority].tail = node;
		//Head also has to be null, hence point to the same node
		queue->p_buckets[priority].head = node;
		//Update the highest priority index, since we have added a element to an empty priority
		if(queue->count == 0 || priority < queue->highest_priority_index)
			queue->highest_priority_index = priority;
	} else {
		//Add a new link to the exising tail, and then make the tail to point to the new node
		temp->next = node;
		queue->p_buckets[priority].tail = node;
	}

	//update other parameters
	queue->count++;
	return 0;
}

//This is the standard dequeue operation, the data is stored in the out parameter
//Return value is 0 on success.
int remove_highest_priority_elem(Priority_Queue *queue, void **data) {
	Element_Node *head;
	int i;
	//First do the error checking
	if (queue == NULL || data == NULL)
		return -1;

	//Check if queue is empty
	if(queue->count == 0)
		return ERROR_QUEUE_EMPTY;

	//Here we know that if count is >0 then the highest_priority_index has to point to
	//the current highest priority bucket and that bucket cannot be empty, hence head != null
	//Get the data element from the head of the highest priority queue
	head = queue->p_buckets[queue->highest_priority_index].head;
	*data = head->data;
	//if head next is null implies Last element of the bucket
	if(head->next == NULL) {
		//Set the tail to null as well
		queue->p_buckets[queue->highest_priority_index].tail = NULL;
		queue->p_buckets[queue->highest_priority_index].head = NULL;
		//Recompute the highest priority index
		for (i = queue->highest_priority_index+1; i < queue->max_priorities; ++i) {
			if(queue->p_buckets[i].head != NULL) {
				queue->highest_priority_index = i;
				break;
			}
		}
	} else {
		queue->p_buckets[queue->highest_priority_index].head = head->next;
	}
	//the element_node is freed, but the data it contains is not freed, its upto the caller
	free(head);

	//update the parameters
	queue->count--;
	return 0;

}
//The function pointer is used, because the datatype of the element is unknown to the priority queue,
//It is left to the calling application to decide how to free it. For eg, it could be a structure with
//many pointers, so the free_data_func could free accordingly, or it could even choose not to free any data.
void free_priority_queue(Priority_Queue *queue,free_data free_data_func) {
	int max_priors, i;
	Element_Node *next, *current;
	if (queue == NULL)
		return;
	max_priors = queue->max_priorities;

	//First free the elements in the buckets
	for (i = 0; i < max_priors; ++i) {
		current = queue->p_buckets[i].head;
		while(current != NULL) {
			next = current->next;
            //The data type is unknown, hence it is left to the caller to decide how to free it.
			free_data_func(current->data);
			free(current);
			current = next;
		}
	}
	free(queue->p_buckets);
	free(queue);
}
