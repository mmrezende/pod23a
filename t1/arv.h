#ifndef _ARV_H_
#define _ARV_H_

#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

typedef struct no no_t; // Struct opaca do TAD
typedef no_t arv_t; // Sinônimos
typedef int dado_t; // Tipo do dado armazenado nos nós da árvore

arv_t* arv_cria();
void arv_destroi(arv_t* self);

#endif