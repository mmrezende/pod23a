#include "arv.h"

/**
 * Structs opacas
 * (foi optado por usar um descritor da árvore com o intuito de facilitar o caso arv->raiz == NULL)
*/

typedef struct no no_t;

struct no {
    dado_t dado;
    no_t *pai;
    no_t *esq;
    no_t *dir;
    bool isBlack;
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
    self->isBlack = false;
    return self;
}

void no_destroi(no_t* self) {
    if(self->esq != NULL) no_destroi(self->esq);
    if(self->dir != NULL) no_destroi(self->dir);
    free(self);
}

no_t* no_busca(no_t* self, dado_t dado) {
    if(self == NULL || self->dado == dado) return self;

    if(dado_cmp(self->dado, dado)) return no_busca(self->esq, dado);
    return no_busca(self->dir, dado);
}

no_t* no_rotaciona_esquerda(no_t* self) {
    no_t* aux = self->dir;
    
    aux->pai = self->pai;
    self->pai = aux;
    self->dir = aux->esq;
    aux->esq = self;
    if(self->dir != NULL) self->dir->pai = self;

    return aux;
}

no_t* no_rotaciona_direita(no_t* self) {
    no_t* aux = self->esq;
    aux->pai = self->pai;
    self->pai = aux;
    self->esq = aux->dir;
    aux->dir = self;
    if(self->esq != NULL) self->esq->pai = self;

    return aux;
}

// corrige as regras da Árvore Red Black, retornando a nova raiz
no_t* no_corrige_regras(no_t* self) {
    if(self->pai == NULL) {
        self->isBlack = true; // nó raiz sempre é preto
        return self;
    }

    no_t* pai = self->pai;
    no_t* avo = pai->pai;

    if(avo == NULL || pai->isBlack) { // nada a fazer
        while(self->pai != NULL) self = self->pai;
        return self;
    }

    no_t* tio = avo->esq == pai ? avo->dir : avo->esq;

     if(tio != NULL && !tio->isBlack) { // tio é vermelho, muda a cor do pai, tio e avô
        pai->isBlack ^= true;
        tio->isBlack ^= true;
        avo->isBlack ^= true;
        return no_corrige_regras(avo);
    }

    if(avo->esq == pai) {
        if(pai->dir == self) { // caso triângulo (à esquerda)
            no_rotaciona_esquerda(pai);
        } else { // caso linha (à esquerda)
            pai->isBlack ^= true;
            avo->isBlack ^= true;
            no_rotaciona_direita(avo);
        }
    }else {
        if(pai->esq == self) { // caso triângulo (à direita)
            no_rotaciona_direita(pai);
        } else { // caso linha (à direita)
            pai->isBlack ^= true;
            avo->isBlack ^= true;
            no_rotaciona_esquerda(avo);
        }
    }

    return no_corrige_regras(pai); // o nó que viola a regra será sempre o pai original
}

// Insere o nó, retornando um ponteiro para o mesmo
no_t* no_insere(no_t* self, dado_t dado) {
    if(self == NULL) {
        return no_cria(dado);
    }

    if(self->dado == dado) return self; // nó já está na árvore

    no_t* novo_no;
    if(dado_cmp(self->dado, dado)) {
        novo_no = no_insere(self->esq, dado);
        self->esq = novo_no;
        novo_no->pai = self;
    } else {
        novo_no =  no_insere(self->dir, dado);
        self->dir = novo_no;
        novo_no->pai = self;
    }

    return self;
}

bool no_remove(no_t* self, dado_t dado) {
    return false;
}

void no_imprime(no_t* self, int nivel) {
    printf("%d(%c)\n", self->dado, self->isBlack ? 'B' : 'R');
    
    for (int i = 0; i < nivel+1; i++) printf("\t");
    printf("dir: ");
    if(self->dir == NULL) printf("nil\n");
    else no_imprime(self->dir, nivel+1);

    for (int i = 0; i < nivel+1; i++) printf("\t");
    printf("esq: ");
    if(self->esq == NULL) printf("nil\n");
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
    return no_busca(self->raiz, dado)!=NULL;
}

void arv_insere(arv_t* self, dado_t dado) {
    self->raiz = no_insere(self->raiz, dado);
    no_t* novo_no = no_busca(self->raiz,dado);

    self->raiz = no_corrige_regras(novo_no);
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
