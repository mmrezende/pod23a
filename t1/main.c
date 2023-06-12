#include "arv.h"

int main() {
    arv_t* arv = arv_cria();

    int dados[] = {8,5,15,12,19,9,13,23};
    for (size_t i = 0; i < sizeof(dados)/sizeof(int); i++)
    {
        arv_insere(arv, dados[i]);
    }
    
    
    arv_imprime(arv);
    arv_insere(arv, 10);
    arv_imprime(arv);
    
    return EXIT_SUCCESS;
}