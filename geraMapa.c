/*
*	Mapa (Condições):
*		-Gás natural sobre petróleo e sempre abaixo de rocha (ou outro material sólido)
*		1º nível:
*			Água
*		2º-5º níveis:
*			Rocha (5), metais e basalto. Combustiveis fósseis tem baixos volumes.
*		6º-10º níveis:
*			Sal (11) por quase todas essas camadas.
*		11º-15º níveis:
*			Rocha e grandes volumes de combustíveis fósseis
*		16º-Abaixo:
*			Muitas rochas, baixa probabilidade de materiais preciosos, combustíveis fósseis e outros
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>
#include "mapeamento.c"
#include "compostos.c"

//Gera um mapa randômico
void geraMapeamento(Mapeamento *mp);

void geraPonto(Mapeamento *mp, Ponto *pontoAtual);

bool estaNoArray(int *array, int elemento);

int main(int argc, char *argv[]){
	iniciaCompostos();
	srand(time(NULL));
	Mapeamento mp;

	if(argc >= 4){
		mp.l = atoi(argv[1]);
		mp.c = atoi(argv[2]);
		mp.p = atoi(argv[3]);
	}else{
		scanf("%d %d %d", &mp.l, &mp.c, &mp.p);
	}

	geraMapeamento(&mp);
	imprimeMapeamento(&mp);
}

void geraMapeamento(Mapeamento *mp){
	alocaMapeamento(mp);
	int l, c, p;

	for(l = 0; l < mp->l; l++){
		for(c = 0; c < mp->c; c++){
			for(p = 0; p < mp->p; p++){
				//Fazer algoritmo
				Ponto pt = {0, l, c, p};
				geraPonto(mp, &pt);
				mp->mapa[l][c][p] = pt;
			}
		}
	}

	return;
}

bool estaNoArray(int *array, int elemento){
	int i;
	for(i = 1; i < array[0]; i++){
		if(array[i] == elemento){
			return true;
		}
	}
	return false;
}

void geraPonto(Mapeamento *mp, Ponto *pontoAtual){
	int x = pontoAtual->x;
	int y = pontoAtual->y;
	int p = pontoAtual->z;
	int a, b;
	switch (p){
		case 0:
			pontoAtual->valor = AGUA;
			break;

		case 1 ... 5:
			if(mp->mapa[x][y][p-1].valor == AGUA){
				a = rand() % 4;
				if(a != 0){
					pontoAtual->valor = AGUA;
				}else{
					a = (rand() % 255) + 1;
					while(!estaNoArray(METAIS, a) && a != ROCHA){
						a = (rand() % 255) + 1;
					}
					pontoAtual->valor = a;
				}
			}else{
				a = rand() % 3;
				if(a != 0){
					pontoAtual->valor = mp->mapa[x][y][p-1].valor;
				}else{
					a = (rand() % 255) + 1;
					while(!estaNoArray(METAIS, a) && a != ROCHA && !estaNoArray(COMBUSTIVEIS, a)){
						a = (rand() % 255) + 1;
					}
					pontoAtual->valor = a;
				}
			}
			break;

		case 6 ... 10:

			break;

		default:
			pontoAtual->valor = 0;
			break;
	}
	return;
}
