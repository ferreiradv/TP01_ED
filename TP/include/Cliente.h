#ifndef CLIENTE_H
#define CLIENTE_H

struct Cliente {
    int id;
    int* carteira;
    int tamanho;
    int capacidade;
};

Cliente* criarCliente(int id);
void comprarAcao(Cliente* c, int acao);
void venderAcao(Cliente* c, int acao);

#endif