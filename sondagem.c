#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h> //Só funciona no C99 ou maior
#include "list.c" //TAD Lista
#include "mapeamento.c" //Tipo Mapeamento e Ponto
#include "compostos.c" //Deinições dos compostos

//Retorna true se o ponto esta no mapa, false caso contrario
bool pontoEstaNoMapa(Mapeamento *mp, Ponto *pt){
	return !(pt->x < 0 || pt->x >= mp->l || pt->y < 0 || pt->y >= mp->c || pt->z < 0 || pt->z >= mp->p);
}

//Retorna true se determinado ponto pt é o último ponto com valor AGUA da coluna e abaixo dele há algo diferente de AGUA
bool isFundoDoMar(Mapeamento *mp, Ponto *pt){
	Ponto acima = {-1, pt->x, pt->y, pt->z-1};
	if(pontoEstaNoMapa(mp, &acima)){
		acima = mp->mapa[pt->x][pt->y][pt->z-1];
	}
	Ponto abaixo = {-1, pt->x, pt->y, pt->z+1};
	if(pontoEstaNoMapa(mp, &abaixo)){
		abaixo = mp->mapa[pt->x][pt->y][pt->z+1];
	}
	//acima.valor == -1 e abaixo.valor == -1 significa que o ponto não está no mapa
	return (pt->valor == AGUA && (acima.valor == AGUA || acima.valor == -1) && (abaixo.valor != AGUA || abaixo.valor == -1));
}

//Retorna o ponto mais profundo mapeado
Ponto maiorProfundidadeMar(Mapeamento *mp){
	Ponto maisProfundo = mp->mapa[0][0][0];
	int l, c, p;

	for(p = 0; p < mp->p; p++){
		for(l = 0; l < mp->l; l++){
			for(c = 0; c < mp->c; c++){
				Ponto pt = mp->mapa[l][c][p];
				if(isFundoDoMar(mp, &pt) && pt.z > maisProfundo.z){
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
Ponto camadaMaisEspessaComposto(Mapeamento *mp, int *camadas, int composto){
	Ponto maisEspesso = mp->mapa[0][0][0];
	/*maisEspesso é o ponto na camada mais próxima a superfície.
	* camadas é a quantidade de camadas que o petroleo se estende
	*/
	int l, c, p;
	*camadas = 0;

	for(l = 0; l < mp->l; l++){
		for(c = 0; c < mp->c; c++){
			for(p = 0; p < mp->p; p++){
				if(mp->mapa[l][c][p].valor == composto){
					int z, qtd = 0;
					for(z = p; z < mp->p; z++){
						if(mp->mapa[l][c][z].valor != composto){
							break;
						}
						qtd++;
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

//Retorn quantas vezes a função foi chamada (ou quantos pontos alvo foram trocados)
int floodFill2D(Mapeamento *mp, Ponto *pt, int compostoAlvo, int valorReposicao){
	int execucoes = 0; //quantas vezes ele foi executado
	if(!pontoEstaNoMapa(mp, pt)){
		return execucoes;
	}
	if(pt->valor == valorReposicao){
		return execucoes;
	}
	if(pt->valor != compostoAlvo){
		return execucoes;
	}
	execucoes = 1;
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

//Retorna um array com [profundidade],[area],[x],[y], sendo x e y as coordenadas centrais
int *fundoDoMar(Mapeamento *mp){
	int areaPlana[4] = {0, 0}; //[profundidade],[area],[x],[y]
	int l, c, p, valorReposicao = -1, i;

	for(p = 0; p < mp->p; p++){
		for(l = 0; l < mp->l; l++){
			for(c = 0; c < mp->c; c++){
				Ponto pt = mp->mapa[l][c][p];
				if(isFundoDoMar(mp, &pt)){ //Se verdade, então elemento abaixo é diferente de água
					Ponto abaixo = {0, pt.x, pt.y, pt.z+1};
					if(pontoEstaNoMapa(mp, &abaixo)){
						mp->mapa[l][c][p+1].valor = valorReposicao;
					}
				}
			}
		}
	}
	//Ao fim dos loops, todo o fundo do mar terá valor -1

	for(p = 0; p < mp->p; p++){
		for(l = 0; l < mp->l; l++){
			for(c = 0; c < mp->c; c++){
				Ponto pt = mp->mapa[l][c][p];
				if(pt.valor == -1){
					valorReposicao--;
					int area = floodFill2D(mp, &pt, pt.valor, valorReposicao);
					if(area > areaPlana[1]){
						areaPlana[0] = p;
						areaPlana[1] = area;
						i = valorReposicao;
					}
				}
			}
		}
	}

	areaPlana[1] = 0;

	Ponto esq = {0,0,mp->l,areaPlana[0]};
	Ponto dir = {0,0,0,areaPlana[0]};
	Ponto cima = {0,mp->c,0,areaPlana[0]};
	Ponto baixo = {0,0,0,areaPlana[0]};
	for(l = 0; l < mp->l; l++){
		for(c = 0; c < mp->c; c++){
			Ponto atual = mp->mapa[l][c][areaPlana[0]];
			if(atual.valor == i){ // i contém o valor de reposição da maior área plana
				areaPlana[1] += 1;
				if(atual.y < esq.y){
					esq = atual;
				}
				if(atual.y > dir.y){
					dir = atual;
				}

				if(atual.x < cima.x){
					cima = atual;
				}
				if(atual.x > baixo.x){
					baixo = atual;
				}
			}
		}
	}

	areaPlana[2] = (baixo.x + cima.x)/2;
	areaPlana[3] = (dir.y + esq.y)/2;

	return &areaPlana;
}

//Mesma coisa que o 2D, mas com 3 dimensões.
int floodFill3D(Mapeamento *mp, Ponto *pt, int compostoAlvo, int valorReposicao){
	int execucoes = 0;
	if(!pontoEstaNoMapa(mp, pt)){
		return 0;
	}
	if(pt->valor == valorReposicao){
		return 0;
	}
	if(pt->valor != compostoAlvo){
		return 0;
	}
	int x = pt->x;
	int y = pt->y;
	int z = pt->z;
	mp->mapa[x][y][z].valor = valorReposicao;
	execucoes = 1;

	Ponto acima = {0, x, y, z-1}; //valor, x, y, z
	if(pontoEstaNoMapa(mp, &acima)){
		acima = mp->mapa[x][y][z-1];
	}

	Ponto abaixo = {0, x, y, z+1};
	if(pontoEstaNoMapa(mp, &abaixo)){
		abaixo = mp->mapa[x][y][z+1];
	}

	Ponto esq = {0, x, y-1, z};
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

	execucoes += floodFill3D(mp, &esq, compostoAlvo, valorReposicao);
	execucoes += floodFill3D(mp, &dir, compostoAlvo, valorReposicao);
	execucoes += floodFill3D(mp, &cima, compostoAlvo, valorReposicao);
	execucoes += floodFill3D(mp, &baixo, compostoAlvo, valorReposicao);

	execucoes += floodFill3D(mp, &acima, compostoAlvo, valorReposicao);
	execucoes += floodFill3D(mp, &abaixo, compostoAlvo, valorReposicao);

	return execucoes;
}

//Retorna a profundidade que possui mais petroleo conexo
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
	freeMapeamento(&petroleo);
	return profundidade[0];
}

//Retorna o volume do maior "agrupamento" (maior região conexa) de um composto
int maiorVolumeConexoComposto(Mapeamento *mp, int composto){
	int l, c, p, volume = 0, i = -1;
	Ponto pontoI = {i,0,0,0}; //ponto que gera um flood fill no maior volume encontrado

	for(p = 0; p < mp->p; p++){
		for(l = 0; l < mp->l; l++){
			for(c = 0; c < mp->c; c++){
				Ponto pt = mp->mapa[l][c][p];
				if(pt.valor == composto){
					int vl = floodFill3D(mp, &pt, composto, i);
					pt.valor = i;
					if(vl > volume){
						if(i != -1){
							floodFill3D(mp, &pontoI, pontoI.valor, composto);
						}
						volume = vl;
						pontoI = pt;
					}else{
						floodFill3D(mp, &pt, i, composto);
					}
					--i;
				}
			}
		}
	}

	floodFill3D(mp, &pontoI, pontoI.valor, -1); //Retorno para -1 para poder reutilizar
	return volume;
}

//Retorna o composto que possui o maior volume conexo
int compostoMaiorVolumeConexo(Mapeamento *mp){
	//array [composto][volume]
	int compostoMaiorVl[2];
	int l, c, p;

	for(l = 0; l < mp->l; l++){
		for(c = 0; c < mp->c; c++){
			for(p = 0; p < mp->p; p++){
				Ponto pt = mp->mapa[l][c][p];
				int volume = 0;
				if(pt.valor != 0){ //Se não for mar
					volume = floodFill3D(mp, &pt, pt.valor, -1);
					if(volume > compostoMaiorVl[1]){
						compostoMaiorVl[0] = pt.valor;
						compostoMaiorVl[1] = volume;
					}
				}
			}
		}
	}

	return compostoMaiorVl[0];
}

int main(int argc, char *argv[]){
	iniciaCompostos(); //É necessário inicar os compostos
	Mapeamento mp;

	leTamanhoMapeamento(&mp.l, &mp.c, &mp.p);
	alocaMapeamento(&mp);
	preencheMapeamento(&mp);
	// imprimeMapeamento(&mp);

	//Questão 1
	Ponto maisProfundo = maiorProfundidadeMar(&mp);
	printf("Area explorada de %dKm² com maior profundidade na coordenada: %d x %d\n", mp.l*mp.c*100, maisProfundo.x, maisProfundo.y);

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
	printf("Maior area plana no fundo do mar: %dkm² (coordenadas centrais %d x %d)\n",
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

	//Questão 5
	int camadas;
	Ponto maisEspesso = camadaMaisEspessaComposto(&mp, &camadas, 2);
	printf("Coordenada com a maior espessura de uma camada continua de petroleo: ");
	printf("%d x %d com %d metros\n", maisEspesso.x, maisEspesso.y, camadas*1000);

	//Questão 6
	int profundidade = profundidadeMaisPetroleoConexo(&mp);
	printf("Profundidade com a maior area conexa de petroleo: %d metros\n", profundidade*1000);

	//Questão 7
	Mapeamento petroleo;
	equalizeMapeamento(&mp, &petroleo);
	int volume = maiorVolumeConexoComposto(&petroleo, PETROLEO);
	printf("Maior volume de petroleo em regiao conexa: %dKm³\n",
				//Cada "cubo" tem dimensões x e y = 10Km e z = 1km. Logo, cada cubo tem 100Km³, ou, 100.000.000.000m³
				volume*100);

	//Questão 8
	maisEspesso = camadaMaisEspessaComposto(&petroleo, &camadas, -1);
	printf("Coordenada %d x %d tem a maior espessura da regiao conexa de petroleo com %d quilometros cubicos\n",
				maisEspesso.x, maisEspesso.y, volume*100);
	freeMapeamento(&petroleo);

	//Questão 9
	int composto = compostoMaiorVolumeConexo(&mp);
	printf("Dentre os %d compostos encontrados na area, a %s tem o maior volume conexo.\n",
				compostos.size, COMPOSTOS[composto]);

	freeList(&compostos);
	freeMapeamento(&mp);
	return;
}
