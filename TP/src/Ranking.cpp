#include "Ranking.hpp"

void merge(ItemRanking** arr, int esq, int meio, int dir) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;

    ItemRanking** L = new ItemRanking*[n1];
    ItemRanking** R = new ItemRanking*[n2];

    for (int i = 0; i < n1; i++) 
        L[i] = arr[esq + i];

    for (int j = 0; j < n2; j++) 
        R[j] = arr[meio + 1 + j];

    int i = 0, j = 0, k = esq;

    while (i < n1 && j < n2) {

        if (L[i]->valor > R[j]->valor || 
           (L[i]->valor == R[j]->valor && L[i]->id < R[j]->id)) {

            arr[k] = L[i];
            i++;
        } 
        else {
            arr[k] = R[j];
            j++;
        }

        k++;
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
}

void mergeSort(ItemRanking** arr, int esq, int dir) {

    if (esq < dir) {

        int meio = esq + (dir - esq) / 2;

        mergeSort(arr, esq, meio);
        mergeSort(arr, meio + 1, dir);

        merge(arr, esq, meio, dir);
    }
}

double obterValorMetrica(Acao* a, std::string tipo) {

    if (a == nullptr) return 0;

    if (tipo == "RET") return a->calcularRET();
    if (tipo == "AVGRET") return a->calcularAVGRET();
    if (tipo == "STAB") return a->calcularSTAB();
    if (tipo == "CONS") return a->calcularCONS();

    return 0;
}