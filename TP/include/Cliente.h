#ifndef CLIENTE_H
#define CLIENTE_H

#include "array_dinamico.h"

struct Cliente {
    int id;
    ArrayDinamico* carteira;
};

Cliente* criarCliente(int id);
void comprarAcao(Cliente* c, int acao);
void venderAcao(Cliente* c, int acao);

#endif