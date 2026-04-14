#ifndef ARRAY_DINAMICO_H
#define ARRAY_DINAMICO_H

struct ArrayDinamico {
    int* dados;
    int tamanho;
    int capacidade;
};

ArrayDinamico* criarDinamico(int capacidade);
void aumentarCapacidade(ArrayDinamico* arr);
void adicionar(ArrayDinamico* arr, int elemento);
void remover(ArrayDinamico* arr, int elemento);


#endif