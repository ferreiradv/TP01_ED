#include <iostream>
#include <string>
#include <iomanip>
#include "Acao.hpp"
#include "Cliente.hpp"


#define MAX 1000

struct Rankingaux{
    int id;
    double metrica;
    double pontuacao;
};

struct ItemRanking {
    int id;
    double valor;
};

void merge(ItemRanking** arr, int esq, int meio, int dir) {
    int n1 = meio - esq + 1;
    int n2 = dir - meio;

    // temps
    ItemRanking** L = new ItemRanking*[n1];
    ItemRanking** R = new ItemRanking*[n2];

    for (int i = 0; i < n1; i++) L[i] = arr[esq + i];
    for (int j = 0; j < n2; j++) R[j] = arr[meio + 1 + j];

    int i = 0, j = 0, k = esq;

    while (i < n1 && j < n2) {
        // criterio: maior valor primeiro. 
        // valores iguais -> menor ID primeiro
        if (L[i]->valor > R[j]->valor || (L[i]->valor == R[j]->valor && L[i]->id < R[j]->id)) {
            arr[k] = L[i];
            i++;
        } else {
            arr[k] = R[j];
            j++;
        }
        k++;
    }

    while (i < n1) arr[k++] = L[i++];
    while (j < n2) arr[k++] = R[j++];

    delete[] L;
    delete[] R;
    }

    void mergeSort(ItemRanking** arr, int esq, int dir) {
    if (esq < dir) {
        int meio = esq + (dir - esq) / 2;
        mergeSort(arr, esq, meio);
        mergeSort(arr, meio + 1, dir);
        merge(arr, esq, meio, dir);
    }
    }

    double obterValorMetrica(Acao* a, string tipo) {
    if (tipo == "RET") return a->calcularRET();
    if (tipo == "AVGRET") return a->calcularAVGRET();
    if (tipo == "STAB") return a->calcularSTAB();
    if (tipo == "CONS") return a->calcularCONS();
    return 0;
    }

using namespace std;
int main(){
    int w;
    char input;//recebera o primeiro caractere da linha

    Acao** acoes = nullptr;
    Cliente** clientes = nullptr;

   int numAcoes = 0, numClientes = 0;


    while(cin >> input){//loop principal do main

        if(input == 'M') {
            cin >> w;
        }

        else if(input == 'A') {

            int id;
            cin >> id;

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

            cin >> id >> preco;

            acoes[id]->adicionarPreco(preco);
        }
        else if(input == 'B') {

            int cliente, acao;
            cin >> cliente >> acao;

            comprarAcao(clientes[cliente], acao);
        }   
        else if(input == 'V') {

            int cliente, acao;
            cin >> cliente >> acao;

            venderAcao(clientes[cliente], acao);
        }

        else if(input == 'Q'){
    int idconsulta, cliente, n, nmetricas;
    cin >> idconsulta >> cliente >> n >> nmetricas; 

    string* metricas = new string[nmetricas];
    double* pesos = new double[nmetricas];

    for(int i = 0; i < nmetricas; i++){
        cin >> metricas[i] >> pesos[i];
    }

    Rankingaux* rankingglobal = new Rankingaux[MAX];

    for(int i = 0; i < MAX; i++){
        rankingglobal[i].pontuacao = 0;
        rankingglobal[i].id = i;
    }

    for(int m = 0; m < nmetricas; m++){

        ItemRanking** temporario = new ItemRanking*[numAcoes];
        int count = 0;

        for(int i = 0; i < MAX; i++){
            if(acoes[i] != nullptr){
                temporario[count] = new ItemRanking;
                temporario[count]->id = i;
                temporario[count]->valor = obterValorMetrica(acoes[i], metricas[m]);
                count++;
            }
        }

        mergeSort(temporario, 0, count - 1);

        for(int i = 0; i < count; i++){
            int idDaAcao = temporario[i]->id;
            double pontosGanhos = (count - i);
            rankingglobal[idDaAcao].pontuacao += pontosGanhos * pesos[m];
        }

        for(int i = 0; i < count; i++)
            delete temporario[i];

        delete[] temporario;
    }

    // FILTRAR CARTEIRA DO CLIENTE

    int tamanhoCarteira = getNumAcoesCliente(clientes[cliente]);

    ItemRanking* rankingLocal = new ItemRanking[tamanhoCarteira];

    for(int i = 0; i < tamanhoCarteira; i++){
        int idAcao = getAcaoCliente(clientes[cliente], i);
        rankingLocal[i].id = idAcao;
        rankingLocal[i].valor = rankingglobal[idAcao].pontuacao;
    }

    ItemRanking** ponteiros = new ItemRanking*[tamanhoCarteira];

    for(int i = 0; i < tamanhoCarteira; i++){
        ponteiros[i] = &rankingLocal[i];
    }

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
    for(int i = 0; i < numAcoes; i++){
        delete acoes[i];
    }
    for(int i = 0; i < numClientes; i++){
        destruirCliente(clientes[i]);
    }
    delete[] acoes;
    delete[] clientes;

    return 0;
}