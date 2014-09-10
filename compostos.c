//Definições para legibilidade do código
#define AGUA 0
#define GAS 1
#define PETROLEO 2
#define CARVAO 3
#define XISTO 4
#define ROCHA 5
#define URANIO 6
#define SILICA 7
#define OURO 8
#define DIAMANTE 9
#define CRISTAL 10
#define SAL 11
#define SELENIO 12
#define POLONIO 13
#define PRATA 14
#define PLATINA 15
#define GRAFITE 16
#define FOSSIL 17
#define FERRO 18
#define BASALTO 19
#define MAGNESIO 20
#define NIQUEL 21
#define PALADIO 22
#define CORAL 23
#define CALCARIO 24

#define DESCONHECIDO 255

char *COMPOSTOS[256] = {"agua", "gas natural", "petroleo", "carvao", "xisto",
                        "rocha", "uranio", "silica", "ouro", "diamante",
                        "cristal", "sal", "selenio", "polonio", "prata",
                        "platina", "grafite", "fossil", "ferro", "basalto",
                        "magnesio", "niquel", "paladio", "coral", "calcario"};

//Primeiro espaço é o tamanho
int METAIS[8] = {8, OURO, PRATA, PLATINA, FERRO, MAGNESIO, NIQUEL, PALADIO};
int ROCHAS[7] = {7, ROCHA, BASALTO, GRAFITE, CRISTAL, CORAL, CALCARIO};
int COMBUSTIVEIS[5] = {5, GAS, PETROLEO, CARVAO, XISTO};

void iniciaCompostos(){
  int i;
  for(i = 25; i < 256; i++){
    COMPOSTOS[i] = "desconhecido";
  }

}
