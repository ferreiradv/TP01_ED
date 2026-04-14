#include "Cliente.h"

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
