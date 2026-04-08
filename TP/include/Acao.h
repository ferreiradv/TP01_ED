#ifndef ACAO_HPP
#define ACAO_HPP

#include <string>

// Usar std:: explicitamente é preferível em headers para evitar poluição de nomes
class Acao {
private:
    int id;
    double* historicoPrecos; // Array de tamanho fixo 'w'
    int countPrecos;         // Total de preços recebidos (ajuda a saber se atingiu w)
    int indexAtual;          // Para o buffer circular
    int w;

public:
    // O construtor deve receber apenas ID e W. Ele aloca o array internamente.
    Acao(int id, int w);
    
    // Destrutor essencial para liberar o array historicoPrecos [cite: 257]
    ~Acao();

    // Getters
    int getId() const;
    int getW() const;

    // Métodos de negócio
    void adicionarPreco(double preco); // Adiciona e gerencia o buffer circular [cite: 71, 177]
    
    // Métodos de cálculo conforme as fórmulas do PDF [cite: 22, 47]
    double calcularRET() const;
    double calcularAVGRET() const;
    double calcularSTAB() const;
    double calcularCONS() const;
    
    // Retorna a métrica pedida (útil para a estratégia sob demanda)
    double getMetricValue(std::string metrica) const;

    // DICA: Para o desempate exigido no PDF, ter o ID acessível é vital [cite: 54, 94]
};

#endif