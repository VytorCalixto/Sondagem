/*
*	Mapa (Condições):
*		-Gás natural sobre petróleo e sempre abaixo de rocha (ou outro material sólido)
*		1º nível:
*			Quase 100% água (0), baixa probabilidade de rocha (5)
*		2º-5º níveis:
*			Maiores probabilidades para materiais sólidos (comuns e/ou preciosos - exceto diamante).
*		6º-10º níveis:
*			Maior probabilidade para combustíveis fósseis. Maior probabilidade para diamante, mas ainda assim, baixa.
*			Baixa probabilidade para água.
*		11º-15º níveis:
*			Maior probabilidade para diamante, combustíveis fósseis e urânio.
*			Baixíssima probabilidade de água
*		16º-Abaixo:
*			Muitas rochas, baixa a probabilidade de materiais preciosos, combustíveis fósseis e outros
*
*/

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include "mapeamento.c"

//Gera um mapa randômico
void geraMapeamento(Mapeamento *mp);

void geraPonto(Mapeamento *mp, Ponto *pontoAtual);

int main(int argc, char *argv[]){
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

void geraPonto(Mapeamento *mp, Ponto *pontoAtual){
	int x = pontoAtual->x;
	int y = pontoAtual->y;
	int p = pontoAtual->z;
	int a, b;
	switch (p){
		case 0:
			a = rand() % 1000;
			if(a == 0){
				pontoAtual->valor = 5;
			}else{
				pontoAtual->valor = 0;
			}
			break;

		case 1 ... 5:
			if(mp->mapa[x][y][p-1].valor == 0){ //Água em cima
				a = rand() % 5;
				if(a != 0){
					pontoAtual->valor = 0;
				}else{
					b = (rand() % 10) + 1;
					while((b == 1 || b == 2)){
						b = (rand() % 10) + 1;
					}
					pontoAtual->valor = b;
				}
			}else{
				a = rand() % 10;
				if(a != 0){
					pontoAtual->valor = mp->mapa[x][y][p-1].valor;
				}else{
					b = (rand() % 255) + 1;
					pontoAtual->valor = b;
				}
			}
			break;

		case 6 ... 10:
			if(mp->mapa[x][y][p-1].valor == 0){ //Água em cima
				a = rand() % 5;
				if(a == 0){
					pontoAtual->valor = 0;
				}else{
					b = (rand() % 10) + 1;
					while((b == 1 || b == 2)){
						b = (rand() % 10) + 1;
					}
					pontoAtual->valor = b;
				}
			}else{
				a = rand() % 33;
				if(a != 0){
					pontoAtual->valor = mp->mapa[x][y][p-1].valor;
				}else{
					b = (rand() % 255) + 1;
					pontoAtual->valor = b;
				}
			}
			break;

		default:
			pontoAtual->valor = 1;
			break;
	}
	return;
}
