#include <iostream>
#include <string>
#include <iomanip>
#include "Acao.hpp"
#include "Cliente.hpp"
#include "Ranking.hpp"
#include <chrono>
#define MAX 1000

using namespace std;
int main()
{
    auto inicio1 = std::chrono::high_resolution_clock::now();
    int w;
    char input; // recebera o primeiro caractere da linha

    Acao **acoes = nullptr;
    Cliente **clientes = nullptr;

    int numAcoes = 0, numClientes = 0;

    while (cin >> input)
    { // loop principal do main

        if (input == 'M')
        {
            cin >> w; // recebe o w (tamanho do buffer circular)
            string metrica;
            getline(cin, metrica);
        }

        else if (input == 'A')
        {

            int id;
            cin >> id;
            // podemos assumir que as ações serão inseridas em ordem crescente de id,
            // então o id da próxima ação a ser inserida será igual ao número de ações já inseridas
            if (acoes == nullptr)
            {
                acoes = new Acao *[MAX];
                for (int i = 0; i < MAX; i++)
                {
                    acoes[i] = nullptr;
                } // inicializa o vetor de ações com nullptr
                // evitar segfault
            }

            acoes[id] = new Acao(id, w);
            numAcoes++;
        }
        else if (input == 'U')
        {
            int id;
            cin >> id;
            if (clientes == nullptr)
            {
                clientes = new Cliente *[MAX];
                for (int i = 0; i < MAX; i++)
                {
                    clientes[i] = nullptr;
                } // inicializa o vetor de clientes com nullptr
                // evitar segfault
            }
            clientes[id] = criarCliente(id);
            numClientes++;
        }
        else if (input == 'P')
        {

            int id;
            double preco;
            // le a entrada de id e preco da ação, e adiciona o preço ao histórico da ação correspondente
            cin >> id >> preco;

            if (acoes != nullptr && acoes[id] != nullptr)
            {
                acoes[id]->adicionarPreco(preco);
            }
        }
        else if (input == 'B')
        {

            int cliente, acao;
            cin >> cliente >> acao;
            if (clientes != nullptr && clientes[cliente] != nullptr &&
                acoes != nullptr && acoes[acao] != nullptr)
            { // so compra se o cliente e a ação existirem
                comprarAcao(clientes[cliente], acao);
            }
        }

        else if (input == 'V')
        {

            int cliente, acao;
            cin >> cliente >> acao;
            // usa o metodo nativo do TAD cliente para vender a ação.
            // removendo a acao a carteira do cliente [array dinamico]
            if (clientes != nullptr && clientes[cliente] != nullptr)
            {
                venderAcao(clientes[cliente], acao);
            }
        }

        // funcao mais complexa do projeto
        else if (input == 'Q')
        {
            
            int idconsulta, cliente, n, nmetricas;
            cin >> idconsulta >> cliente >> n >> nmetricas;

            string *metricas = new string[nmetricas];
            double *pesos = new double[nmetricas];

            for (int i = 0; i < nmetricas; i++)
            {
                cin >> metricas[i] >> pesos[i];
            }

            //-----------------------------------------------

            // ranking global
            Rankingaux *rankingglobal = new Rankingaux[MAX];

            for (int i = 0; i < MAX; i++)
            {
                rankingglobal[i].pontuacao = 0;
                rankingglobal[i].id = i;
            }

            // vetor aux para ordenação
            ItemRanking** temporario = new ItemRanking*[MAX];

            for (int m = 0; m < nmetricas; m++)
            {
                int count = 0;
                for(int i = 0; i < MAX; i++){
                    if(acoes != nullptr && acoes[i] != nullptr){
                        temporario[count] = new ItemRanking;
                        temporario[count]->id = i;
                        temporario[count]->valor = obterValorMetrica(acoes[i], metricas[m]);
                        count++;
                    }
                }

                if (count > 0)
                    mergeSort(temporario, 0, count - 1);

                // cálculo da pontuação
                for (int i = 0; i < count; i++)
                {
                    int idDaAcao = temporario[i]->id;
                    double pontosGanhos = (count - i);
                    rankingglobal[idDaAcao].pontuacao += pontosGanhos * pesos[m];
                }

                // limpeza do vetor temporário
                for (int i = 0; i < count; i++)
                {
                    delete temporario[i];
                }
            }

            delete[] temporario;

            //-----------------------------------------------

            if (clientes[cliente] == nullptr)
            {
                cout<< "o cliente " << cliente << " nao existe." << endl;  
                cout<<"portanto a consulta " << idconsulta << " nao pode ser processada." << endl;
                delete[] rankingglobal;
                delete[] metricas;
                delete[] pesos;
                continue;
            }

            int tamanhoCarteira = getNumAcoesCliente(clientes[cliente]);

            ItemRanking *rankingLocal = new ItemRanking[tamanhoCarteira];

            for (int i = 0; i < tamanhoCarteira; i++)
            {
                int idAcao = getAcaoCliente(clientes[cliente], i);
                rankingLocal[i].id = idAcao;
                rankingLocal[i].valor = rankingglobal[idAcao].pontuacao;
            }

            ItemRanking **ponteiros = new ItemRanking *[tamanhoCarteira];

            for (int i = 0; i < tamanhoCarteira; i++)
            {
                ponteiros[i] = &rankingLocal[i];
            }

            if (tamanhoCarteira > 0)
                mergeSort(ponteiros, 0, tamanhoCarteira - 1);

            //-----------------------------------------------

            int limite = (n < tamanhoCarteira) ? n : tamanhoCarteira;

            // MELHORES
            for (int i = 0; i < limite; i++)
            {
                cout << "R " << idconsulta << " M "
                     << i << " "
                     << ponteiros[i]->id << " ";

                cout << fixed << setprecision(2)
                     << ponteiros[i]->valor << endl;
            }

            // PIORES
            for (int i = 0; i < limite; i++)
            {
                int pos = tamanhoCarteira - 1 - i;

                cout << "R " << idconsulta << " P "
                     << i << " "
                     << ponteiros[pos]->id << " ";

                cout << fixed << setprecision(2)
                     << ponteiros[pos]->valor << endl;
            }

            //-----------------------------------------------
            delete[] rankingLocal;
            delete[] ponteiros;
            delete[] rankingglobal;
            delete[] metricas;
            delete[] pesos;

        }
    }
    for (int i = 0; i < MAX; i++)
    {
        if (acoes != nullptr && acoes[i] != nullptr)
            delete acoes[i];
        if (clientes != nullptr && clientes[i] != nullptr)
            destruirCliente(clientes[i]);
    }
    delete[] acoes;
    delete[] clientes;
            auto fim1 = std::chrono::high_resolution_clock::now();
            auto duration = std::chrono::duration_cast<std::chrono::microseconds>(fim1 - inicio1);
            cout << "Tempo gasto algoritmo 1: " << duration.count() << " microssegundos" << endl;
    return 0;
}
