#include <stdio.h>
#include <stdlib.h>

const char *COMPOSTOS[255] = {"agua", "gas natural", "petroleo", "carvao", "xisto", "rocha", "uranio", "silica", "ouro", "diamante"}; 
 
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

int arrayLength(int *array){
	int length = 0;
	while(array[length]) 
		length++;
	return length;
}

void alocaMapeamento(Mapeamento *mp);

void preencheMapeamento(Mapeamento *mp, char *argv[]);

void imprimeMapeamento(Mapeamento *mp);

//Retorna o ponto mais profundo da área mapeada do mar
Ponto maiorProfundidadeMar(Mapeamento *mp);

//"Retorna" o array compostos com os compostos distintos. A quantidade de compostos é o tamanho do array.
void qtdCompostosDistintos(Mapeamento *mp, int *compsts);

void addComposto(int composto, int *compsts);

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
	int *compostos;
	compostos = (int *) malloc(sizeof(int));
	qtdCompostosDistintos(&mp, compostos);
	printf("\nCompostos distintos identificados: %d (", arrayLength(compostos));
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

void qtdCompostosDistintos(Mapeamento *mp, int *compsts){
	int l,c,p;

	for(p = 0; p < mp->p; p++){
		for(l = 0; l < mp->l; l++){
			for(c = 0; c < mp->c; c++){
				Ponto composto = mp->mapa[l][c][p];
				addComposto(composto.valor, compsts);
			}
		}
	}
	return;
}

void addComposto(int composto, int* compsts){
	int i;
	for(i = 0; i < arrayLength(compsts); i++){
		if((compsts[i] == composto) || (compsts[i] == 0)){
			return;
		}
	}
	compsts = (int *) realloc(compsts, (sizeof(int) * (arrayLength(compsts)+1) ));
	printf("%d ", arrayLength(compsts));
	// compsts[arrayLength(compsts)-1] = composto;
}