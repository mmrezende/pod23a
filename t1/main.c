#include "arv.h"

int main() {
    arv_t* arv = arv_cria();

    int dados[] = {8,5,15,12,19,9,13,23};
    for (size_t i = 0; i < sizeof(dados)/sizeof(int); i++)
    {
        arv_insere(arv, dados[i]);
    }
    arv_imprime(arv);

    // Testa quatro correções da inserção (raiz, tio vermelho, triângulo e linha)
    arv_insere(arv, 10);
    arv_imprime(arv);

    // Testa remoção com nó esquerdo vazio
    arv_remove(arv, 19);
    arv_imprime(arv);

    // Testa remoção com nó direito vazio
    arv_insere(arv, 1);
    arv_imprime(arv);
    arv_remove(arv, 5);
    arv_imprime(arv);

    // Testa remoção da raiz com nenhum dos nós vazio
    arv_remove(arv, 12);
    arv_imprime(arv);
    
    return EXIT_SUCCESS;
}