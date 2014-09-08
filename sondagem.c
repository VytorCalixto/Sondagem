#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //Só funciona no C99 ou maior
#include "list.c" //TAD Lista
#include "mapeamento.c" //Tipo Mapeamento e Ponto

const char *COMPOSTOS[256] = {"agua", "gas natural", "petroleo", "carvao", "xisto", "rocha", "uranio", "silica", "ouro", "diamante"};

//Retorna o ponto mais profundo mapeado
Ponto maiorProfundidadeMar(Mapeamento *mp){
	Ponto maisProfundo = mp->mapa[0][0][0];
	int l, c, p;

	for(p = 0; p < mp->p; p++){
		for(l = 0; l < mp->l; l++){
			for(c = 0; c < mp->c; c++){
				if((mp->mapa[l][c][p].valor == 0) && (mp->mapa[l][c][p].z > maisProfundo.z)){
					maisProfundo = mp->mapa[l][c][p];
				}
			}
		}
	}
	return maisProfundo;
}

//Adiciona um composto não repetido em uma lista
void addComposto(int composto, List *compostos){
	int i;

	//Se o composto for Água, retornamos
	if(composto == 0){
		return;
	}
	/*i começa em 1, pois 0 é nodo cabeça
	* Se já encontrarmos o composto no vetor, retornamos
	*/
	for(i = 1; i <= compostos->size; i++){
		if((compostos->vector[i] == composto)){
			return;
		}
	}
	addList(composto, compostos);
}

//Colona na lista compostos todos os compostos distintos
void qtdCompostosDistintos(Mapeamento *mp, List *compostos){
	int l,c,p;

	for(p = 0; p < mp->p; p++){
		for(l = 0; l < mp->l; l++){
			for(c = 0; c < mp->c; c++){
				Ponto composto = mp->mapa[l][c][p];
				addComposto(composto.valor, compostos);
			}
		}
	}
	return;
}

//Formata a saída para a questão 2
void formatQuestao2(List *compostos){
	int i;
	for(i = 1; i <= compostos->size; i++){
		if(i == compostos->size - 1){
			printf("%s e ", COMPOSTOS[compostos->vector[i]]);
		}else if(i == compostos->size){
			printf("%s", COMPOSTOS[compostos->vector[i]]);
		}else{
			printf("%s, ", COMPOSTOS[compostos->vector[i]]);
		}
	}
}

/*
* Coloca no array tresMaiores os três compostos com o maior volume
* [composto][qtd]
* [composto][qtd]
* [composto][qtd]
*/
void compostosMaiorVolume(Mapeamento *mp, List *compostos, int tresMaiores[3][2]){
	int qtd[compostos->size];
	int i, l, c, p;

	//Inicia o vetor de quantidades com 0;
	for(i = 1; i <= compostos->size; i++){
		qtd[i] = 0;
	}

	for(l = 0; l < 3; l++){
		for(c = 0; c < 2; c++){
			tresMaiores[l][c] = 0;
		}
	}

	for(i = 1; i <= compostos->size; i++){

		for(p = 0; p < mp->p; p++){
			for(l = 0; l < mp->l; l++){
				for(c = 0; c < mp->c; c++){
					/*Se o elemento da posição [l]inha, [c]oluna, [p]rofundidade
					* for igual ao composto na posição i do vetor de compostos
					* somamos 1 na posição i do vetor de quantidades
					*/
					if(mp->mapa[l][c][p].valor == compostos->vector[i]){
						qtd[i]+=1;
					}
				}
			}
		}

	}

	for(i = 1; i <= compostos->size; i++){
		if(qtd[i] > tresMaiores[0][1]){
			tresMaiores[2][0] = tresMaiores[1][0];
			tresMaiores[2][1] = tresMaiores[1][1];
			tresMaiores[1][0] = tresMaiores[0][0];
			tresMaiores[1][1] = tresMaiores[0][1];
			tresMaiores[0][0] = compostos->vector[i];
			tresMaiores[0][1] = qtd[i];
		}else if(qtd[i] > tresMaiores[1][1]){
			tresMaiores[2][0] = tresMaiores[1][0];
			tresMaiores[2][1] = tresMaiores[1][1];
			tresMaiores[1][0] = compostos->vector[i];
			tresMaiores[1][1] = qtd[i];
		}else if(qtd[i] > tresMaiores[2][1]){
			tresMaiores[2][0] = compostos->vector[i];
			tresMaiores[2][1] = qtd[i];
		}
	}
}

//Retorna o ponto que contém a camada mais espessa de petróleo e coloca em camadas a quantidade de camadas que a coluna de petróleo atravessa.
Ponto camadaMaisEspessaPetroleo(Mapeamento *mp, int *camadas){
	Ponto maisEspesso = mp->mapa[0][0][0];
	/*maisEspesso é o ponto na camada mais próxima a superfície.
	* camadas é a quantidade de camadas que o petroleo se estende
	*/
	int l, c, p;
	*camadas = 0;

	for(l = 0; l < mp->l; l++){
		for(c = 0; c < mp->c; c++){
			for(p = 0; p < mp->p; p++){
				if(mp->mapa[l][c][p].valor == 2){
					int z, qtd = 0;
					for(z = p; z < mp->p; z++){
						if(mp->mapa[l][c][z].valor == 2){
							qtd++;
						}
					}
					if(qtd > *camadas){
						maisEspesso = mp->mapa[l][c][p];
						*camadas = qtd;
					}
				}
			}
		}
	}

	return maisEspesso;
}

//Retorna um array com [profundidade],[area],[x],[y], sendo x e y as coordenadas centrais
int *fundoDoMar(Mapeamento *mp){
	int compostoAlvo = 0;
	int valorReposicao = -1;
	int l, c, p;
	for(l = 0; l < mp->l; l++){
		for(c = 0; c < mp->c; c++){
			for(p = 0; p < mp->p; p++){
				if(p+1 < mp->p){
					if(mp->mapa[l][c][p].valor == compostoAlvo && mp->mapa[l][c][p+1].valor != compostoAlvo){
						mp->mapa[l][c][p+1].valor = valorReposicao;
					}
				}
			}
		}
	}
	/*array maiorArea [profundidade],[area],[x],[y]
	* x e y sendo as coordenadas centrais
	*/
	int maiorArea[4] = {0,0};
	for(p = 0; p < mp->p; p++){
		int area = 0;
		for(l = 0; l < mp->l; l++){
			for(c = 0; c < mp->c; c++){
				if(mp->mapa[l][c][p].valor == valorReposicao){
					area++;
				}
			}
		}
		if(area > maiorArea[1]){
			maiorArea[0] = p;
			maiorArea[1] = area;
		}
	}


	/*		/--------------y-------------/
	*		/[				 ][			][	][			 ]
	*		|[				 ][			][	][			 ]
	*		x[				 ][cima	][-1][direita]
	*		|[esquerda][	-1	][-1][			 ]
	*		/[				 ][baixo][-1][			 ]
	*/
	Ponto esq = {0,0,mp->l,maiorArea[0]};
	Ponto dir = {0,0,0,maiorArea[0]};
	Ponto cima = {0,mp->c,0,maiorArea[0]};
	Ponto baixo = {0,0,0,maiorArea[0]};
	for(l = 0; l < mp->l; l++){
		for(c = 0; c < mp->c; c++){
			Ponto atual = mp->mapa[l][c][maiorArea[0]];

			if(atual.valor == valorReposicao){
				if(atual.y < esq.y){
					esq = atual;
				}else if(atual.y > dir.y){
					dir = atual;
				}

				if(atual.x < cima.x){
					cima = atual;
				}else if(atual.x > baixo.x){
					baixo = atual;
				}
			}
		}
	}

	maiorArea[2] = dir.y - esq.y;
	maiorArea[3] = baixo.x - cima.x;
	return maiorArea;
}

bool pontoEstaNoMapa(Mapeamento *mp, Ponto *pt){
	if(pt->x < 0 || pt->x >= mp->l || pt->y < 0 || pt->y >= mp->c || pt->z < 0 || pt->z >= mp->p){
		return false;
	}
	return true;
}

int floodFill2D(Mapeamento *mp, Ponto *pt, int compostoAlvo, int valorReposicao){
	int execucoes = 0; //quantas vezes ele foi executado
	if(!pontoEstaNoMapa(mp, pt)){
		return;
	}
	if(pt->valor == valorReposicao){
		return;
	}
	if(pt->valor != compostoAlvo){
		return;
	}
	int x = pt->x;
	int y = pt->y;
	int z = pt->z;
	mp->mapa[x][y][z].valor = valorReposicao;

	Ponto esq = {0, x, y-1, z}; //valor, x, y, z
	if(pontoEstaNoMapa(mp, &esq)){
		esq = mp->mapa[x][y-1][z];
	}
	Ponto dir = {0, x, y+1, z};
	if(pontoEstaNoMapa(mp, &dir)){
		dir = mp->mapa[x][y+1][z];
	}
	Ponto cima = {0, x-1, y, z};
	if(pontoEstaNoMapa(mp, &cima)){
		cima = mp->mapa[x-1][y][z];
	}
	Ponto baixo = {0, x+1, y, z};
	if(pontoEstaNoMapa(mp, &baixo)){
		baixo = mp->mapa[x+1][y][z];
	}
	execucoes += floodFill2D(mp, &esq, compostoAlvo, valorReposicao);
	execucoes += floodFill2D(mp, &dir, compostoAlvo, valorReposicao);
	execucoes += floodFill2D(mp, &cima, compostoAlvo, valorReposicao);
	execucoes += floodFill2D(mp, &baixo, compostoAlvo, valorReposicao);
	return execucoes;
}

int profundidadeMaisPetroleoConexo(Mapeamento *mp){
	int l, c, p;
	Mapeamento petroleo;
	equalizeMapeamento(mp, &petroleo);
	//array com [profundidade][volume]
	int profundidade[2] = {0,0};

	for(p = 0; p < petroleo.p; p++){
		for(l = 0; l < petroleo.l; l++){
			for(c = 0; c < petroleo.c; c++){
				if(petroleo.mapa[l][c][p].valor == 2){
					Ponto atual = petroleo.mapa[l][c][p];
					int volume = floodFill2D(&petroleo, &atual, 2, -1);
					if(volume > profundidade[1]){
						profundidade[0] = p;
						profundidade[1] = volume;
					}
				}
			}
		}
	}

	return profundidade[0];
}

int main(int argc, char *argv[]){
	Mapeamento mp;

	leTamanhoMapeamento(&mp.l, &mp.c, &mp.p);
	alocaMapeamento(&mp);
	preencheMapeamento(&mp);
	// imprimeMapeamento(&mp);

	//Questão 1
	Ponto maisProfundo = maiorProfundidadeMar(&mp);
	printf("Área explorada de %dKm² com maior profundidade na coordenada: %d x %d\n", mp.l*mp.c*100, maisProfundo.x, maisProfundo.y);

	//Questão 2
	List compostos;
	initializeList(&compostos);
	qtdCompostosDistintos(&mp, &compostos);
	printf("Compostos distintos identificados: %d (", compostos.size);
	formatQuestao2(&compostos);
	printf(")\n");

	//Questão 3
	Mapeamento fundoMar;
	equalizeMapeamento(&mp, &fundoMar);
	int *area;
	area = (int *) fundoDoMar(&fundoMar);
	printf("Maior área plana no fundo do mar: %dkm² (coordenadas centrais %d x %d)\n",
					area[1]*100, area[2], area[3]);
	freeMapeamento(&fundoMar);

	//Questão 4
	/*Três compostos com maior volume.
	* Vetor tresCompostos com três linhas e duas colunas.
	* [composto][qtd]
	* [composto][qtd]
	* [composto][qtd]
	*/
	int tresMaiores[3][2];
	compostosMaiorVolume(&mp, &compostos, tresMaiores);
	printf("Os 3 maiores compostos com maior volume em ordem crescente: %s, %s e %s\n",
					COMPOSTOS[tresMaiores[2][0]], COMPOSTOS[tresMaiores[1][0]], COMPOSTOS[tresMaiores[0][0]]);
	freeList(&compostos);

	//Questão 5
	int camadas;
	Ponto maisEspesso = camadaMaisEspessaPetroleo(&mp, &camadas);
	printf("Coordenada com a maior espessura de uma camada contínua de petróleo: ");
	printf("%d x %d com %d metros\n", maisEspesso.x, maisEspesso.y, camadas*1000);

	//Questão 6
	int profundidade = profundidadeMaisPetroleoConexo(&mp);
	printf("Profundidade com a maior área conexa de petróleo: %d metros\n", profundidade*1000);

	//Questão 7
	//Questão 8
	//Questão 9
}
