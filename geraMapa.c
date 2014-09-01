/*
	Mapa (Condições):
		-Gás natural sobre petróleo e sempre abaixo de rocha (ou outro material sólido)
		-Sílica (pura) em concentrações pequenas, baixa probabilidade de grandes volumes
		1º nível:
			Quase 100% água (0), baixa probabilidade de rocha (5)
		2º-5º níveis:
			Maiores probabilidades para materiais sólidos (comuns e/ou preciosos - exceto diamante).
		6º-10º níveis:
			Maior probabilidade para combustíveis fósseis. Maior probabilidade para diamante, mas ainda assim, baixa.
			Baixa probabilidade para água.
		11º-15º níveis:
			Maior probabilidade para diamante, combustíveis fósseis e urânio.
			Baixíssima probabilidade de água
		16º-Abaixo:
			Muitas rochas, baixa a probabilidade de materiais preciosos, combustíveis fósseis e outros

*/

#include <stdio.h>
#include <stdlib.h>

typedef struct{
	int ***mapa;
	//Dimensões do mapa, [l]inha, [c]oluna e [p]rofundidade
	int l,c,p;
}Mapa;

//Recebe um mapa e aloca em memória
void alocaMapa(Mapa *mp);

//Gera um mapa randômico
void geraMapa(Mapa *mp);

//Imprime um mapa na saída padrão
void imprimeMapa(Mapa *mp);


int main(int argc, char *argv[]){
	Mapa mp;
	mp.l = atoi(argv[1]);
	mp.c = atoi(argv[2]);
	mp.p = atoi(argv[3]);

	geraMapa(&mp);
	imprimeMapa(&mp);
}

void alocaMapa(Mapa *mp){
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

void geraMapa(Mapa *mp){
	alocaMapa(mp);
	int l, c, p;

	for(l = 0; l < mp->l; l++){
		for(c = 0; c < mp->c; c++){
			for(p = 0; p < mp->p; p++){
				//Fazer algoritmo
				mp->mapa[l][c][p] = l+c+p;
			}
		}
	}

	return;
}

void imprimeMapa(Mapa *mp){
	int l, c, p;

	printf("%d %d %d\n", mp->l, mp->c, mp->p);

	for(p = 0; p < mp->p; p++){
		for(l = 0; l < mp->l; l++){
			for(c = 0; c < mp->c; c++){
				printf("%d ", mp->mapa[l][c][p]);
			}
			printf("\n");
		}
	}
	return;
}