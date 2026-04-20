#ifndef CLIENTE_H
#define CLIENTE_H

#include "array_dinamico.hpp"

struct Cliente {
    int id;
    ArrayDinamico* carteira;
};

Cliente* criarCliente(int id);
void comprarAcao(Cliente* c, int acao);
void venderAcao(Cliente* c, int acao);
int getNumAcoesCliente(Cliente* c);
int getAcaoCliente(Cliente* c, int i);
void destruirCliente(Cliente* c);
#endif