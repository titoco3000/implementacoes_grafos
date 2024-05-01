#include <iostream>
#include <fstream>
#include <filesystem>
#include "TGrafo.h"
#include "TGrafoLista.h"
#include "TGrafoND.h"
#include "TGrafoNDFloat.h"
#include "TGrafoFloat.h"

void teste_geral()
{
    TGrafo *g1 = new TGrafo(4);
    g1->insereA(0, 1);
    g1->insereA(0, 2);
    g1->insereA(2, 1);
    g1->insereA(2, 3);
    g1->insereA(1, 3);

    std::cout << "Grafo para os exercícios 1-5:\n";
    g1->show();

    std::cout << "\n1) InDegree\n    inDegree(3) = " << g1->inDegree(3)
              << "\n_______________________________________________________________________________________";
    std::cout << "\n\n2) OutDegree\n    outDegree(2) = " << g1->outDegree(2)
              << "\n_______________________________________________________________________________________";
    std::cout << "\n\n3) Fonte\n    ehFonte(0) = " << g1->ehFonte(0)
              << "\n_______________________________________________________________________________________";
    std::cout << "\n\n4) Sorvedouro\n    ehSorvedouro(0) = " << g1->ehSorvedouro(0)
              << "\n_______________________________________________________________________________________";

    std::cout << "\n\n5) Simetria\n    ehSimetrico() = " << g1->ehSimetrico();
    g1->insereA(1, 0);
    g1->insereA(2, 0);
    g1->insereA(1, 2);
    g1->insereA(3, 1);
    g1->insereA(3, 2);
    std::cout << "\nInserindo arestas que faltam\n";
    g1->show();
    std::cout << "ehSimetrico() = " << g1->ehSimetrico()
              << "\n_______________________________________________________________________________________";

    std::cout << "\n\n6) Lendo o arquivo:\n";

    std::ifstream file("grafo.txt");
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::cout << line << '\n';
        }
        file.close();
    }
    std::cout << "    Grafo lido:\n";
    TGrafo *g2 = new TGrafo("grafo.txt");
    g2->show();

    std::cout << "\n_______________________________________________________________________________________";

    std::cout << "\n\n7) Grafo não-dirigido:\n";
    TGrafoND *g3 = new TGrafoND(4);
    g3->insereA(0, 1);
    g3->insereA(0, 2);
    g3->insereA(2, 1);
    g3->insereA(2, 3);
    g3->insereA(1, 3);
    g3->removeA(0, 1);
    g3->show();

    std::cout << "\n_______________________________________________________________________________________";

    std::cout << "\n\n8) Grafo não-direcionado com pesos:\n";
    TGrafoNDFloat *g4 = new TGrafoNDFloat(4);
    g4->insereA(0, 1, 0.1);
    g4->insereA(0, 2, 0.2);
    g4->insereA(2, 1, 0.3);
    g4->insereA(2, 3, 0.4);
    g4->insereA(1, 3, 0.5);
    g4->removeA(0, 1);
    g4->show();

    std::cout << "\n_______________________________________________________________________________________";

    std::cout << "\n\n9) Remoção de vértice:\n    Original:\n";
    g1->show();
    std::cout << "    3º vértice removido:\n";
    g1->removeV(2);
    g1->show();

    std::cout << "\n_______________________________________________________________________________________";

    std::cout << "\n\n10) Grafo não-direcionado completo:\n    grafo original:\n";
    g3->show();
    std::cout << "    é completo: " << g3->ehCompleto();
    g3->insereA(0, 0);
    g3->insereA(1, 1);
    g3->insereA(2, 2);
    g3->insereA(3, 3);
    g3->insereA(0, 1);
    g3->insereA(0, 3);
    g3->insereA(1, 2);
    std::cout << "\n\n    grafo completado:\n";
    g3->show();
    std::cout << "    é completo: " << g3->ehCompleto();

    std::cout << "\n_______________________________________________________________________________________";

    std::cout << "\n\n11) Grafo completo:\n    grafo original:\n";
    g1->show();
    std::cout << "    é completo: " << g1->ehCompleto();
    for (int i = 0; i < 4; i++)
        for (int j = 0; j < 4; j++)
            g1->insereA(i, j);

    std::cout << "\n    grafo com novas arestas:\n";
    g1->show();

    std::cout << "    é completo: " << g1->ehCompleto();

    std::cout << "\n_______________________________________________________________________________________";

    std::cout << "\n\n12) Grafo complementar:\n    grafo:\n";
    g1->removeA(2, 3);
    g1->removeA(1, 1);
    g1->removeA(1, 2);
    g1->removeA(3, 2);
    g1->show();
    TGrafo *g5 = g1->complementar();
    std::cout << "\n    grafo complementar:\n";
    g5->show();

    std::cout << "\n_______________________________________________________________________________________";

    std::cout << "\n\n13) Conexidade de não-direcionado:\n    grafo: ";
    g3->removeA(0, 1);
    g3->show();
    std::cout << "\nConexidade: " << g3->categoriaConexidade();

    std::cout << "\n_______________________________________________________________________________________";

    std::cout << "\n\n14) Conexidade:\n    grafo: ";
    g1->removeA(1, 0);
    g1->removeA(2, 0);
    g1->show();
    std::cout << "\nConexidade: " << g1->categoriaConexidade();

    std::cout << "\n_______________________________________________________________________________________";

    std::cout << "\n\n15) Grafo reduzido:\n    original:\n";
    g5->insereA(2, 0);
    g5->insereA(2, 1);
    g5->show();
    std::cout << "\n\nReduzido:\n";
    TGrafo *g6 = g5->reduzido();
    g6->show();

    std::cout << "\n_______________________________________________________________________________________";

    std::cout << "\n\n16) Grafo direcionado com pesos:\n";
    TGrafoFloat *g7 = new TGrafoFloat(4);
    g7->insereA(0, 1, 0.1);
    g7->insereA(0, 2, 0.2);
    g7->insereA(2, 1, 0.3);
    g7->insereA(2, 3, 0.4);
    g7->insereA(1, 3, 0.5);
    g7->show();

    std::cout << "\n\n17) Igualdade:\n    A:\n";
    TGrafo *g8 = new TGrafo(3);

    TGrafoLs *g9 = new TGrafoLs(3);

    g8->insereA(0, 0);
    g8->insereA(0, 1);
    g8->insereA(0, 2);
    g9->insereA(0, 0);
    g9->insereA(0, 1);
    g9->insereA(0, 2);

    g8->show();
    std::cout << "\n    B:\n";
    g9->show();
    std::cout << "\n    equivalentes(A, B): " << g8->ehEquivalente(g9);

    std::cout << "\n\n_______________________________________________________________________________________";

    std::cout << "\n\n18) Conversão:\n    original:\n";
    g8->show();
    std::cout << "    Convertido:\n";
    TGrafoLs *g10 = g8->paraLista();
    g10->show();

    std::cout << "\n\n_______________________________________________________________________________________";

    std::cout << "\n\n19) Inversão:\n    original:";
    g10->show();
    g10->inverterVertices();
    std::cout << "\n    Invertetido:\n";
    g10->show();

    std::cout << "\n\n_______________________________________________________________________________________";

    std::cout << "\n\n    Grafo para os exs 20-22:\n";
    g1->show();

    std::cout << "\n\n20) Fonte:\n    ehFonte(1): " << g1->ehFonte(1)
              << "\n_______________________________________________________________________________________";

    std::cout << "\n\n21) Sorvedouro:\n    ehSorvedouro(1): " << g1->ehSorvedouro(1)
              << "\n_______________________________________________________________________________________";

    std::cout << "\n\n22) Simetria:\n    ehSimetrico(): " << g1->ehSimetrico()
              << "\n_______________________________________________________________________________________";

    std::cout << "\n\n23) Lendo o arquivo:\n";

    file.open("grafo.txt");
    if (file.is_open())
    {
        std::string line;
        while (std::getline(file, line))
        {
            std::cout << line << '\n';
        }
        file.close();
    }
    std::cout << "    Grafo lido:\n";
    TGrafoLs *g11 = new TGrafoLs("grafo.txt");
    g11->show();

    std::cout << "\n_______________________________________________________________________________________";

    std::cout << "\n\n24) Remoção de vértice grafo não-direcionado:\n    grafo original: ";
    g3->removeA(0, 1);
    g3->removeA(0, 2);
    g3->show();
    g3->removeV(1);
    std::cout << "    Grafo após remover 2º vertice:\n";
    g3->show();

    std::cout << "\n_______________________________________________________________________________________";

    std::cout << "\n\n25) Remoção de vértice:\n    grafo original: ";
    g1->show();
    g1->removeV(1);
    std::cout << "    grafo após remover 2º vertice:\n";
    g1->show();

    std::cout << "\n_______________________________________________________________________________________";

    std::cout << "\n\n26) grafo completo:\n    grafo original: ";
    g1->show();
    std::cout << "\n    É completo: " << g1->ehCompleto() << "\nRemovendo arestas:\n";
    g1->insereA(1, 0);
    g1->show();
    std::cout << "\n    É completo: " << g1->ehCompleto();

    std::cout << "\n_______________________________________________________________________________________";

    std::cout << "\n\nLiberando todos os grafos usados\n\n";

    delete g1;
    delete g2;
    delete g3;
    delete g4;
    delete g5;
    delete g6;
    delete g7;
    delete g8;
    delete g9;
    delete g10;
    delete g11;

    std::cout << std::endl;
}

void teste_ordenacao_topologica()
{
    int *ordem = (int *)malloc(sizeof(int) * 8);
    TGrafo *g10 = new TGrafo(8);

    g10->insereA(0, 1);
    g10->insereA(0, 2);
    g10->insereA(0, 4);
    g10->insereA(1, 3);
    g10->insereA(1, 4);
    g10->insereA(2, 5);
    g10->insereA(2, 6);
    g10->insereA(3, 7);
    g10->insereA(4, 7);
    g10->insereA(5, 4);
    g10->insereA(5, 6);
    g10->insereA(6, 7);

    std::cout << "Grafo g10:\n";
    g10->show();
    g10->ordenacaoTopologica(ordem);

    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (ordem[j] == i)
            {
                std::cout << (char)(j + 'a') << ' ';
                break;
            }
        }
    }
    std::cout << std::endl;

    std::cout << "\nNão descobri qual era o segundo exemplo referido pelo relatório, então fiz um grafo aleatório\n";

    TGrafo *g = new TGrafo(5);

    g->insereA(1, 0);
    g->insereA(1, 2);
    g->insereA(1, 2);
    g->insereA(2, 3);
    g->insereA(0, 3);
    g->insereA(3, 4);

    g->ordenacaoTopologica(ordem);
    g->show();

    for (int i = 0; i < 5; i++)
    {
        for (int j = 0; j < 5; j++)
        {
            if (ordem[j] == i)
            {
                std::cout << (char)(j + 'a') << ' ';
                break;
            }
        }
    }
    std::cout << std::endl
              << std::endl;

    free(ordem);
    delete g10;
    delete g;
}

void teste_profundidade_e_largura()
{
    int *ordem = (int *)malloc(sizeof(int) * 8);
    TGrafo *g10 = new TGrafo(8);

    g10->insereA(0, 1);
    g10->insereA(0, 2);
    g10->insereA(0, 4);
    g10->insereA(1, 3);
    g10->insereA(1, 4);
    g10->insereA(2, 5);
    g10->insereA(2, 6);
    g10->insereA(3, 7);
    g10->insereA(4, 7);
    g10->insereA(5, 4);
    g10->insereA(5, 6);
    g10->insereA(6, 7);

    std::cout << "Grafo g10:\n";
    g10->show();

    std::cout << "\nPercurso em profundidade:\n";
    g10->percursoEmProfundidade(0, ordem);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (ordem[j] == i)
            {
                std::cout << (char)(j + 'a') << ' ';
                break;
            }
        }
    }
    std::cout << "\n\nPercurso em largura:\n";
    g10->percursoEmLargura(0, ordem);
    for (int i = 0; i < 8; i++)
    {
        for (int j = 0; j < 8; j++)
        {
            if (ordem[j] == i)
            {
                std::cout << (char)(j + 'a') << ' ';
                break;
            }
        }
    }
    std::cout << std::endl;

    free(ordem);
    delete g10;
}

void testeCaminhoMinimo(){
    TGrafo *g = new TGrafo(5);
    g->insereA(0,1,1);
    g->insereA(0,4,1);
    g->insereA(1,2,1);
    g->insereA(1,3,2);
    g->insereA(2,3,4);
    g->insereA(2,4,2);
    g->insereA(3,0,3);
    g->insereA(4,0,2);
    g->insereA(4,3,1);
    
    std::cout<<"Grafo 1:\n";
    g->exibirRotasMinimas();

    TGrafo *g1 = new TGrafo(4);
    g1->insereA(0, 1);
    g1->insereA(0, 2);
    g1->insereA(2, 1);
    g1->insereA(2, 3);
    g1->insereA(1, 3);

    std::cout<<"Grafo 2:\n";
    
    g1->exibirRotasMinimas();

    delete g;
    delete g1;
}

void testeArvoreMinima(){
    TGrafoNDFloat *g = new TGrafoNDFloat(9);
    g->insereA(0,1,4);
    g->insereA(0,5,5);
    g->insereA(1,2,7);
    g->insereA(1,5,3);
    g->insereA(2,3,5);
    g->insereA(2,6,6);
    g->insereA(3,4,3);
    g->insereA(4,6,2);
    g->insereA(4,7,4);
    g->insereA(5,6,7);
    g->insereA(5,8,5);
    g->insereA(6,7,6);
    g->insereA(7,8,8);

    g->exibirArestasPrim();
    delete g;

    TGrafoNDFloat *g4 = new TGrafoNDFloat(4);
    g4->insereA(0, 1, 0.1);
    g4->insereA(0, 2, 0.2);
    g4->insereA(2, 1, 0.3);
    g4->insereA(2, 3, 0.4);
    g4->insereA(1, 3, 0.5);
    g4->exibirArestasPrim();

    delete g4;
}

void testeColoracao(){
    TGrafoND *g1 = new TGrafoND(5);
    g1->insereA(0,1);
    g1->insereA(0,4);
    g1->insereA(1,2);
    g1->insereA(1,3);
    g1->insereA(2,3);
    g1->insereA(3,4);
    g1->exibirColoracaoSequencial();
    delete g1;

    int a = 7,
        b = 8,
        c = 3,
        d = 4,
        e = 5,
        f = 2,
        g = 0,
        h = 1,
        i = 6;


    std::cout<<"\n";
    TGrafoND *g2 = new TGrafoND(9);
    g2->insereA(a,f);
    g2->insereA(a,g);
    g2->insereA(a,i);
    g2->insereA(b,c);
    g2->insereA(b,h);
    g2->insereA(c,e);
    g2->insereA(c,h);
    g2->insereA(d,e);
    g2->insereA(d,f);
    g2->insereA(d,h);
    g2->insereA(e,g);
    g2->insereA(f,g);
    g2->insereA(f,i);
    g2->insereA(g,h);
    g2->insereA(g,i);
    g2->exibirColoracaoSequencial();
    delete g2;
}
int main()
{
    testeColoracao();
    return 0;
}