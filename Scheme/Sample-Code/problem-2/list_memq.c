#include<stdio.h>
#include<stdlib.h>

struct pair {
   int          car;
   struct pair* cdr;
 };
 
typedef struct pair*  PAIR;
 
PAIR cons(int val, PAIR ml) {
     PAIR r;
     r = (PAIR) malloc(sizeof(struct pair));
     r->car = val;
     r->cdr = ml;
     return r;
};

//Function list_memq : [PAIR int] -> int [0=> false, 1=> true]
//-------------------------------------------------------------
int list_memq(PAIR ls, int x) {
	PAIR ls1 = ls;
    ls_memq:
	if (ls1 == NULL) {
		return 0;
	}
	if (ls1->car == x) {
		return 1;
	} else {
		ls1 = ls1->cdr;
		goto ls_memq;
	}
}

void print_list(PAIR ls) {
	printf("Following are the elements of the list:\n");
	while (ls != NULL )
	{
		printf("%d ",ls->car);
		ls = ls->cdr;
	}
	printf("\n\n");
}

//Main method to test the code
int main() {

	//Let us create a list from 1 to 10
	int i = 10;

	char *op[8] = {"False", "True"};
	PAIR ls = cons(i, NULL);

	//Loop to create the list using cons
	for (i=i-1;i>0;--i) {
		ls=cons(i,ls);
	}

	print_list(ls);

	//Check for membership of say 1, 35, 10, 2
	printf("list_memq(1) = %s\n",op[list_memq(ls,1)]);
	printf("list_memq(35) = %s\n",op[list_memq(ls,35)]);
	printf("list_memq(10) = %s\n",op[list_memq(ls,10)]);
	printf("list_memq(2) = %s\n",op[list_memq(ls,2)]);

	printf("\n");
	return 0;
}

