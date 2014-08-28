#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int ***mapa;
	//Dimensões do mapeamento, [l]inha, [c]oluna e [p]rofundidade
	int l,c,p;
}Mapeamento;

//Recebe um mapeamento e aloca em memória
void alocaMapeamento(Mapeamento *mp);


int main(int argc, char *argv[]){
	Mapeamento mp;
	// mp.l = atoi(argv[1]);
	// mp.c = atoi(argv[2]);
	// mp.p = atoi(argv[3]);

	printf("%s %s %s\n", argv[1], argv[2], argv[3]);

	// alocaMapeamento(&mp);
	printf("%d\n", argc);

}

void alocaMapeamento(Mapeamento *mp){
	int i,j,k;
	mp->mapa = (int ***) malloc(sizeof(int**) * mp->l);

	for(i=0; i < mp->l; i++){
		mp->mapa[i] = (int **) malloc(sizeof(int*) * mp->c);
		for(j=0; j < mp->c; j++){
			mp->mapa[i][j] = (int *) malloc(sizeof(int) * mp->p);
		}
	}

	return;
}