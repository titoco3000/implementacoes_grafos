#include <iostream>
#include <fstream>
#include <filesystem>
#include <iomanip>

#include "TGrafoNDFloat.h"

using namespace std;

#include <unistd.h>
std::string cwd()
{
    char buffer[FILENAME_MAX];
    if (getcwd(buffer, FILENAME_MAX) != nullptr)
    {
        return {buffer};
    }
    return "";
}
TGrafoNDFloat::TGrafoNDFloat(int n)
{
    this->n = n;
    this->m = 0;
    float **adjac = new float *[n];
    for (int i = 0; i < n; i++)
        adjac[i] = new float[n];
    adj = adjac;
    for (int i = 0; i < n; i++)
        for (int j = 0; j < n; j++)
            adj[i][j] = 0;
}

TGrafoNDFloat::TGrafoNDFloat(std::string arquivo)
{
    std::string full_path = cwd() + "/" + arquivo;

    std::ifstream inFile(full_path);

    if (inFile)
    {
        inFile >> this->n;

        this->m = 0;

        this->adj = new float *[n];
        for (int i = 0; i < n; i++)
            this->adj[i] = new float[n];

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

TGrafoNDFloat::~TGrafoNDFloat()
{
    n = 0;
    m = 0;
    delete[] *adj;
    std::cout << "espaço liberado" << endl;
}

void TGrafoNDFloat::insereA(int v, int w, float peso)
{
    if (adj[v][w] == 0)
    {
        m += 2;
    }
    adj[v][w] = peso;
    adj[w][v] = peso;
}

void TGrafoNDFloat::removeA(int v, int w)
{
    if (adj[v][w] != 0)
    {
        adj[v][w] = 0;
        adj[w][v] = 0;
        m -= 2;
    }
}

void TGrafoNDFloat::show()
{
    std::cout << "n: " << n << std::endl
              << std::fixed << std::setprecision(1);
    std::cout << "m: " << m << std::endl;
    for (int i = 0; i < n; i++)
    {
        std::cout << "\n";
        for (int w = 0; w < n; w++)
            std::cout << "Adj[" << i << "," << w << "]= " << adj[i][w] << " ";
    }
    cout << "\nfim da impressao do grafo." << endl;
}

int TGrafoNDFloat::inDegree(int v)
{
    int r = 0;
    for (size_t i = 0; i < this->n; i++)
        if (this->adj[i][v])
            r++;
    return r;
}

int TGrafoNDFloat::outDegree(int v)
{
    int r = 0;
    for (size_t i = 0; i < this->n; i++)
        if (this->adj[v][i])
            r++;
    return r;
}

int TGrafoNDFloat::ehFonte(int v)
{
    return outDegree(v) > 0 && inDegree(v) == 0;
}

int TGrafoNDFloat::ehSorvedouro(int v)
{
    return inDegree(v) > 0 && outDegree(v) == 0;
}

int TGrafoNDFloat::ehSimetrico()
{
    for (size_t i = 0; i < this->n; i++)
        for (size_t j = 0; j < this->n; j++)
            if (this->adj[i][j] != this->adj[j][i])
                return 0;
    return 1;
}

void TGrafoNDFloat::exibirArestasPrim()
{
    std::cout << "Árvore mínima:\n";

    int *arestasAdicionadas = (int *)calloc(sizeof(int), n);
    arestasAdicionadas[0] = 1;
    int qtdArestasAdicionadas = 1;
    while (qtdArestasAdicionadas < n)
    {
        int menor[2] = {-1, -1};
        for (int i = 0; i < n; i++)
        {
            for (int j = 0; j < n; j++)
            {
                if (
                    arestasAdicionadas[i] &&
                    !arestasAdicionadas[j] &&
                    adj[i][j] > 0 &&
                    (menor[0] < 0 || adj[menor[0]][menor[1]] > adj[i][j]))
                {
                    menor[0] = i;
                    menor[1] = j;
                }
            }
        }
        arestasAdicionadas[menor[1]] = 1;
        qtdArestasAdicionadas++;
        std::cout << menor[0] + 1 << " ──> " << menor[1] + 1 << std::endl;
    }
    free(arestasAdicionadas);
}