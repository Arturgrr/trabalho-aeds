#include <stdlib.h>
#include "ordenacao.h"

void bubbleSort(Evento* eventos, int n) {
    for (int i = 0; i < n-1; i++) {
        for (int j = 0; j < n-i-1; j++) {
            if (eventos[j].avaliacao < eventos[j+1].avaliacao) {
                Evento temp = eventos[j];
                eventos[j] = eventos[j+1];
                eventos[j+1] = temp;
            }
        }
    }
}

void selectionSort(Evento* eventos, int n) {
    int i, j, Max;
    Evento x;
    
    for (i = 1; i <= n - 1; i++) {
        Max = i;
        for (j = i + 1; j <= n; j++) {
            if (eventos[j].avaliacao > eventos[Max].avaliacao) {
                Max = j;
            }
        }
        x = eventos[Max];
        eventos[Max] = eventos[i];
        eventos[i] = x;
    }
}

void insertionSort(Evento* eventos, int n) {
    int i, j;
    Evento x;
    
    for (i = 2; i <= n; i++) {
        x = eventos[i];
        j = i - 1;
        eventos[0] = x;
        while (x.avaliacao < eventos[j].avaliacao) {
            eventos[j+1] = eventos[j]; 
            j--;
        }
        eventos[j+1] = x;
    }
}

void shellSort(Evento* eventos, int n) {
    int i, j;
    int h = 1;
    Evento x;

    do {
        h = h * 3 + 1;
    } while (h < n);

    do {
        h /= 3; 

        for (i = h; i < n; i++) {
            x = eventos[i];
            j = i;

            while (j >= h && eventos[j - h].avaliacao < x.avaliacao) {
                eventos[j] = eventos[j - h];
                j -= h;
            }

            eventos[j] = x;
        }
    } while (h > 1);
}

int partition(Evento* eventos, int p, int r) {
    Evento x, aux;
    int i, j;
    
    x = eventos[r];
    i = p - 1;
    
    for(j = p; j < r; j++) {
        if (eventos[j].avaliacao >= x.avaliacao) {
            i = i + 1;
            aux = eventos[i];
            eventos[i] = eventos[j];
            eventos[j] = aux;
        }
    }
    
    aux = eventos[i + 1];
    eventos[i + 1] = eventos[r];
    eventos[r] = aux;
    
    return i + 1;
}

void quickSortHelper(Evento* eventos, int p, int r) {
    int q;
    
    if(p < r) {
        q = partition(eventos, p, r);
        quickSortHelper(eventos, p, q - 1);
        quickSortHelper(eventos, q + 1, r);
    }
}

void quickSort(Evento* eventos, int n) {
    quickSortHelper(eventos, 0, n-1);
}

void merge(Evento* eventos, int l, int m, int r) {
    int n1 = m - l + 1;
    int n2 = r - m;
    
    Evento* L = (Evento*)malloc(n1 * sizeof(Evento));
    Evento* R = (Evento*)malloc(n2 * sizeof(Evento));
    
    for (int i = 0; i < n1; i++)
        L[i] = eventos[l + i];
    for (int j = 0; j < n2; j++)
        R[j] = eventos[m + 1 + j];
    
    int i = 0, j = 0, k = l;
    while (i < n1 && j < n2) {
        if (L[i].avaliacao >= R[j].avaliacao) {
            eventos[k] = L[i];
            i++;
        } else {
            eventos[k] = R[j];
            j++;
        }
        k++;
    }
    
    while (i < n1) {
        eventos[k] = L[i];
        i++;
        k++;
    }
    
    while (j < n2) {
        eventos[k] = R[j];
        j++;
        k++;
    }
    
    free(L);
    free(R);
}

void mergeSortHelper(Evento* eventos, int l, int r) {
    if (l < r) {
        int m = l + (r - l) / 2;
        mergeSortHelper(eventos, l, m);
        mergeSortHelper(eventos, m + 1, r);
        merge(eventos, l, m, r);
    }
}

void mergeSort(Evento* eventos, int n) {
    mergeSortHelper(eventos, 0, n-1);
}

void heapify(Evento* eventos, int i, int n) {
    Evento aux;
    int esq = 2*i;
    int dir = 2*i+1;
    int maior;
    
    if((eventos[i].avaliacao < eventos[esq].avaliacao) && (esq <= n) && (esq >= 1)) {
        maior = esq;
    } else {
        maior = i;
    }
    
    if((eventos[maior].avaliacao < eventos[dir].avaliacao) && (dir <= n) && (dir >= 1)) {
        maior = dir;
    }
    
    if(maior != i) {
        aux = eventos[maior];
        eventos[maior] = eventos[i];
        eventos[i] = aux;
        heapify(eventos, maior, n);
    }
}

void buildMaxHeap(Evento* eventos, int n) {
    int i;
    for(i = n/2; i > 0; i--) {
        heapify(eventos, i, n);
    }
}

void heapSort(Evento* eventos, int n) {
    buildMaxHeap(eventos, n);
    
    for(int i = n; i > 1; i--) {
        Evento aux = eventos[1];
        eventos[1] = eventos[i];
        eventos[i] = aux;
        heapify(eventos, 1, i-1);
    }
} 