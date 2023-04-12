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
int get_rand() {
    return (MIN + rand()) % (MAX - MIN + 1);
}

bool in_array(int vet[], size_t size, int value) {
    for(int c=0; c<size; c++) {
        if(vet[c] == value) return true;
    }

    return false;
}

int fill(int vet[TAM]) {
    for(int c=0; c<TAM; c++) {
        vet[c] = get_rand();
    }
}

int fill_unique(int vet[TAM]) {
    for(int c=0; c<TAM; c++) {
        int value;
        do {
            value = get_rand();
        } while(in_array(vet, c, value));
        vet[c] = value;
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

void quick_sort(int vet[], size_t start, size_t end) {
    if(start >= end || start < 0 || end < 0 ) return;
    printf("\nstart %d, end %d\n", start, end);

    int pivot = vet[start];
    int i = start, j = end;
    do {
        while(vet[i] < pivot) i++;
        while(vet[j] > pivot) j--;

        if(i<=j) {
            int aux = vet[i];
            vet[i] = vet[j];
            vet[j] = aux;
        }
    } while(i<j);
    printf("[Pivot %d, i %d, j %d] ", pivot, i, j);
    print(vet);

    if(i>start){
        printf("\t");
        quick_sort(vet, start, i-1);
    }

    if(i<end){
        printf("\t");
        quick_sort(vet, i+1, end);
    }
}

int main() {
    srand(time(NULL));
    int vet[TAM];

    // fill(vet);
    fill_unique(vet);

    print(vet);

    // bubble_sort(vet);
    // insertion_sort(vet);
    // shell_sort(vet);
    quick_sort(vet, 0, TAM-1);

    print(vet);
    printf(ordenado(vet) ? "ordenado!\n": "não está ordenado!\n");
}