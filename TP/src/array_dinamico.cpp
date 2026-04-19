#include "array_dinamico.hpp"

ArrayDinamico* criarDinamico(int capacidade) {
    ArrayDinamico* arr = new ArrayDinamico;
    
    
    arr->capacidade = capacidade;
    arr->tamanho = 0;
    arr->dados = new int[arr->capacidade];

    return arr;
}

bool contem(ArrayDinamico* arr, int elemento){
    for(int i = 0; i < arr->tamanho; i++){
        if(arr->dados[i] == elemento)
            return true;
    }
    return false;
}

void aumentarCapacidade(ArrayDinamico* arr) {

    arr->capacidade *= 2;

    int* novo = new int[arr->capacidade];

    for(int i = 0; i < arr->tamanho; i++) {
        novo[i] = arr->dados[i];
    }

    delete[] arr->dados;
    arr->dados = novo;
}

void adicionar(ArrayDinamico* arr, int elemento) {

    if(contem(arr, elemento))
        return;

    if(arr->tamanho == arr->capacidade) {
        aumentarCapacidade(arr);
    }

    arr->dados[arr->tamanho] = elemento;
    arr->tamanho++;
}

void remover(ArrayDinamico* arr, int elemento) {

    for(int i = 0; i < arr->tamanho; i++) {

        if(arr->dados[i] == elemento) {

            for(int j = i; j < arr->tamanho - 1; j++) {
                arr->dados[j] = arr->dados[j + 1];
            }

            arr->tamanho--;
            return;
        }
    }
}

void destruir(ArrayDinamico* arr) {
    delete[] arr->dados;
    delete arr;
}
