typedef int ListType;

typedef struct
{
	ListType *vector;
	int size;
}List;

void freeList(List *list){
	list->size = 0;
	free(list->vector);
}

void initializeList(List *list){
	//If the vector isn't NULL, there's something in there
	if(list->vector == NULL){
		freeList(list);
	}else{
		//If it's NULL, it's new
		list->size = 0; //First item is head node, so size is 0
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
	//i starts in 1. 0 is head node
	for(i = 1; i <= list->size; i++){
		printf("%d ", list->vector[i]);
	}
}
