/*
*	Mapa (Condições):
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

bool pontoEstaNoMapa(Mapeamento *mp, Ponto *pt);

void randomFloodFill(Mapeamento *mp, Ponto *inicial, int valorReposicao);

void main(int argc, char *argv[]){
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
	FILE *mapa;
	mapa = fopen("mapa.txt", "w");
	fprintf(mapa,"%d %d %d\n", mp.l, mp.c, mp.p);
	int l, c, p;
	for(p = 0; p < mp.p; p++){
		for(l = 0; l < mp.l; l++){
			for(c = 0; c < mp.c; c++){
				fprintf(mapa, "%d ", mp.mapa[l][c][p]);
			}
			fprintf(mapa, "\n");
		}
		fprintf(mapa, "\n");
	}
	fclose(mapa);
}

void geraMapeamento(Mapeamento *mp){
	alocaMapeamento(mp);
	int l, c, p;

	for(l = 0; l < mp->l; l++){
		for(c = 0; c < mp->c; c++){
			for(p = 0; p < mp->p; p++){
				//Todos os pontos são inicializados com -1 para o flood fill
				Ponto pt = {-1, l, c, p};
				mp->mapa[l][c][p] = pt;
			}
		}
	}

	for(l = 0; l < mp->l; l++){
		for(c = 0; c < mp->c; c++){
			for(p = 0; p < mp->p; p++){
				Ponto pt = mp->mapa[l][c][p];
				if(pt.valor == -1){
					geraPonto(mp, &pt);
					// mp->mapa[l][c][p] = pt;
				}
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

bool pontoEstaNoMapa(Mapeamento *mp, Ponto *pt){
	return !(pt->x < 0 || pt->x >= mp->l || pt->y < 0 || pt->y >= mp->c || pt->z < 0 || pt->z >= mp->p);
}

void geraPonto(Mapeamento *mp, Ponto *pontoAtual){
	int x = pontoAtual->x;
	int y = pontoAtual->y;
	int z = pontoAtual->z;
	int a;
	switch (z){
		case 0: //superfície é sempre água
			pontoAtual->valor = AGUA;
			mp->mapa[x][y][z] = *pontoAtual;
			break;

		case 1 ... 5:
			if(mp->mapa[x][y][z-1].valor == AGUA){
				a = rand() % 2;
				if(a != 0){
					randomFloodFill(mp, pontoAtual, AGUA);
				}else{
					a = (rand() % 255) + 1;
					while(!estaNoArray(ROCHAS, a)){
						a = (rand() % 255) + 1;
					}
					randomFloodFill(mp, pontoAtual, a);
				}
			}else if(mp->mapa[x][y][z-1].valor != -1){
				a = rand() % 5;
				if(a != 0){
					randomFloodFill(mp, pontoAtual, mp->mapa[x][y][z-1].valor);
				}else{
					a = (rand() % 255) + 1;
					while(!estaNoArray(ROCHAS, a) && !estaNoArray(METAIS, a) && !estaNoArray(COMBUSTIVEIS, a)){
						a = (rand() % 255) + 1;
					}
					randomFloodFill(mp, pontoAtual, a);
				}
			}else{
				a = (rand() % 255) + 1;
				while(!estaNoArray(ROCHAS, a) && !estaNoArray(METAIS, a) && !estaNoArray(COMBUSTIVEIS, a)){
					a = (rand() % 255) + 1;
				}
				randomFloodFill(mp, pontoAtual, a);
			}
			break;

		case 6 ... 10:
			if(mp->mapa[x][y][z-1].valor == AGUA){
				a = rand() % 10;
				if(a == 0){
					randomFloodFill(mp, pontoAtual, AGUA);
				}else{
					a = rand() % 4;
					if(a != 0){
						randomFloodFill(mp, pontoAtual, SAL);
					}else{
						a = (rand() % 255) + 1;
						while(!estaNoArray(ROCHAS, a) &&  !estaNoArray(METAIS, a)){
							a = (rand() % 255) + 1;
						}
						randomFloodFill(mp, pontoAtual, a);
					}
				}
			}else{
				a = rand() % 3;
				if(a != 0){
					randomFloodFill(mp, pontoAtual, SAL);
				}else{
					while(!estaNoArray(COMBUSTIVEIS, a)){
						a = (rand() % 255) + 1;
					}
					randomFloodFill(mp, pontoAtual, a);
				}
			}
			break;

		case 11 ... 16:
			a = rand() % 5;
			if(a != 0){
				while(!estaNoArray(COMBUSTIVEIS, a)){
					a = (rand() % 255) + 1;
				}
				randomFloodFill(mp, pontoAtual, a);
			}else{
				a = (rand() % 255) + 1;
				randomFloodFill(mp, pontoAtual, a);
			}
			break;

		default:
			while(!estaNoArray(ROCHAS, a)){
				a = (rand() % 255) + 1;
			}
			randomFloodFill(mp, pontoAtual, a);
			break;
	}
	return;
}

void randomFloodFill(Mapeamento *mp, Ponto *inicio, int valorReposicao){
	if(!pontoEstaNoMapa(mp, inicio)){
		return;
	}
	if(inicio->valor == valorReposicao){
		return;
	}
	if(inicio->valor >= 0){ // >= 0 significa que é um composto e, portanto, já foi preenchido
		return;
	}
	int x = inicio->x;
	int y = inicio->y;
	int z = inicio->z;
	mp->mapa[x][y][z].valor = valorReposicao;

	int r1 = rand() % 4;
	int r2 = rand() % 4;
	int r3 = rand() % 4;
	int r4 = rand() % 4;
	int r5 = rand() % 19;
	if(r1 == 0){
		Ponto esq = {-1, x, y-1, z}; //valor, x, y, z
		if(pontoEstaNoMapa(mp, &esq)){
			esq = mp->mapa[x][y-1][z];
		}
		randomFloodFill(mp, &esq, valorReposicao);
	}
	if(r2 == 0){
		Ponto dir = {-1, x, y+1, z}; //valor, x, y, z
		if(pontoEstaNoMapa(mp, &dir)){
			dir = mp->mapa[x][y+1][z];
		}
		randomFloodFill(mp, &dir, valorReposicao);
	}
	if(r3 == 0){
		Ponto cima = {-1, x-1, y, z}; //valor, x, y, z
		if(pontoEstaNoMapa(mp, &cima)){
			cima = mp->mapa[x-1][y][z];
		}
		randomFloodFill(mp, &cima, valorReposicao);
	}
	if(r4 == 0){
		Ponto baixo = {-1, x+1, y, z}; //valor, x, y, z
		if(pontoEstaNoMapa(mp, &baixo)){
			baixo = mp->mapa[x+1][y][z];
		}
		randomFloodFill(mp, &baixo, valorReposicao);
	}
	if(r5 == 0){
		Ponto embaixo = {-1, x, y, z+1}; //valor, x, y, z
		if(pontoEstaNoMapa(mp, &embaixo)){
			embaixo = mp->mapa[x][y][z+1];
		}
		randomFloodFill(mp, &embaixo, valorReposicao);
	}
	return;
}
