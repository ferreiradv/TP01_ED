#include <iostream>
#include <string>
#include <iomanip>
#include "Acao.hpp"
#include "Cliente.hpp"
#include "Ranking.hpp"
#include <chrono>
#define MAX 1000

ItemRanking** rankingRET = new ItemRanking*[MAX];
ItemRanking** rankingAVGRET = new ItemRanking*[MAX];
ItemRanking** rankingSTAB = new ItemRanking*[MAX];
ItemRanking** rankingCONS = new ItemRanking*[MAX];

void inserirOrdenado(ItemRanking** ranking, int& tamanho, int id, double valor) {
    int i = tamanho - 1;

    while (i >= 0 && ranking[i]->valor < valor) {
        ranking[i + 1] = ranking[i];
        i--;
    }

    ranking[i + 1] = new ItemRanking{id, valor};
    tamanho++;
}

int tamRET = 0, tamAVGRET = 0, tamSTAB = 0, tamCONS = 0;

using namespace std;
int main(){
    int w;
    char input;//recebera o primeiro caractere da linha

    Acao** acoes = nullptr;
    Cliente** clientes = nullptr;

   int numAcoes = 0, numClientes = 0;


    while(cin >> input){//loop principal do main

        if(input == 'M') {
            cin >> w;//recebe o w (tamanho do buffer circular)
                string metrica;
                getline(cin, metrica);
        }

        else if(input == 'A') {

            int id;
            cin >> id;
            //podemos assumir que as ações serão inseridas em ordem crescente de id,
            //então o id da próxima ação a ser inserida será igual ao número de ações já inseridas
            if(acoes == nullptr) {
                acoes = new Acao*[MAX]; 
                for(int i = 0; i < MAX; i++) {
                    acoes[i] = nullptr;
                }//inicializa o vetor de ações com nullptr
                //evitar segfault
            }

            acoes[id] = new Acao(id, w);
            numAcoes++;
            // calcula todas as métricas UMA VEZ
            double ret = acoes[id]->calcularRET();
            double avgret = acoes[id]->calcularAVGRET();
            double stab = acoes[id]->calcularSTAB();
            double cons = acoes[id]->calcularCONS();
            // insere em cada ranking
            inserirOrdenado(rankingRET, tamRET, id, ret);
            inserirOrdenado(rankingAVGRET, tamAVGRET, id, avgret);
            inserirOrdenado(rankingSTAB, tamSTAB, id, stab);
            inserirOrdenado(rankingCONS, tamCONS, id, cons);
        }
        else if(input == 'U'){
            int id;
            cin >> id;
             if(clientes == nullptr) {
                clientes = new Cliente*[MAX]; 
                for(int i = 0; i < MAX; i++) {
                    clientes[i] = nullptr;
                }//inicializa o vetor de clientes com nullptr
                //evitar segfault
            } 
            clientes[id] = criarCliente(id);
            numClientes++;
        }
        else if(input == 'P') {

            int id;
            double preco;
            //le a entrada de id e preco da ação, e adiciona o preço ao histórico da ação correspondente
            cin >> id >> preco;

            acoes[id]->adicionarPreco(preco);
        }
        else if(input == 'B') {

            int cliente, acao;
            cin >> cliente >> acao;
            //usa o metodo nativo do TAD cliente para comprar a ação.
            //adicionando a acao a carteira do cliente [array dinamico]
            comprarAcao(clientes[cliente], acao);
        }   
        else if(input == 'V') {

            int cliente, acao;
            cin >> cliente >> acao;
             //usa o metodo nativo do TAD cliente para vender a ação.
            //removendo a acao a carteira do cliente [array dinamico]
            venderAcao(clientes[cliente], acao);
        }


        //funcao mais complexa do projeto
else if(input == 'Q'){

    int idconsulta, cliente, n, nmetricas;
    cin >> idconsulta >> cliente >> n >> nmetricas; 

    string* metricas = new string[nmetricas];
    double* pesos = new double[nmetricas];

    for(int i = 0; i < nmetricas; i++){
        cin >> metricas[i] >> pesos[i];
    }

    if(clientes[cliente] == nullptr){
        delete[] metricas;
        delete[] pesos;
        continue;
    }

    int tamanhoCarteira = getNumAcoesCliente(clientes[cliente]);

    ItemRanking* rankingLocal = new ItemRanking[tamanhoCarteira];

    // inicializa
    for(int i = 0; i < tamanhoCarteira; i++){
        int idAcao = getAcaoCliente(clientes[cliente], i);
        rankingLocal[i].id = idAcao;
        rankingLocal[i].valor = 0;
    }

    // 🔹 para cada métrica, usar ranking já pronto
    for(int m = 0; m < nmetricas; m++){

        ItemRanking** rankingAtual = nullptr;
        int tamanhoRanking = 0;

        if(metricas[m] == "RET"){
            rankingAtual = rankingRET;
            tamanhoRanking = tamRET;
        }
        else if(metricas[m] == "AVGRET"){
            rankingAtual = rankingAVGRET;
            tamanhoRanking = tamAVGRET;
        }
        else if(metricas[m] == "STAB"){
            rankingAtual = rankingSTAB;
            tamanhoRanking = tamSTAB;
        }
        else if(metricas[m] == "CONS"){
            rankingAtual = rankingCONS;
            tamanhoRanking = tamCONS;
        }

        // percorre ranking global já ordenado
        for(int i = 0; i < tamanhoRanking; i++){
            int idAcao = rankingAtual[i]->id;
            double pontos = (tamanhoRanking - i) * pesos[m];

            // verifica se pertence ao cliente
            for(int j = 0; j < tamanhoCarteira; j++){
                if(rankingLocal[j].id == idAcao){
                    rankingLocal[j].valor += pontos;
                    break;
                }
            }
        }
    }

    // ordenar ranking local
    ItemRanking** ponteiros = new ItemRanking*[tamanhoCarteira];

    for(int i = 0; i < tamanhoCarteira; i++){
        ponteiros[i] = &rankingLocal[i];
    }

    if(tamanhoCarteira > 0)
        mergeSort(ponteiros, 0, tamanhoCarteira - 1);

    int limite = (n < tamanhoCarteira) ? n : tamanhoCarteira;

    // MELHORES
    for(int i = 0; i < limite; i++){
        cout << "R " << idconsulta << " M "
             << i << " "
             << ponteiros[i]->id << " ";

        cout << fixed << setprecision(2)
             << ponteiros[i]->valor << endl;
    }

    // PIORES
    for(int i = 0; i < limite; i++){
        int pos = tamanhoCarteira - 1 - i;

        cout << "R " << idconsulta << " P "
             << i << " "
             << ponteiros[pos]->id << " ";

        cout << fixed << setprecision(2)
             << ponteiros[pos]->valor << endl;
    }

    delete[] rankingLocal;
    delete[] ponteiros;
    delete[] metricas;
    delete[] pesos;
}

    }
for(int i = 0; i < MAX; i++){
    if(acoes != nullptr && acoes[i] != nullptr) delete acoes[i];
    if(clientes != nullptr && clientes[i] != nullptr) destruirCliente(clientes[i]);
}
    delete[] acoes;
    delete[] clientes;

    return 0;
}