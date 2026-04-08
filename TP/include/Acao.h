#ifndef ACAO_HPP
#define ACAO_HPP

#include <string>

using namespace std;


class Acao{
private:
int id;
double* HistoricoPrecos;
int numCot;
int w;

public:
    Acao(int id, double* HistoricoPrecos, int numCot, int w);
    int getId() const;
    double* getHistoricoPrecos() const;
    int getNumCot() const;
    int getW() const;
    double adicionarPreco(double preco);
    double calcularRET();
    double calcularAVGRET();
    double calcularSTAB();
    double CalcularCONS();
    double getScore(string Metrica);


};

#endif;