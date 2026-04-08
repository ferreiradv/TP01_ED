template <typename T>
class Vetor {
private:
    T* itens;
    int capacidade;
    int tamanho;

    void redimensionar(int novaCapacidade);

public:
    Vetor();
    ~Vetor(); // Importante para evitar vazamento de memória
    void adicionar(T item);
    T& obter(int indice);
    int getTamanho();
    void remover(int indice);
};