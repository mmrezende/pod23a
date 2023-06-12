#include "arv.h"

int main() {
    arv_t* arv = arv_cria();

    arv_insere(arv, 1);

    arv_imprime(arv);

    return EXIT_SUCCESS;
}