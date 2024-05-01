/*
Implementa��o de uma Classe para grafos denominada TGrafo,
usando Matriz de Adjacência
e métodos para utilização de um grafo dirigido.
*/
#ifndef ___GRAFO_MATRIZ_ADJACENCIA___

#define ___GRAFO_MATRIZ_ADJACENCIA___

#include <string>
#include "TGrafoLista.h"

// definição de uma estrutura para armezanar um grafo
// Também seria poss�vel criar um arquivo grafo.h 
// e fazer a inclus�o "#include <grafo.h>"
class TGrafo{
	protected:
		int n; // quantidade de v�rtices
		int m; // quantidade de arestas
		int **adj; //matriz de adjac�ncia
	public:
		TGrafo( int n);
		TGrafo( std::string arquivo );
		~TGrafo();		

		virtual void insereA(int v, int w);
		virtual void insereA(int v, int w, int p);
		virtual void removeA(int v, int w);
		virtual void removeV(int v);
		void show();

		int inDegree(int v);
		int outDegree(int v);
		int ehFonte(int v);
		int ehSorvedouro(int v);
		int ehSimetrico();

		int removerVertice(int v);
		int ehCompleto();
		int ehEquivalente(TGrafoLs* outro);

		TGrafo* complementar();
		TGrafo* reduzido();
		TGrafoLs* paraLista();

		int categoriaConexidade();

		int ordenacaoTopologica(int *vec);
		void percursoEmProfundidade(int inicio, int *vec);
		void percursoEmLargura(int inicio, int *vec);

		void exibirRotasMinimas();

};

#endif
