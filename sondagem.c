#include <stdio.h>
#include <stdlib.h>
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

int main(int argc, char *argv[]){
	Mapeamento mp;

	leTamanhoMapeamento(&mp.l, &mp.c, &mp.p);
	alocaMapeamento(&mp);
	preencheMapeamento(&mp);
	// imprimeMapeamento(&mp);

	//Questão 1
	Ponto maisProfundo = maiorProfundidadeMar(&mp);
	printf("Área explorada de %dKm² com maior profundidade na coordenada: %d x %d\n", mp.l*mp.c*10, maisProfundo.x, maisProfundo.y);

	//Questão 2
	List compostos;
	initializeList(&compostos);
	qtdCompostosDistintos(&mp, &compostos);
	printf("Compostos distintos identificados: %d (", compostos.size);
	formatQuestao2(&compostos);
	printf(")\n");

	//Questão 3

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
	//Questão 7
	//Questão 8
	//Questão 9
}
