#include <iostream>
#include <fstream>

#include "TGrafo.h"
#include "Matriz.h"

using namespace std;

#include <unistd.h>
#include <queue>
#include <stack>
#include <limits.h>
std::string cwda()
{
    char buffer[FILENAME_MAX];
    if (getcwd(buffer, FILENAME_MAX) != nullptr)
    {
        return {buffer};
    }
    return "";
}

void preencherFechoTransitivoDireto(int **matriz, int *atingiveis, int n, int v)
{
    atingiveis[v] = 1;
    for (int i = 0; i < n; i++)
    {
        if (!atingiveis[i])
        {
            if (matriz[v][i])
            {
                preencherFechoTransitivoDireto(matriz, atingiveis, n, i);
            }
        }
    }
}
void preencherFechoTransitivoInverso(int **matriz, int *atinge, int n, int v)
{
    atinge[v] = 1;
    for (int i = 0; i < n; i++)
    {
        if (!atinge[i])
        {
            if (matriz[i][v])
            {
                preencherFechoTransitivoInverso(matriz, atinge, n, i);
            }
        }
    }
}

// Construtor do TGrafo, respons�vel por
// Criar a matriz de adjac�ncia v x v do Grafo
TGrafo::TGrafo(int n)
{
    this->n = n;
    // No in�cio dos tempos n�o h� arestas
    this->m = 0;
    // aloca da matriz do TGrafo
    int **adjac = new int *[n];
    for (int i = 0; i < n; i++)
        adjac[i] = new int[n];
    adj = adjac;
    // Inicia a matriz com zeros
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;
}

TGrafo::TGrafo(std::string arquivo)
{
    std::string full_path = cwda() + "/" + arquivo;
    std::ifstream inFile(full_path);

    if (inFile)
    {
        inFile >> this->n;

        this->m = 0;

        this->adj = new int *[n];
        for (int i = 0; i < n; i++)
            this->adj[i] = new int[n];

        // Inicia a matriz com zeros
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adj[i][j] = 0;

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

// Destructor, responsavel por
// liberar a memoria alocada para a matriz
TGrafo::~TGrafo()
{
    n = 0;
    m = 0;
    delete[] *adj;
    std::cout << "espaço liberado" << std::endl;
}

// Insere uma aresta no Grafo tal que
// v � adjacente a w
void TGrafo::insereA(int v, int w)
{
    // testa se nao temos a aresta
    if (adj[v][w] == 0)
    {
        adj[v][w] = 1;
        m++; // atualiza qtd arestas
    }
}

void TGrafo::insereA(int v, int w, int p)
{
    // testa se nao temos a aresta
    if (adj[v][w] == 0)
    {
        m++;
    }
    adj[v][w] = p;
}

// remove uma aresta v->w do Grafo
void TGrafo::removeA(int v, int w)
{
    // testa se temos a aresta
    if (adj[v][w] == 1)
    {
        adj[v][w] = 0;
        m--; // atualiza qtd arestas
    }
}
void TGrafo::removeV(int v)
{
    for (int i = 0; i < this->n; i++)
    {
        if (i != v)
        {
            for (int j = 0; j < this->n; j++)
            {
                if (j > v)
                {
                    this->adj[i][j - 1] = this->adj[i][j];
                }
            }
            if (i > v)
            {
                adj[i - 1] = adj[i];
            }
        }
        else
        {
            delete[] adj[i];
        }
    }
    this->n--;
}

// Apresenta o Grafo contendo
// n�mero de v�rtices, arestas
// e a matriz de adjac�ncia obtida
void TGrafo::show()
{
    std::cout << "n: " << n << std::endl;
    std::cout << "m: " << m << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << "\n";
        for (int w = 0; w < n; w++)
            if (adj[i][w] == 1)
                std::cout << "Adj[" << i << "," << w << "]= 1"
                          << " ";
            else
                std::cout << "Adj[" << i << "," << w << "]= 0"
                          << " ";
    }
    cout << "\nfim da impressao do grafo." << endl;
}

int TGrafo::inDegree(int v)
{
    int r = 0;
    for (size_t i = 0; i < this->n; i++)
        if (this->adj[i][v])
            r++;
    return r;
}

int TGrafo::outDegree(int v)
{
    int r = 0;
    for (size_t i = 0; i < this->n; i++)
        if (this->adj[v][i])
            r++;
    return r;
}

int TGrafo::ehFonte(int v)
{
    return outDegree(v) > 0 && inDegree(v) == 0;
}

int TGrafo::ehSorvedouro(int v)
{
    return inDegree(v) > 0 && outDegree(v) == 0;
}

int TGrafo::ehSimetrico()
{
    for (size_t i = 0; i < this->n; i++)
        for (size_t j = 0; j < this->n; j++)
            if (this->adj[i][j] != this->adj[j][i])
                return 0;
    return 1;
}

int TGrafo::removerVertice(int v)
{
    if (v >= this->n)
        return 0;

    int **adjac = new int *[n - 1];
    m = 0;

    int i_completos = 0;

    for (int i = 0; i < n; i++)
    {
        adjac[i] = new int[n - 1];
        if (i != v)
        {
            int j_completos = 0;
            for (int j = 0; j < n; j++)
            {
                if (j != v)
                {
                    adjac[i_completos][j_completos] = this->adj[i][j];
                    j_completos++;
                    if (this->adj[i][j] != 0)
                        m++;
                }
            }
            i_completos++;
        }
        delete[] adj[i];
    }
    delete adj;
    adj = adjac;
    n = n - 1;

    return 1;
}

int TGrafo::ehCompleto()
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            if (i != j && adj[i][j] == 0)
                return 0;
    return 1;
}

int TGrafo::ehEquivalente(TGrafoLs *outro)
{
    if (m != outro->m)
        return 0;

    for (int v = 0; v < n; v++)
    {
        TNo *proximo = outro->adj[v];
        while (proximo != nullptr)
        {
            if (!adj[v][proximo->w])
                return false;
            proximo = proximo->prox;
        }
    }
    return 1;
}

TGrafo *TGrafo::complementar()
{
    TGrafo *c = new TGrafo(this->n);
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            if (adj[i][j] == 0)
                c->insereA(i, j);
    return c;
}

TGrafo *TGrafo::reduzido()
{
    int *atingidos = (int *)malloc(sizeof(int) * n);
    int *atingem = (int *)malloc(sizeof(int) * n);

    // cada pos de grupos em q grupo está o vertice no index
    int *grupo = (int *)malloc(sizeof(int) * n);
    int qtd_grupos = 0;

    for (int i = 0; i < n; i++)
        grupo[i] = -1;

    for (int v = 0; v < n; v++)
    {
        // se ainda nao foi movido para um grupo
        if (grupo[v] == -1)
        {
            grupo[v] = qtd_grupos;

            // limpa
            for (int i = 0; i < n; i++)
            {
                atingidos[i] = 0;
                atingem[i] = 0;
            }

            // preenche
            preencherFechoTransitivoDireto(this->adj, atingidos, n, v);
            preencherFechoTransitivoInverso(this->adj, atingem, n, v);

            for (int i = 0; i < n; i++)
            {
                if (grupo[i] == -1 && atingidos[i] && atingem[i])
                {
                    grupo[i] = qtd_grupos;
                }
            }
            qtd_grupos++;
        }
    }

    TGrafo *c = new TGrafo(qtd_grupos);

    // associa as arestas
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (adj[i][j] && grupo[i] != grupo[j])
            {
                c->insereA(grupo[i], grupo[j]);
            }
        }
    }

    free(atingem);
    free(atingidos);
    free(grupo);

    return c;
}
TGrafoLs *TGrafo::paraLista()
{
    TGrafoLs *lista = new TGrafoLs(n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (adj[i][j])
                lista->insereA(i, j);
        }
    }
    return lista;
}

int TGrafo::categoriaConexidade()
{
    int *atingidos = (int *)malloc(sizeof(int) * n);
    int *atingem = (int *)malloc(sizeof(int) * n);

    int categoria = 3;

    // verifica por desconexo
    for (int i = 0; i < n; i++)
    {
        int sum = 0;
        for (int j = 0; j < n; j++)
            sum += adj[i][j] + adj[j][i];
        if (sum == 0)
        {
            categoria = 0;
            break;
        }
    }
    if (categoria > 0)
        for (int v = 0; v < n; v++)
        {
            // limpa
            for (int i = 0; i < n; i++)
            {
                atingidos[i] = 0;
                atingem[i] = 0;
            }

            // preenche
            preencherFechoTransitivoDireto(this->adj, atingidos, n, v);
            preencherFechoTransitivoInverso(this->adj, atingem, n, v);

            if (categoria == 3)
            {
                for (int i = 0; i < n; i++)
                    if (!atingidos[i])
                    {
                        categoria--;
                        break;
                    }
            }
            if (categoria == 2)
            {
                for (int i = 0; i < n; i++)
                    if (!atingidos[i] && !atingem[i])
                    {
                        categoria--;
                        break;
                    }
            }

            // // imprime
            // for (int i = 0; i < n; i++)
            //     std::cout << atingidos[i] << ' ';
            // std::cout << "    ";
            // for (int i = 0; i < n; i++)
            //     std::cout << atingem[i] << ' ';
            // std::cout << std::endl;
        }

    free(atingidos);
    free(atingem);
    return categoria;
}

int TGrafo::ordenacaoTopologica(int *vec)
{
    std::queue<int> fila;

    int *grausDeEntrada = (int *)malloc(sizeof(int) * this->n);
    for (int i = 0; i < this->n; i++)
        for (int j = 0; j < this->n; j++)
            grausDeEntrada[i] += adj[j][i];

    int qtdFeitos = 0;
    for (int i = 0; i < this->n; i++)
    {
        if (grausDeEntrada[i] == 0)
        {
            //"esvazia" o vetor
            for (int j = 0; j < this->n; j++)
                vec[j] = -1;

            fila.push(i);
            while (!fila.empty())
            {
                for (int j = 0; j < this->n; j++)
                {
                    if (this->adj[fila.front()][j] && vec[j] == -1)
                    {
                        grausDeEntrada[j]--;
                        if (grausDeEntrada[j] == 0)
                            fila.push(j);
                    }
                }
                vec[fila.front()] = qtdFeitos++;
                fila.pop();
            }
            break;
        }
    }
    free(grausDeEntrada);
    return qtdFeitos > 0;
}

void TGrafo::percursoEmLargura(int inicio, int *vec)
{
    std::queue<int> fila;

    for (int i = 0; i < n; i++)
    {
        vec[i] = -1;
    }

    fila.push(inicio);

    int qtd = 0;
    while (!fila.empty())
    {
        for (int i = 0; i < n; i++)
        {
            if (adj[fila.front()][i] && vec[i] == -1)
            {
                vec[i] = -2;
                fila.push(i);
            }
        }
        vec[fila.front()] = qtd++;
        fila.pop();
    }
}

void TGrafo::percursoEmProfundidade(int inicio, int *vec)
{
    std::stack<int> pilha;

    for (int i = 0; i < n; i++)
    {
        vec[i] = -1;
    }

    pilha.push(inicio);

    int qtd = 0;
    while (!pilha.empty())
    {
        for (int i = 0; i < n; i++)
        {
            if (adj[pilha.top()][i] && vec[i] == -1)
            {
                vec[i] = -2;
                pilha.push(i);
            }
        }
        vec[pilha.top()] = qtd++;
        pilha.pop();
    }
}

// Algoritmo de Floyd
void TGrafo::exibirRotasMinimas()
{
    //um numero muito grande para fazer as vezes de infinito. Se usar INT_MAX, na hora q for somar dá overflow e fica negativo
    int inf = 100000;

    Matriz *d = new Matriz(this->n, this->n);
    Matriz *r = new Matriz(this->n, this->n);
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (i == j)
                d->set(i, j, 0);
            else if (adj[j][i] > 0)
                d->set(i, j, adj[j][i]);
            else
                d->set(i, j, inf);

            if (d->get(i, j) < inf)
                r->set(i, j, i);
            else
                r->set(i, j, -1);
        }
    }

    for (int k = 0; k < n; k++)
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                if (i != j && d->get(i, k) + d->get(k, j) < d->get(i, j))
                {
                    d->set(i, j, d->get(i, k) + d->get(k, j));
                    r->set(i, j, r->get(k, j));
                }

    // Impressao
    std::cout << "  │";
    for (int j = 0; j < n; j++)
        std::cout << ' ' << j + 1;
    std::cout << "\n──┼";
    
    for (int j = 0; j < n; j++)
        std::cout << "──";
    
    std::cout<<'\n';

    for (int i = 0; i < n; i++)
    {
        std::cout<<i+1<<" │";
        for (int j = 0; j < n; j++)
            std::cout<<' '<<r->get(j,i)+1;
        std::cout<<'\n';
        
    }
    std::cout<<std::endl;

    delete r;
    delete d;
}