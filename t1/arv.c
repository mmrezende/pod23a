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
    bool isNil;
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
    self->isNil = false;
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
    if(aux->pai != NULL) {
        if(aux->pai->dir == self) {
            aux->pai->dir = aux;
        }else {
            aux->pai->esq = aux;
        }
    }
    self->pai = aux;
    self->dir = aux->esq;
    aux->esq = self;
    if(self->dir != NULL) self->dir->pai = self;

    return aux;
}

no_t* no_rotaciona_direita(no_t* self) {
    no_t* aux = self->esq;

    aux->pai = self->pai;
    if(aux->pai != NULL) {
        if(aux->pai->dir == self) {
            aux->pai->dir = aux;
        }else {
            aux->pai->esq = aux;
        }
    }
    self->pai = aux;
    self->esq = aux->dir;
    aux->dir = self;
    if(self->esq != NULL) self->esq->pai = self;

    return aux;
}

// corrige as regras na insersão da Árvore Red Black, retornando a nova raiz
no_t* no_corrige_insercao(no_t* self) {
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
        return no_corrige_insercao(avo);
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

    return no_corrige_insercao(pai); // o nó que viola a regra será sempre o pai original
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

void no_transplanta(no_t* u, no_t* v, no_t** raiz) {
    if(u->pai == NULL) *raiz = v;
    else if (u == u->pai->esq) u->pai->esq = v;
    else u->pai->dir = v;

    if(v != NULL) v->pai = u->pai;
}

no_t* no_minimo(no_t* self) {
    while(self->esq != NULL) self = self->esq;

    return self;
}

void no_corrige_remocao(no_t* self) {

    while(self->pai != NULL && self->isBlack) {
        no_t* irmao;
        if(self == self->pai->esq) {
            irmao = self->pai->dir;
            if(irmao != NULL && !irmao->isBlack) {
                irmao->isBlack = true;
                self->pai->isBlack = false;
                no_rotaciona_esquerda(self->pai);
                irmao = self->pai->dir;
            }

            if((irmao->esq == NULL || irmao->esq->isBlack) && (irmao->dir == NULL || irmao->dir->isBlack)) {
                irmao->isBlack = false;
                self = self->pai;
            }else {
                if (irmao->dir == NULL || irmao->dir->isBlack) {
                    if(irmao->esq != NULL) irmao->esq->isBlack = true;
                    irmao->isBlack = false;
                    no_rotaciona_direita(irmao);
                    irmao = self->pai->dir;
                }

                irmao->isBlack = self->pai == NULL || self->pai->isBlack;
                if(self->pai != NULL) self->pai->isBlack = true;
                if(irmao->dir != NULL) irmao->dir->isBlack = true;
                if(self->pai != NULL) no_rotaciona_esquerda(self->pai);

                while(self->pai != NULL) self = self->pai;
            }
        }else {
            irmao = self->pai->esq;
            if(irmao != NULL && !irmao->isBlack) {
                irmao->isBlack = true;
                self->pai->isBlack = false;
                no_rotaciona_direita(self->pai);
                irmao = self->pai->esq;
            }

            if((irmao->dir == NULL || irmao->dir->isBlack) && (irmao->esq == NULL || irmao->esq->isBlack)) {
                irmao->isBlack = false;
                self = self->pai;
            }else {
                if (irmao->esq == NULL || irmao->esq->isBlack) {
                    if(irmao->dir != NULL) irmao->dir->isBlack = true;
                    irmao->isBlack = false;
                    no_rotaciona_esquerda(irmao);
                    irmao = self->pai->esq;
                }

                irmao->isBlack = self->pai == NULL || self->pai->isBlack;
                if(self->pai != NULL) self->pai->isBlack = true;
                if(irmao->esq != NULL) irmao->esq->isBlack = true;
                if(self->pai != NULL) no_rotaciona_direita(self->pai);

                while(self->pai != NULL) self = self->pai;
            }
        }
    }

    self->isBlack = true;
}

no_t* no_cria_nil() {
    no_t* self = no_cria(0);
    self->dir = NULL;
    self->esq = NULL;
    self->isBlack = true;
    self->isNil = true;
    return self;
}

void no_remove(no_t* vitima, no_t** raiz) {
    bool wasBlack = vitima->isBlack;

    no_t* critico;
    if(vitima->esq == NULL) {
        critico = vitima->dir;
        if(critico == NULL) critico = no_cria_nil();
        no_transplanta(vitima, critico, raiz);
    } else if(vitima->dir == NULL) {
        critico = vitima->esq;
        if(critico == NULL) critico = no_cria_nil();
        no_transplanta(vitima, critico, raiz);
    } else {
        no_t* minimo_dir = no_minimo(vitima->dir);
        wasBlack = minimo_dir->isBlack;
        critico = minimo_dir->dir;
        if(critico == NULL) critico = no_cria_nil();
        
        if(minimo_dir->pai == vitima) {
            critico->pai = minimo_dir;
        }else {
            no_transplanta(minimo_dir, critico, raiz);
            minimo_dir->dir = vitima->dir;
            minimo_dir->dir->pai = minimo_dir;
        }

        no_transplanta(vitima, minimo_dir, raiz);
        minimo_dir->esq = vitima->esq;
        minimo_dir->esq->pai = minimo_dir;
        minimo_dir->isBlack = vitima->isBlack;
    }

    if(wasBlack) no_corrige_remocao(critico);

    vitima->dir = NULL;
    vitima->esq = NULL;
    no_destroi(vitima);
    if(critico->isNil) {
        critico->dir = NULL;
        critico->esq = NULL;
        if(critico->pai != NULL) {
            if(critico->pai->esq == critico) {
                critico->pai->esq = NULL;
            }else {
                critico->pai->dir = NULL;
            }
        }
        no_destroi(critico);
    }
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

    self->raiz = no_corrige_insercao(novo_no);
}

bool arv_remove(arv_t* self, dado_t dado) {
    no_t* vitima = no_busca(self->raiz, dado);
    if(vitima == NULL) return false;

    no_remove(vitima, &self->raiz);
    return true;
}

void arv_imprime(arv_t* self) {
    if(self->raiz == NULL) {
        printf("\n*árvore vazia*\n");
        return;
    }

    printf("\nraiz: ");
    no_imprime(self->raiz, 0);
}
