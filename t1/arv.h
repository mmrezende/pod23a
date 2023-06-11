#ifndef _ARV_H_
#define _ARV_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct arv arv_t; // Struct opaca do TAD
typedef int dado_t; // Tipo do dado armazenado nos nós da árvore

arv_t* arv_cria();
void arv_destroi(arv_t* self);
bool arv_busca(arv_t* self, dado_t dado);
void arv_insere(arv_t* self, dado_t dado);
bool arv_remove(arv_t* self, dado_t dado);
void arv_imprime(arv_t* self);

#endif