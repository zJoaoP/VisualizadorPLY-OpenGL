#include <stdlib.h>
#include "pontos.h"

struct listaDePontos * initListaDePontos(float x, float y, float z){
	struct listaDePontos *l = (struct listaDePontos *) malloc(sizeof(struct listaDePontos));
	l->x = x;
	l->y = y;
	l->z = z;
	l->next = NULL;
	return l;
}

void freeListaDePontos(struct listaDePontos **l){
	if((*l)->next != NULL)
		freeListaDePontos(&((*l)->next));

	free(*l);
	(*l)->next = NULL;
}

void inserirPonto(struct listaDePontos **l, float x, float y, float z){
	if(*l == NULL)
		*l = initListaDePontos(x, y, z);
	else{
		struct listaDePontos *aux = initListaDePontos(x, y, z);
		aux->next = *l;
		*l = aux;
	}
}

int sizeListaDePontos(struct listaDePontos *l){
	if(l == NULL)
		return 0;
	else
		return 1 + sizeListaDePontos(l->next);
}