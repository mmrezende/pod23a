#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define TAM 15
#define MIN 0
#define MAX 100

int n_trocas = 0;
int n_comps = 0;

/**Funções auxiliares*/
int fill(int vet[TAM]) {
    for(int c=0; c<TAM; c++) {
        vet[c] = (MIN + rand()) % (MAX - MIN + 1);
    }
}

void print(int vet[TAM]) {
    printf("{");
    for(int c=0; c<TAM; c++) {
        printf("%d", vet[c]);
        if(c != TAM - 1) printf(", ");
    }
    printf("}\n");
}

bool comp(int a, int b) {
    n_comps++;
    return a>b;
}

void troca(int* a, int* b) {
    n_trocas++;
    int aux = *a;
    *a = *b;
    *b = aux;
}

/**Algoritmos de ordenação*/
void bubble_sort(int vet[TAM]) {
    for(int i=0; i<TAM; i++) {
        int trocas_it = 0;
        for(int j=0; j<(TAM-1-i); j++) {
            if(comp(vet[j], vet[j+1])) {
                troca(vet+j, vet+j+1);
                trocas_it++;
            }
        }
        if(trocas_it == 0) break;
    }
}

int main() {
    srand(time(NULL));
    int vet[TAM];
    fill(vet);
    print(vet);

    bubble_sort(vet);
    print(vet);
}