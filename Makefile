all: sondagem

sondagem: sondagem.o compostos.o list.o mapeamento.o
  gcc -o sondagem sondagem.o compostos.o list.o mapeamento.o

sondagem.o: sondagem.c
  gcc -o sondagem.o -c sondagem.c -w

compostos.o: compostos.c
  gcc -o compostos.o -c compostos.c

list.o: list.c
  gcc -o list.o -c list.c

mapeamento.o: mapeamento.c
  gcc -o mapeamento.o -c mapeamento.c
