#include <iostream>
#include <unistd.h>
#include <fstream>

#include "TGrafoLista.h"

// Construtor do grafo com a lista de
// adjac�ncia
TGrafoLs::TGrafoLs(int n)
{
    // aloca a estrutura TGrafoLs
    this->n = n;
    this->m = 0;
    // aloca m vetor para guardar lista de adjacencias
    TNo **adjac = new TNo *[n];
    // Inicia o vetor com NULL
    for (int i = 0; i < n; i++)
        adjac[i] = nullptr;
    adj = adjac;
}

TGrafoLs::TGrafoLs(std::string arquivo)
{
    char buffer[FILENAME_MAX];
    getcwd(buffer, FILENAME_MAX);
    std::string b = {buffer};
    std::string full_path = b + "/" + arquivo;
    std::ifstream inFile(full_path);

    if (inFile)
    {
        inFile >> this->n;
        this->m = 0;
        // aloca m vetor para guardar lista de adjacencias
        TNo **adjac = new TNo *[n];
        // Inicia o vetor com NULL
        for (int i = 0; i < n; i++)
            adjac[i] = nullptr;
        adj = adjac;

        int a, de, para;
        inFile >> a;
        for (int i = 0; i < a; i++)
        {
            inFile >> de;
            inFile >> para;
            this->insereA(de, para);
        }
    }
    else
    {
        std::cerr << "Falha ao abrir arquivo" << std::endl;
        exit(1);
    }
}

/*
M�todo que cria uma aresta v-w no grafo. O m�todo sup�e que
v e w s�o distintos, positivos e menores que V.
Se o grafo j� tem a aresta v-w, o m�todo n�o faz nada.
O m�todo tamb�m atualiza a quantidade de arestas no grafo.
*/
void TGrafoLs::insereA(int v, int w)
{

    TNo *novoNo;
    // anda na lista para chegar ao final
    TNo *no = adj[v];
    TNo *ant = nullptr;
    // anda na lista enquanto no != NULL E w  > no->w
    while (no && w >= no->w)
    {
        if (w == no->w)
            return;
        ant = no;
        no = no->prox;
    };
    // cria o novo No para guardar w
    novoNo = new TNo;
    novoNo->w = w;
    novoNo->prox = no;
    // atualiza a lista
    if (ant == nullptr)
    {
        // insere no inicio
        adj[v] = novoNo;
    }
    else
        // insere no final
        ant->prox = novoNo;
    m++;
}
/*
M�todo que libera a mem�ria utilizada pela
lista de adjac�ncia.
*/
TGrafoLs::~TGrafoLs()
{
    // libera cada um dos nos da lista encadeada
    for (int i = 0; i < n; i++)
    {
        TNo *no = adj[i];
        TNo *ant = nullptr;
        while (no)
        {
            ant = no;
            no = no->prox;
            delete ant;
        }
    }
    n = 0;
    m = 0;
    // libera o vetor onde cada posicao apontava para uma lista encadeada
    delete[] adj;
};
/*
M�todo que remove do grafo a aresta que tem ponta inicial v
e ponta final w. O m�todo sup�e que v e w s�o distintos,
positivos e menores que V. Se n�o existe a aresta v-w,
o m�todo n�o faz nada. O m�todo tamb�m atualiza a
quantidade de arestas no grafo.
*/
void TGrafoLs::removeA(int v, int w)
{
    // Obt�m o in�cio da lista do v�rtice v
    TNo *no = adj[v];
    TNo *ant = nullptr;
    // Percorre a lista do v�rtice v
    // procurando w (se adjacente)
    while (no != nullptr && no->w != w)
    {
        ant = no;
        no = no->prox;
    }
    // Se w � adjacente, remove da lista de v
    if (no != nullptr)
    {
        ant->prox = no->prox;
        delete no;
        no = nullptr;
        m--;
    }
}
/*
Para cada v�rtice v do grafo, este m�todo imprime, em
uma linha, todos os v�rtices adjacentes ao v�rtice v
(vizinhos ao v�rtice v).
*/
void TGrafoLs::show()
{
    std::cout << "n: " << n;
    std::cout << "\nm: " << m;
    for (int i = 0; i < n; i++)
    {
        std::cout << "\n"
                  << i << ": ";
        // Percorre a lista na posi��o i do vetor
        TNo *no = adj[i];
        while (no)
        {
            std::cout << no->w << " ";
            no = no->prox;
        }
    }
    std::cout << std::endl
              << "fim da impressao do grafo." << std::endl;
}

void TGrafoLs::inverterVertices()
{
    for (int v = 0; v < n; v++)
    {
        if (adj[v])
        {
            TNo *a = adj[v];
            TNo *b = a->prox;
            TNo *c = nullptr;
            while (b)
            {
                a->prox = c;
                c = a;
                a = b;
                b = b->prox;
            }
            a->prox = c;
            adj[v] = a;
        }
    }
}

int TGrafoLs::ehFonte(int v){
    if(adj[v]!=nullptr){
        for (int i = 0; i < n; i++)
        {
            TNo *node = adj[i];
            while (node!=nullptr)
            {
                if(node->w == v)
                    return 0;
                node = node->prox;
            }
            
        }
        return 1;
    }
    return 0;
}

int TGrafoLs::ehSorvedouro(int v){
    if(adj[v]==nullptr){
        for (int i = 0; i < n; i++)
        {
            TNo *node = adj[i];
            while (node!=nullptr)
            {
                if(node->w == v)
                    return 1;
                node = node->prox;
            }
            
        }
    }
    return 0;
}

int TGrafoLs::ehSimetrico(){
    for (int i = 0; i < n; i++)
    {
        TNo *node = adj[i];
        while (node!=nullptr)
        {
            TNo *outro = adj[node->w];
            bool achou = false;
            while (outro!=nullptr)
            {
                if(outro->w == i){
                    achou = true;
                    break;
                }
                outro = outro->prox;
            }
            if(!achou)
                return 0;
            node = node->prox;
        }
    }
    return 1;
}