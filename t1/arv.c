#include "arv.h"

/**
 * Structs opacas
 * (foi optado por usar um descritor da árvore com o intuito de facilitar o caso arv->raiz == NULL)
*/

typedef struct no no_t;

struct no {
    dado_t dado;
    no_t *esq;
    no_t *dir;
};

struct arv {
    no_t* raiz;
};

/**
 * Funções auxiliares
*/

no_t* no_cria(dado_t dado) {
    no_t* self = calloc(1, sizeof(no_t));
    self->dado = dado;
    return self;
}

void no_destroi(no_t* self) {
    if(self->esq != NULL) no_destroi(self->esq);
    if(self->dir != NULL) no_destroi(self->dir);
    free(self);
}

// verdadeiro se o dado deve estar à esquerda do nó atual
bool no_cmp(no_t* self, dado_t dado) {
    return (dado < self->dado);
}

bool no_busca(no_t* self, dado_t dado) {
    if(self == NULL) return false;

    if(self->dado == dado) return true;
    if(no_cmp(self, dado)) return no_busca(self->esq, dado);
    return no_busca(self->dir, dado);
}

void no_insere(no_t* self, dado_t dado) {
    if(self->dado == dado) return; // nó já está na árvore

    if(no_cmp(self, dado))
        if(self->esq == NULL) self->esq = no_cria(dado);
        else no_insere(self->esq, dado);
    else
        if(self->dir == NULL) self->dir = no_cria(dado);
        else no_insere(self->dir, dado);
}

bool no_remove(no_t* self, dado_t dado) {
    return false;
}

void no_imprime(no_t* self, int nivel) {
    printf("%d\n", self->dado);
    
    for (int i = 0; i < nivel; i++) printf("\t");
    printf("dir: ");
    if(self->dir == NULL) printf("\n");
    else no_imprime(self->dir, nivel+1);

    for (int i = 0; i < nivel; i++) printf("\t");
    printf("esq: ");
    if(self->esq == NULL) printf("\n");
    else no_imprime(self->esq, nivel+1);
}

/**
 * Funções da interface
*/

arv_t* arv_cria() {
    return calloc(1, sizeof(arv_t));
}

void arv_destroi(arv_t* self) {
    if(self->raiz != NULL) no_destroi(self->raiz);
    free(self);
}

bool arv_busca(arv_t* self, dado_t dado) {
    return no_busca(self->raiz, dado);
}

void arv_insere(arv_t* self, dado_t dado) {
    if(self->raiz == NULL) self->raiz = no_cria(dado);

    no_insere(self->raiz, dado);
}

bool arv_remove(arv_t* self, dado_t dado) {
    if(self->raiz == NULL) return false;

    return no_remove(self->raiz, dado);
}

void arv_imprime(arv_t* self) {
    if(self->raiz == NULL) {
        printf("\n*árvore vazia*\n");
        return;
    }

    printf("\nraiz: ");
    no_imprime(self->raiz, 0);
}
