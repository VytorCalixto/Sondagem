#include <stdio.h>

typedef int ListType;

typedef struct 
{
	ListType *vector;
	int size;
}List;

void initializeList(List *list){
	list->size = 0; //First item is head node
	list->vector = (ListType *) malloc(sizeof(ListType));
}

void addList(ListType e, List *list){
	list->size++;
	list->vector = (ListType *) realloc(list->vector, sizeof(ListType) * (list->size+1));
	list->vector[list->size] = e;
}