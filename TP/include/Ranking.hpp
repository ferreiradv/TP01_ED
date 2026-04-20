#ifndef RANKING_HPP
#define RANKING_HPP 


#include "Acao.hpp"
#include <string>

struct Rankingaux{
    int id;
    double metrica;
    double pontuacao;
};

struct ItemRanking {
    int id;
    double valor;
};

void merge(ItemRanking** arr, int esq, int meio, int dir);

void mergeSort(ItemRanking** arr, int esq, int dir);

double obterValorMetrica(Acao* a, std::string tipo);

#endif