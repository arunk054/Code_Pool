
#include <stdio.h>
#include<stdlib.h>
#define MAXSIZE 10

#define FREE_VALUE -1
#define TAIL_NEXT_INDEX -2

/*global variables : 1.dataIndex:  keeps track of the head of the list.
2.freeIndex:  keeps track of the next available position in the list.
*/

/*
 * NOTE : If position or data argument is negative, then it is assumed to be invalid
 *Free index is computed by finding the index of first free element starting from index 0 of array
 *But if an element is deleted, then free index is assigned the index of the deleted element.
 */

int dataIndex, freeIndex;

int computeFreeIndex(int list[][2]){
	int i;
	freeIndex=FREE_VALUE;
	for (i = 0; i < MAXSIZE; ++i) {
		if (list[i][1]==-1)
			freeIndex=i;
	}

	return 0;
}

int list_create(int list[][2]) {
	int i;

	//default -2 it does not point to any of the elements, empty list
	dataIndex=TAIL_NEXT_INDEX;
	//default - the zeroth index is considered free
	freeIndex=0;
	for (i = 0; i < MAXSIZE; ++i) {
		//dummy
		list[i][0]=0;
		//if the next element is set to FREE_VALUE, it implies it is empty
		list[i][1]=FREE_VALUE;
	}
	return 0;
}

int list_insert_position(int list[][2], int data, int position){
	int currentIndex, count, tempIndex;

	//Full list
	if (freeIndex == FREE_VALUE)
		return -1;

	//invalid position
	if (position < 0 || data < 0)
		return -1;

	//empty list
	if (dataIndex == TAIL_NEXT_INDEX) {
		//In an empty list where else can you insert an element
		if (position != 0)
			return -1;
		dataIndex=freeIndex;
		list[dataIndex][0]=data;
		list[dataIndex][1]=TAIL_NEXT_INDEX;
		computeFreeIndex(list);
		return 0;
	}

	//special case of inserting at position 0
	if (position == 0) {
		list[freeIndex][0]=data;
		list[freeIndex][1]=dataIndex;
		dataIndex=freeIndex;
		computeFreeIndex(list);
		return 0;
	}

	//First traverse the list
	currentIndex = dataIndex;
	count=1;

	while (count < position) {
		currentIndex=list[currentIndex][1];
		//this means we have reached the last node i.e position > size of list
		//And cannot insert at the specified position
		if (currentIndex==TAIL_NEXT_INDEX) {
			return -1;
		}
		count++;
	}

	//now currentIndex points to the element at (position -1)
	tempIndex=list[currentIndex][1];
	list[currentIndex][1]=freeIndex;
	list[freeIndex][0]=data;
	list[freeIndex][1]=tempIndex;

	computeFreeIndex(list);
	return 0;
}

int list_insert_tail (int list[][2], int data) {
	int currentIndex;

	//Full list
	if (freeIndex == FREE_VALUE)
		return -1;//list is full

	//empty list
	if (dataIndex == TAIL_NEXT_INDEX) {
		dataIndex=freeIndex;
		list[dataIndex][0]=data;
		list[dataIndex][1]=TAIL_NEXT_INDEX;
		computeFreeIndex(list);
		return 0;
	}
	currentIndex=dataIndex;
	while (list[currentIndex][1]!=TAIL_NEXT_INDEX) {
		currentIndex=list[currentIndex][1];
	}

	//Now we are at the tail
	list[freeIndex][0]=data;
	list[freeIndex][1]=TAIL_NEXT_INDEX;
	list[currentIndex][1]=freeIndex;
	computeFreeIndex(list);
	return 0;
}

void list_display(int list[][2]){
	int nextIndex;
	//empty list
	if (dataIndex==TAIL_NEXT_INDEX)
		return;
	nextIndex=dataIndex;
	do {
		printf("%d\n",list[nextIndex][0]);
		nextIndex=list[nextIndex][1];
	}while(nextIndex!=TAIL_NEXT_INDEX);

	printf("\n");
}

int list_delete_position (int list[][2],int position) {
	int currentIndex, nextIndex, count, tempIndex;

	//empty list
	if (dataIndex == TAIL_NEXT_INDEX)
		return -1;

	//invalid position
	if (position < 0)
		return -1;

	//special case of deleting at position 0
	if (position == 0) {
		//since the head is being freed
		freeIndex=dataIndex;
		//new DataIndex computed
		dataIndex=list[dataIndex][1];
		//Mark the older head as freed
		list[freeIndex][1]=FREE_VALUE;
		return 0;
	}

	//First traverse the list
	currentIndex = dataIndex;
	count=1;

	while (count < position) {
		currentIndex=list[currentIndex][1];
		//this means we have reached the last node i.e position > size of list
		//And hence cannot delete the specified position
		if (currentIndex==TAIL_NEXT_INDEX) {
			return -1;
		}
		count++;
	}

	//now currentIndex points to the element at (position-1)
	nextIndex=list[currentIndex][1];
	//we are trying to delete a non-existing position
	if (nextIndex == TAIL_NEXT_INDEX)
		return -1;

	list[currentIndex][1]=list[nextIndex][1];
	list[nextIndex][1]=FREE_VALUE;

	//We have got a new free element, why not use it right away
	freeIndex=nextIndex;
	return 0;

}

int list_delete_tail (int list[][2]) {

	int currentIndex, nextToNextIndex;

	//empty list
	if (dataIndex == TAIL_NEXT_INDEX) {
		return -1;
	}

	//special case of only one element in list and hence delete dataIndex
	if (list[dataIndex][1]==TAIL_NEXT_INDEX){
		//Mark this node as free ie the head node is free
		list[dataIndex][1]=FREE_VALUE;
		//use the recently freed index
		freeIndex=dataIndex;
		//the list is empty hence reset dataIndex
		dataIndex=TAIL_NEXT_INDEX;
		return 0;
	}

	currentIndex=dataIndex;
	nextToNextIndex=list[list[currentIndex][1]][1];
	while (nextToNextIndex!=TAIL_NEXT_INDEX) {
		currentIndex=list[currentIndex][1];
		nextToNextIndex=list[list[currentIndex][1]][1];
	}


	//Now the currentIndex points to element before tail
	//Therefore the next element of current is tail and we need to free it.
	freeIndex = list[currentIndex][1];
	list[freeIndex][1]=FREE_VALUE;
	list[currentIndex][1]=TAIL_NEXT_INDEX;
	return 0;

}

int list_get_data(int list[][2], int position){

	int currentIndex, count;

	//empty list
	if (dataIndex == TAIL_NEXT_INDEX)
		return -1;

	//invalid position
	if (position < 0)
		return -1;

	//Traverse the list
	currentIndex=dataIndex;
	count=0;

	while (count < position) {
		currentIndex=list[currentIndex][1];
		//this means we have reached the last node i.e position > size of list
		//And hence cannot get data of specified position
		if (currentIndex==TAIL_NEXT_INDEX) {
			return -1;
		}
		count++;
	}
	//Now currentIndex points to the required position
	return list[currentIndex][0];
}

int main (){
	int list[MAXSIZE][2];
	list_create(list);
	list_insert_position(list,10,0);
	list_insert_position(list,11,0);
	list_insert_position(list,12,0);
	list_insert_position(list,13,0);
	list_display(list);

	list_insert_tail(list,14);
	list_display(list);

	list_delete_tail(list);
	list_display(list);

	list_delete_position(list,0);
	list_display(list);

        printf("\n data at position 2 is %d\n\n",list_get_data(list,2));


/*
	list_create(list);
	list_insert_tail(list,1);
	list_insert_position(list,20,0);
	list_insert_position(list,10,1);
	list_insert_position(list,12,2);
	list_insert_tail(list,4);
	list_insert_position(list,14,3);
	list_insert_position(list,21,0);
	list_insert_tail(list,33);
	list_insert_tail(list,22);
	list_insert_tail(list,11);
	list_delete_position(list,0);
	list_insert_position(list,21,4);
	list_delete_position(list,9);
	list_insert_tail(list,99);

	list_delete_position(list,8);
	list_delete_position(list,5);
	list_delete_position(list,4);
	list_delete_position(list,2);
	list_delete_position(list,1);
	list_delete_position(list,0);
	list_delete_position(list,0);
	list_delete_position(list,0);
	list_delete_position(list,0);
	list_delete_position(list,0);
	list_delete_position(list,1);

	list_insert_position(list,20,0);
	list_insert_position(list,10,1);
	list_insert_position(list,12,2);
	list_insert_tail(list,4);
	list_insert_position(list,14,3);
	list_insert_position(list,21,0);
	list_insert_tail(list,33);
	list_insert_tail(list,22);
	list_insert_tail(list,11);
	list_insert_tail(list,40);
	list_delete_tail(list);
	list_insert_position(list,5,1);

	list_delete_tail(list);
	list_delete_tail(list);
	list_delete_tail(list);
	list_delete_tail(list);
	list_delete_tail(list);
	list_delete_tail(list);
	//list_delete_tail(list);
	list_delete_tail(list);
	list_insert_position(list,18,0);
	list_insert_position(list,17,0);
	list_insert_position(list,19,-1);
	list_delete_position(list,-1);

	//printf("%d %d\n", freeIndex, dataIndex);
	list_display(list);

	printf("data at %d is %d\n\n",3,list_get_data(list,3));*/
	return 0;
}
