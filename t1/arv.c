#include "arv.h"

struct no {
    dado_t val;
    // no_t *esq;
    // no_t *dir;
};

arv_t* arv_cria() {
    return malloc(sizeof(arv_t));
}

void arv_destroi(arv_t* self) {
    free(self);
}