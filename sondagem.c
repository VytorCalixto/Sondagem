#include <stdio.h>
#include <stdlib.h>
#include "list.c" //TAD Lista

const char *COMPOSTOS[256] = {"agua", "gas natural", "petroleo", "carvao", "xisto", "rocha", "uranio", "silica", "ouro", "diamante"};
 
typedef struct 
{
	//Valor (0-255) e coordenadas (x,y,z)
	int valor, x, y, z;
}Ponto;

typedef struct{
	Ponto ***mapa;
	//Dimensões do mapeamento, [l]inha, [c]oluna e [p]rofundidade
	int l,c,p;
}Mapeamento;

void alocaMapeamento(Mapeamento *mp);

void preencheMapeamento(Mapeamento *mp, char *argv[]);

void imprimeMapeamento(Mapeamento *mp);

//Retorna o ponto mais profundo da área mapeada do mar
Ponto maiorProfundidadeMar(Mapeamento *mp);

//"Retorna" o array compostos com os compostos distintos. A quantidade de compostos é o tamanho do array.
void qtdCompostosDistintos(Mapeamento *mp, List *compostos);

void addComposto(int composto, List *compostos);

//Formata o texto da questão 2
void formatQuestao2(List *compostos);

int main(int argc, char *argv[]){
	Mapeamento mp;
	mp.l = atoi(argv[1]);
	mp.c = atoi(argv[2]);
	mp.p = atoi(argv[3]);

	alocaMapeamento(&mp);
	preencheMapeamento(&mp, argv);
	// imprimeMapeamento(&mp);

	//Questão 1
	Ponto maisProfundo = maiorProfundidadeMar(&mp);
	printf("Área explorada de %dKm² com maior profundidade na coordenada: %dx%d\n", mp.l*mp.c*10, maisProfundo.x, maisProfundo.y);

	//Questão 2
	List compostos;
	initializeList(&compostos);
	qtdCompostosDistintos(&mp, &compostos);
	printf("\nCompostos distintos identificados: %d (", compostos.size);
	formatQuestao2(&compostos);
	printf(")\n");

}

void alocaMapeamento(Mapeamento *mp){
	int i,j,k;
	mp->mapa = (Ponto ***) malloc(sizeof(Ponto**) * mp->l);

	for(i=0; i < mp->l; i++){
		mp->mapa[i] = (Ponto **) malloc(sizeof(Ponto*) * mp->c);
		for(j=0; j < mp->c; j++){
			mp->mapa[i][j] = (Ponto *) malloc(sizeof(Ponto) * mp->p);
		}
	}

	return;
}

void preencheMapeamento(Mapeamento *mp, char *argv[]){
	int l, c, p, a = 4;

	for(p = 0; p < mp->p; p++){
		for(l = 0; l < mp->l; l++){
			for(c = 0; c < mp->c; c++){
				Ponto pt;
				pt.valor = atoi(argv[a]);
				pt.x = l;
				pt.y = c;
				pt.z = p;
				mp->mapa[l][c][p] = pt;
				a++;
			}
		}
	}

	return;
}

void imprimeMapeamento(Mapeamento *mp){
	int l, c, p;
	for(p = 0; p < mp->p; p++){
		for(l = 0; l < mp->l; l++){
			for(c = 0; c < mp->c; c++){
				printf("%d", mp->mapa[l][c][p].valor);
			}
			printf("\n");
		}
	}

	return;
}

Ponto maiorProfundidadeMar(Mapeamento *mp){
	Ponto maisProfundo = mp->mapa[0][0][0];
	int l, c, p;

	for(p = 0; p < mp->p; p++){
		for(l = 0; l < mp->l; l++){
			for(c = 0; c < mp->c; c++){
				if(mp->mapa[l][c][p].z > maisProfundo.z){
					maisProfundo = mp->mapa[l][c][p];
				}
			}
		}
	}

	return maisProfundo;
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

void addComposto(int composto, List *compostos){
	int i;

	if(composto == 0){
		return;
	}
	//i começa em 1, pois 0 é nodo cabeça
	for(i = 1; i <= compostos->size; i++){
		if((compostos->vector[i] == composto)){
			return;
		}
	}
	addList(composto, compostos);
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