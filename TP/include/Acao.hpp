#ifndef ACAO_HPP
#define ACAO_HPP

#include <string>
//O TAD Ação possui um id unico e um historia de preços gerido por um buffer circular
//nos metodos são calculados os valores das metricas pedidas no enunciado.
class Acao {
private:
    int id;
    double* historicoPrecos; // Array de tamanho fixo 'w'
    int countPrecos;         // Total de preços recebidos (ajuda a saber se atingiu w)
    int indexAtual;          // Para o buffer circular
    int w;

public:
    Acao(int id, int w);
    
    ~Acao();

    // Getters
    int getId() const;
    int getW() const;

    // Métodos de negócio
    void adicionarPreco(double preco); 
    
    
    double calcularRET() const;
    double calcularAVGRET() const;
    double calcularSTAB() const;
    double calcularCONS() const;


};

#endif