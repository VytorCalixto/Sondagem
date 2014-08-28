#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int **img, i, j;
	int l = atoi(argv[1]);
	int c = atoi(argv[2]);
	
	img = (int **) malloc(sizeof(int*)*l);
	
	for(i=0;i<l;i++)
		img[i] = (int *) malloc(sizeof(int)*c);
	
	for(i=0;i<l;i++)
		for(j=0;j<c;j++)
			img[i][j]=i+j;

	for(i=0;i<l;i++){
		for(j=0;j<c;j++){
			printf("%d", img[i][j]);
		}
		printf("\n");
	}
	
	for(i=0;i<l;i++)
		free(img[i]);
	free(img);
	return 0;
		
}
