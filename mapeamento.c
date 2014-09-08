typedef struct{
  //Valor (0-255) e coordenadas (x,y,z)
  int valor, x, y, z;
}Ponto;

typedef struct{
  Ponto ***mapa;
  //Dimensões do mapeamento, [l]inha, [c]oluna e [p]rofundidade
  int l,c,p;
}Mapeamento;

void leTamanhoMapeamento(int *l, int *c, int *p){
  scanf("%d %d %d", l, c, p);
}

void alocaMapeamento(Mapeamento *mp){
  int l,c;
  mp->mapa = (Ponto ***) malloc(sizeof(Ponto**) * mp->l);

  for(l = 0; l < mp->l; l++){
    mp->mapa[l] = (Ponto **) malloc(sizeof(Ponto*) * mp->c);
    for(c = 0; c < mp->c; c++){
      mp->mapa[l][c] = (Ponto *) malloc(sizeof(Ponto) * mp->p);
    }
  }

  return;
}

void freeMapeamento(Mapeamento *mp){
  int l, c, p;

  for(l = 0; l < mp->l; l++){
    for(c = 0; c < mp->c; c++){
      free(mp->mapa[l][c]);
    }
    free(mp->mapa[l]);
  }
  free(mp->mapa);
  mp->l = 0;
  mp->c = 0;
  mp->p = 0;
}

void preencheMapeamento(Mapeamento *mp){
  int l, c, p, a = 4;

  for(p = 0; p < mp->p; p++){
    for(l = 0; l < mp->l; l++){
      for(c = 0; c < mp->c; c++){
        Ponto pt;
        scanf("%d", &pt.valor);
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
        printf("%d ", mp->mapa[l][c][p].valor);
      }
      printf("\n");
    }
    printf("\n");
  }

  return;
}

/* Mapeamento a; leTamanhoMapeamento(&a); alocaMapeamento(&a); etc, etc
*  Mapeamento b;
*  b = a; Faz com que b.mapa (Ponto ***) aponte para a.mapa
*  Quando se modifica b.mapa, modifica-se a.mapa também
*
* equalizeMapeamento(a, b) faz com que os valores de b.mapa sejam iguais os de a.mapa, mas eles apontem para locais diferentes de memória.
*/
void equalizeMapeamento(Mapeamento *original, Mapeamento *copia){
  int l, c, p;
  copia->l = original->l;
  copia->c = original->c;
  copia->p = original->p;
  alocaMapeamento(copia);

  for(l = 0; l < original->l; l++){
    for(c = 0; c < original->c; c++){
      for(p = 0; p < original->p; p++){
        copia->mapa[l][c][p] = original->mapa[l][c][p];
      }
    }
  }
}
