#ifndef CLIENTE_HPP
#define CLIENTE_HPP

#include <string>

using namespace std;


class Cliente{
private:
int id;
ListaAcoes* carteira;// estrutura de dados a ser implementada para armazenar as ações do cliente

public:
void comprarAcao(Acao* acao);//adiciona ponteiro da açao a carteira
void venderAcao(Acao* acao);//remove ponteiro da açao da carteira
ListaAcoes* getCarteira();//retorna a carteira do cliente
};

#endif;