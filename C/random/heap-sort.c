/*
 * sort.c
 *
 *  Created on: Aug 20, 2009
 *      Author: root
 */

#include "sort.h"

void sort (int *arr, int size) {

	//implementation of a heap sort

	int i,start, left, right, toSwap, root ;

	//CREATE THE HEAP, INPLACE
	if (size < 2)
		return;

	//using shift operators to multiply
	start = (size-2) >> 1;

	for (i=start; i >= 0 ; --i) {
		root=i;

		do {
			left = (root<<1) + 1;

			if (left < size) {
				if ((right = left + 1) < size){
					toSwap = (arr[left]>arr[right])?left:right;
				} else {
					toSwap = left;
				}
				if (arr[root] < arr[toSwap]) {
					left=arr[root];
					arr[root]=arr[toSwap];
					arr[toSwap]=left;
				}
			} else  {
				break;
			}
			//new root is its child with which it was swapped
			root = toSwap;
		}while (root <= start);
	}

	//Now we have constructed the heap, its time to sort

	do {
		size--;
		left=arr[0];
		arr[0]=arr[size];
		arr[size]=left;

		if (size<2)
			return;
		start = (size-2) >> 1;
		root=0;
		do {
			left = (root<<1) + 1;
			if (left < size) {
				if ((right = left + 1) < size){
					toSwap = (arr[left]>arr[right])?left:right;
				} else {
					toSwap = left;
				}
				if (arr[root] < arr[toSwap]) {
					left=arr[root];
					arr[root]=arr[toSwap];
					arr[toSwap]=left;
				}
			} else  {
				break;
			}
			//new root is its child with which it was swapped
			root = toSwap;
		}while (root <= start);
	}while (1);

}
