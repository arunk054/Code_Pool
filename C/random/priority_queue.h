
/*
 * The data structures and APIs of the priority queue are defined as follows,
 */

//Error codes
#define ERROR_MAX_SIZE_REACHED 1
#define ERROR_INVALID_PRIORITY 2
#define ERROR_QUEUE_EMPTY 3

typedef struct elem_node{
	//The data type of the element is kept as void*, which could be anything depending on the app
	void *data;
	struct elem_node *next;

}Element_Node;

typedef struct {
	Element_Node *head;
	Element_Node *tail;

}Priority_Bucket;

typedef struct {

	Priority_Bucket *p_buckets;
	//Points to the current highest priority bucket index, if count =0, this is undefined
	unsigned char highest_priority_index;
	//Gives the total number of elements in the priority queue
	int count;
	//These could be made global, but keeping it here adds flexibility,
	//Different applications can use the priority queue with different levels & max_elems
	unsigned char max_priorities;
	int max_elements;
}Priority_Queue;

//It allocates memory and populates the variables in the structure, returns 0 on success
//Using char allows to have upto 256 priorities, 0==> Highest priority
int initialize_priority_queue(Priority_Queue **queue, unsigned char max_priorities, int max_elements);

//This is the standard enqueue operation
int insert_into_queue(Priority_Queue *queue, void *data, unsigned char priority) ;
//This takes a function pointer which will be called to free each element
//This is needed bcause we dont know the data type of the element, and it is left to

//This is the standard dequeue operation, the data is stored in the out parameter
//Return value is 0 on success.
int remove_highest_priority_elem(Priority_Queue *queue, void **data);

typedef void (*free_data)();
// calling application to decide how it should be freed.
void free_priority_queue(Priority_Queue *queue, free_data free_data_func);

