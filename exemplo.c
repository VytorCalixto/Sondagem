#include <stdio.h>
#include <stdlib.h>

int main(int argc, char *argv[]){
	int ***img, i, j, k;
	int l = atoi(argv[1]);
	int c = atoi(argv[2]);
	int p = atoi(argv[3]);
	
	img = (int ***) malloc(sizeof(int**)*l);

	for(i=0;i<l;i++){
		img[i] = (int **) malloc(sizeof(int*)*c);
		for(j=0;j<c;j++){
			img[i][j] = (int *) malloc(sizeof(int)*p);
		}
	}
	
	for(i=0;i<l;i++){
		for(j=0;j<c;j++){
			for(k=0;k<p;k++){
				img[i][j][k]=i+j+k;
			}
		}
	}

	for(i=0;i<l;i++){
		for(j=0;j<c;j++){
			for(k=0;k<p;k++){
				printf("%d", img[i][j][1]);
			}
			printf("\n");
		}
		printf("\n");
	}
	
	for(i=0;i<l;i++){
		for(j=0;j<c;j++){
			free(img[i][j]);
		}
		free(img[i]);
	}
	free(img);
	return 0;
		
}
