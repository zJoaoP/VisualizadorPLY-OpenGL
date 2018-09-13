#ifndef _PONTOS_
#define _PONTOS_ 1

struct listaDePontos{
	float x, y, z;
	struct listaDePontos* next;
};

struct listaDePontos * initListaDePontos(float x, float y, float z);

void freeListaDePontos(struct listaDePontos **l);
void inserirPonto(struct listaDePontos **l, float x, float y, float z);

int sizeListaDePontos(struct listaDePontos *l);

#endif