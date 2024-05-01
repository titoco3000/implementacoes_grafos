/*
Implementa��o de uma Classe para grafos denominada TGrafoFloat,
usando Matriz de Adjacência
e métodos para utilização de um grafo dirigido.
*/
#ifndef ___GRAFO_MATRIZ_ADJACENCIA_FLOAT___

#define ___GRAFO_MATRIZ_ADJACENCIA_FLOAT___

#include <string>

// definição de uma estrutura para armezanar um grafo
// Também seria poss�vel criar um arquivo grafo.h 
// e fazer a inclus�o "#include <grafo.h>"
class TGrafoFloat{
	protected:
		int n; // quantidade de v�rtices
		int m; // quantidade de arestas
		float **adj; //matriz de adjac�ncia
	public:
		TGrafoFloat( int n);
		TGrafoFloat( std::string arquivo );
		~TGrafoFloat();		

		virtual void insereA(int v, int w, float peso);
		virtual void removeA(int v, int w);
		void show();

		int inDegree(int v);
		int outDegree(int v);
		int ehFonte(int v);
		int ehSorvedouro(int v);
		int ehSimetrico();

		int removerVertice(int v);
		int ehCompleto();

		TGrafoFloat* complementar();
		TGrafoFloat* reduzido();
		
		int categoriaConexidade();

};

#endif
