/*
Implementa��o de uma classe para Grafo usando Listas de Adjac�ncias
e seus m�todos para utiliza��o de um grafo dirigido.
*/
#ifndef ___GRAFO_LISTA_ADJACENCIA___
#define ___GRAFO_LISTA_ADJACENCIA___

class TGrafoLs;
#include <string>
#include "TGrafo.h"

// definicao da classe de n�s da lista
class TNo{ // define uma struct (registro)
	public:
		// v�rtice que � adjacente ao elemento da lista
		int w; 
		TNo *prox;
};

// defini��o de uma classe para armezanar um grafo
class TGrafoLs{
	private:
		int n; // quantidade de v�rtices
		int m; // quantidade de arestas
		TNo **adj; // um vetor onde cada entrada guarda o inicio de uma lista
	public:
		TGrafoLs( int n );
		TGrafoLs( std::string arquivo );
		void insereA( int v, int w);
		void removeA( int v, int w);
		void show();
		~TGrafoLs();	

		void inverterVertices();

		int ehFonte(int v);
		int ehSorvedouro(int v);
		int ehSimetrico();

    friend class TGrafo;
};
#endif

