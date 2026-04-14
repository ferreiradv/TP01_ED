#include "Acao.hpp"
#include <cmath>
#include <iostream>

Acao::Acao(int id, int w) {
    this->id = id;
    this->w = w;

    historicoPrecos = new double[w];

    countPrecos = 0;
    indexAtual = 0;
}
Acao::~Acao() {
    delete[] historicoPrecos;
}

//getters
        int Acao::getId() const {
            return id;
        }

        int Acao::getW() const {
            return w;
        }

void Acao::adicionarPreco(double preco) {

    historicoPrecos[indexAtual] = preco;

    indexAtual = (indexAtual + 1) % w;

    if(countPrecos < w) {
        countPrecos++;
    }
}

double Acao::calcularRET() const {

    if(countPrecos < w) return 0;

    int primeiro = indexAtual;
    int ultimo = (indexAtual + w - 1) % w;

    double p0 = historicoPrecos[primeiro];
    double pw = historicoPrecos[ultimo];

    return (pw / p0) - 1.0;
}

double Acao::calcularAVGRET() const {

    if(countPrecos < w) return 0;

    double soma = 0;

    for(int i = 1; i < w; i++) {

        int atual = (indexAtual + i) % w;
        int anterior = (indexAtual + i - 1) % w;

        double ri = (historicoPrecos[atual] / historicoPrecos[anterior]) - 1;

        soma += ri;
    }

    return soma / (w - 1);
}

double Acao::calcularSTAB() const {

    if(countPrecos < w) return 0;

    double media = calcularAVGRET();
    double soma = 0;

    for(int i = 1; i < w; i++) {

        int atual = (indexAtual + i) % w;
        int anterior = (indexAtual + i - 1) % w;

        double ri = (historicoPrecos[atual] / historicoPrecos[anterior]) - 1;

        soma += (ri - media) * (ri - media);
    }

    double vol = sqrt(soma / (w - 1));

    return 1.0 / (1.0 + vol);
}

double Acao::calcularCONS() const {

    if(countPrecos < w) return 0;

    int positivos = 0;

    for(int i = 1; i < w; i++) {

        int atual = (indexAtual + i) % w;
        int anterior = (indexAtual + i - 1) % w;

        double ri = (historicoPrecos[atual] / historicoPrecos[anterior]) - 1;

        if(ri > 0) positivos++;
    }

    return (double) positivos / (w - 1);
}

double Acao::getMetricValue(std::string metrica) const {

    if(metrica == "RET")
        return calcularRET();

    if(metrica == "AVGRET")
        return calcularAVGRET();

    if(metrica == "STAB")
        return calcularSTAB();

    if(metrica == "CONS")
        return calcularCONS();

    return 0;
}