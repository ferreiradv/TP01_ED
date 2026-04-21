#ifndef ARRAY_DINAMICO_H
#define ARRAY_DINAMICO_H
//a estrutura de array dinamico sera usada para gerenciar a carteira dos clientes, permitindo adicionar e remover ações
//de forma eficiente e dinamica, otimizando o uso do memória e otimizado as operações
struct ArrayDinamico {
    int* dados;
    int tamanho;
    int capacidade;
};

ArrayDinamico* criarDinamico(int capacidade);
void aumentarCapacidade(ArrayDinamico* arr);
void adicionar(ArrayDinamico* arr, int elemento);
void remover(ArrayDinamico* arr, int elemento);
void destruir(ArrayDinamico* arr);
bool contem(ArrayDinamico* arr, int elemento);

#endif