#include <iostream>
#include <string>
#include <iomanip>
#include "Acao.hpp"
#include "Cliente.hpp"
#include "Ranking.hpp"

#define MAX 1000

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
        //responsavel por processar a consulta e gerar o ranking das ações da carteira do cliente
        else if(input == 'Q'){
            //leitura dos parametros iniciais da consulta
    int idconsulta, cliente, n, nmetricas;
    cin >> idconsulta >> cliente >> n >> nmetricas; 
            
    //cria os vetores dinamicos da colsulta
    //pois o numero de metricas/pesos varia a cada consulta
    string* metricas = new string[nmetricas];
    double* pesos = new double[nmetricas];
    //leitura das metricas e pesos da consulta
    for(int i = 0; i < nmetricas; i++){
        cin >> metricas[i] >> pesos[i];
    }
    //leitura de dados finalizada

//-----------------------------------------------

    //inicio do processamento da consulta
    Rankingaux* rankingglobal = new Rankingaux[MAX];//vetor com a pontuação de TODAS as acoes 

    for(int i = 0; i < MAX; i++){//inicializa o vetor de ranking global
        rankingglobal[i].pontuacao = 0;
        rankingglobal[i].id = i;
    }

    for(int m = 0; m < nmetricas; m++){
        //para cada metrica da consulta, 
        //é gerado um ranking global de todas as ações, ordenado pelo valor da metrica

        ItemRanking** temporario = new ItemRanking*[numAcoes];//vetor auxiliar para o ranking temporario de cada metrica
        int count = 0;//conta quantas ações existem para a metrica, para saber o tamanho do vetor temporario

        for(int i = 0; i < MAX; i++){//percorre todas as acoes existentes
            if(acoes[i] != nullptr){
                temporario[count] = new ItemRanking;
                temporario[count]->id = i;
                temporario[count]->valor = obterValorMetrica(acoes[i], metricas[m]);
                count++;
                //calcula o valor da metrica para a ação e armazena no vetor temporario, junto com o id da ação
                //conta ações
            }
        }
        if(count > 0)
        mergeSort(temporario, 0, count - 1);//ordena as ações pela metrica usando o merge sort


        //calculo de pontuação
        //apos o ranking global ser gerado e ordenado
        //é calculada a pontuação de [count - i], como pedido no enunciado
        //e multiplicada pelo peso e soma
        for(int i = 0; i < count; i++){
            int idDaAcao = temporario[i]->id;
            double pontosGanhos = (count - i);
            rankingglobal[idDaAcao].pontuacao += pontosGanhos * pesos[m];
        }

        for(int i = 0; i < count; i++)//libera memoria
            delete temporario[i];

        delete[] temporario;
    }

    // FILTRAR CARTEIRA DO CLIENTE
    if(clientes[cliente] == nullptr)//se o cliente da consulta não existe, ignora a consulta e continua o loop
    continue;
    int tamanhoCarteira = getNumAcoesCliente(clientes[cliente]);//pega o numero de açoes do clinete

    ItemRanking* rankingLocal = new ItemRanking[tamanhoCarteira];//cria o vetor para ranking local

    for(int i = 0; i < tamanhoCarteira; i++){//filtragem das açoes do cliente, e consulta na pontuação do ranking global
        int idAcao = getAcaoCliente(clientes[cliente], i);
        rankingLocal[i].id = idAcao;
        rankingLocal[i].valor = rankingglobal[idAcao].pontuacao;
    }

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
    delete[] rankingglobal;
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