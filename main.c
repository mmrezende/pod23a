#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <stdbool.h>

#define TAM 10
#define MIN 0
#define MAX 100

bool ordenado(int vet[TAM]) {
    for(int i=0; i<TAM-1; i++) {
        if(vet[i] > vet[i+1]) return false;
    }

    return true;
}

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
    printf(ordenado(vet) ? "ordenado!\n": "não está ordenado!\n");
}

/**Algoritmos de ordenação*/
void bubble_sort(int vet[TAM]) {
    for(int i=0; i<TAM; i++) {
        int trocas_it = 0;
        for(int j=0; j<(TAM-1-i); j++) {
            if(vet[j] > vet[j+1]) {
                int aux = vet[j];
                vet[j] = vet[j+1];
                vet[j+1] = aux;
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
        for(j=i-1; j>=0 && vet[j] > aux; j--) {
            vet[j+1] = vet[j];
        }
        vet[j+1] = aux;
    }
}

void shell_sort(int vet[TAM]) {
    for(int intervalo=(TAM + 1)/2; intervalo >=1; intervalo/=2) {
        for(int i=intervalo; i<TAM; i++) {
            int aux = vet[i];
            int j = i-intervalo;

            while(j>=0 && aux < vet[j]) {
                vet[j + intervalo] = vet[j];
                j -= intervalo;
            }
            
            vet[j+intervalo] = aux;
        }
    }
}

int main() {
    srand(time(NULL));
    int vet[TAM];
    fill(vet);
    print(vet);

    // bubble_sort(vet);
    // insertion_sort(vet);
    shell_sort(vet);
    print(vet);
}