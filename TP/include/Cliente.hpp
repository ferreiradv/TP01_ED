#ifndef CLIENTE_H
#define CLIENTE_H

#include "array_dinamico.hpp"
//A estrutura cliente representa um cliente do sistema JOLAMBS, cada cliente contem um id unico e
//uma carteira de ações 
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