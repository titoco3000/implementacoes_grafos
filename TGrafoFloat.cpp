#include <iostream>
#include <fstream>
#include <unistd.h>
#include <iomanip>

#include "TGrafoFloat.h"

using namespace std;

#include <unistd.h>
std::string cwdd()
{
    char buffer[FILENAME_MAX];
    if (getcwd(buffer, FILENAME_MAX) != nullptr)
    {
        return {buffer};
    }
    return "";
}

void preencherFechoTransitivoDireto(float **matriz, int *atingiveis, int n, int v)
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
void preencherFechoTransitivoInverso(float **matriz, int *atinge, int n, int v)
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

// Construtor do TGrafoFloat, respons�vel por
// Criar a matriz de adjac�ncia v x v do Grafo
TGrafoFloat::TGrafoFloat(int n)
{
    this->n = n;
    // No in�cio dos tempos n�o h� arestas
    this->m = 0;
    // aloca da matriz do TGrafoFloat
    float **adjac = new float *[n];
    for (int i = 0; i < n; i++)
        adjac[i] = new float[n];
    adj = adjac;
    // Inicia a matriz com zeros
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;
}

TGrafoFloat::TGrafoFloat(std::string arquivo)
{
    std::string full_path = cwdd() + "/" + arquivo;
    std::cout << full_path << std::endl;
    std::ifstream inFile(full_path);

    if (inFile)
    {
        inFile >> this->n;

        this->m = 0;

        this->adj = new float *[n];
        for (int i = 0; i < n; i++)
            this->adj[i] = new float[n];

        // Inicia a matriz com zeros
        for (int i = 0; i < n; i++)
            for (int j = 0; j < n; j++)
                adj[i][j] = 0;

        int a, de, para;
        float peso;
        inFile >> a;
        for (int i = 0; i < a; i++)
        {
            inFile >> de;
            inFile >> para;
            inFile >> peso;
            this->insereA(de, para, peso);
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
TGrafoFloat::~TGrafoFloat()
{
    n = 0;
    m = 0;
    delete[] *adj;
    std::cout << "espaço liberado" << std::endl;
}

// Insere uma aresta no Grafo tal que
// v � adjacente a w
void TGrafoFloat::insereA(int v, int w, float peso)
{
    adj[v][w] = peso;
    // testa se nao temos a aresta
    if (adj[v][w] == 0.0 && peso!=0.0)
        m++; // atualiza qtd arestas
}

// remove uma aresta v->w do Grafo
void TGrafoFloat::removeA(int v, int w)
{
    // testa se temos a aresta
    if (adj[v][w] == 1)
    {
        adj[v][w] = 0;
        m--; // atualiza qtd arestas
    }
}

void TGrafoFloat::show()
{
    std::cout << "n: " << n << std::endl<< std::fixed<< std::setprecision(1);
    std::cout << "m: " << m << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << "\n";
        for (int w = 0; w < n; w++)
            std::cout << "Adj[" << i << "," << w << "]= "<<adj[i][w] << " ";
    }
    cout << "\nfim da impressao do grafo." << endl;
}

int TGrafoFloat::inDegree(int v)
{
    int r = 0;
    for (size_t i = 0; i < this->n; i++)
        if (this->adj[i][v])
            r++;
    return r;
}

int TGrafoFloat::outDegree(int v)
{
    int r = 0;
    for (size_t i = 0; i < this->n; i++)
        if (this->adj[v][i])
            r++;
    return r;
}

int TGrafoFloat::ehFonte(int v)
{
    return outDegree(v) > 0 && inDegree(v) == 0;
}

int TGrafoFloat::ehSorvedouro(int v)
{
    return inDegree(v) > 0 && outDegree(v) == 0;
}

int TGrafoFloat::ehSimetrico()
{
    for (size_t i = 0; i < this->n; i++)
        for (size_t j = 0; j < this->n; j++)
            if (this->adj[i][j] != this->adj[j][i])
                return 0;
    return 1;
}

int TGrafoFloat::removerVertice(int v)
{
    if (v >= this->n)
        return 0;

    float **adjac = new float *[n - 1];
    m = 0;

    int i_completos = 0;

    for (int i = 0; i < n; i++)
    {
        adjac[i] = new float[n - 1];
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

int TGrafoFloat::ehCompleto()
{
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            if (adj[i][j] == 0)
                return 0;
    return 1;
}

TGrafoFloat *TGrafoFloat::complementar()
{
    TGrafoFloat *c = new TGrafoFloat(this->n);
    for (size_t i = 0; i < n; i++)
        for (size_t j = 0; j < n; j++)
            if (adj[i][j] == 0)
                c->insereA(i, j, 1.0);
    return c;
}

TGrafoFloat *TGrafoFloat::reduzido()
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

    TGrafoFloat *c = new TGrafoFloat(qtd_grupos);
    
    //associa as arestas
    for (int i = 0; i < n; i++)
    {
        for (int j = 0; j < n; j++)
        {
            if (adj[i][j] && grupo[i] != grupo[j])
            {
                c->insereA(grupo[i], grupo[j], adj[i][j]);
            }
        }
    }

    free(atingem);
    free(atingidos);
    free(grupo);

    return c;
}

int TGrafoFloat::categoriaConexidade()
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
