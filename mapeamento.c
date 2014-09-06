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

void leTamanhoMapeamento(int *l, int *c, int *p){
  scanf("%d %d %d", l, c, p);
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
        printf("%d", mp->mapa[l][c][p].valor);
      }
      printf("\n");
    }
  }

  return;
}
