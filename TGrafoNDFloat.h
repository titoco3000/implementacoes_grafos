#ifndef ___GRAFO_MATRIZ_ADJACENCIA_ND_FLOAT___
#define ___GRAFO_MATRIZ_ADJACENCIA_ND_FLOAT___

#include <string>

class TGrafoNDFloat{
	private:
		int n;
		int m;
		float **adj;
	public:
		TGrafoNDFloat( int n);
		TGrafoNDFloat( std::string arquivo );
		~TGrafoNDFloat();		

		virtual void insereA(int v, int w, float peso);
		virtual void removeA(int v, int w);
		void show();

		int inDegree(int v);
		int outDegree(int v);
		int ehFonte(int v);
		int ehSorvedouro(int v);
		int ehSimetrico();

		void exibirArestasPrim();

};

#endif
