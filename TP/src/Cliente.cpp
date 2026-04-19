#include "Cliente.hpp"

#include <iostream>

Cliente* criarCliente(int id) {

    Cliente* c = new Cliente;

    c->id = id;
    c->carteira = criarDinamico(10);

    return c;
}

void comprarAcao(Cliente* c, int acao){
    adicionar(c->carteira, acao);   
}

void venderAcao(Cliente* c, int acao){
    remover(c->carteira, acao);
}

int getNumAcoesCliente(Cliente* c){
    return c->carteira->tamanho;
}

int getAcaoCliente(Cliente* c, int i){
    return c->carteira->dados[i];
}

void destruirCliente(Cliente* c){
    destruir(c->carteira);
    delete c;
}
