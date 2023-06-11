#include "arv.h"

int main() {
    arv_t* arv = arv_cria();

    int dados[] = {6, 3, 64, -12, 0, 21, 13, 5};

    for (size_t i = 0; i < sizeof(dados)/sizeof(int); i++)
    {
        arv_insere(arv, dados[i]);
    }

    arv_imprime(arv);

    return EXIT_SUCCESS;
}