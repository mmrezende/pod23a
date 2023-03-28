#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define TAM 10
#define MIN 0
#define MAX 100

int n_escritas = 0;
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
    n_escritas+= 2;
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

void insertion_sort(int vet[TAM]) {
    for(int i=1;i<TAM;i++) {
        int aux = vet[i];
        int j;
        for(j=i-1; j>=0 && comp(vet[j], aux); j--) {
            vet[j+1] = vet[j];
            n_escritas++;
        }
        vet[j+1] = aux;
        n_escritas++;
    }
}

int main() {
    srand(time(NULL));
    int vet[TAM];
    fill(vet);
    print(vet);

    insertion_sort(vet);
    print(vet);
    printf("Escritas: %d, Comparações: %d\n", n_escritas, n_comps);
}