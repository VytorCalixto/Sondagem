#include <stdio.h>

typedef int ListType;

typedef struct
{
	ListType *vector;
	int size;
}List;

void freeList(List *list){
	int size = 0;
	free(list->vector);
}

void initializeList(List *list){
	//If the list is new, the vector is NULL
	if(list->vector==NULL){
		list->size = 0; //First item is head node
	}else{
		//If it's not NULL, free the memory
		freeList(list);
	}
	list->vector = (ListType *) malloc(sizeof(ListType));
}

void addList(ListType e, List *list){
	list->size++;
	list->vector = (ListType *) realloc(list->vector, sizeof(ListType) * (list->size+1));
	list->vector[list->size] = e;
}

void printList(List *list){
	int i;
	for(i = 1; i <= list->size; i++){
		printf("%d ", list->vector[i]);
	}
}
