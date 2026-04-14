#include "Cliente.h"
#include <iostream>

Cliente* criarCliente(int id) {
    Cliente* c = new Cliente;
    
    c->id = id;
    c->capacidade = 10;
    c->tamanho = 0;
    c->carteira = new int[c->capacidade];

    return c;
}

void aumentarCapacidade(Cliente* c) {
    c->capacidade *= 2;
    
    int* novo = new int[c->capacidade];

    for(int i = 0; i < c->tamanho; i++) {
        novo[i] = c->carteira[i];
    }

    delete[] c->carteira;
    c->carteira = novo;
}
void comprarAcao(Cliente* c, int acao) {

    if( c->tamanho == c->capacidade)`{
        aumentarCapacidade(c);
    }

 c->carteira[c->tamanho] = acao;
 c->tamanho++;
}

void venderAcao(Cliente* c, int acao) {

    for(int i = 0; i < c->tamanho; i++) {

        if(c->carteira[i] == acao) {

            for(int j = i; j < c->tamanho - 1; j++) {
                c->carteira[j] = c->carteira[j+1];
            }

            c->tamanho--;
            return;
        }
    }
}
