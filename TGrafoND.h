/*
Implementa��o de uma Classe para grafos denominada TGrafo,
usando Matriz de Adjac�ncia
e m�todos para utiliza��o de um grafo dirigido.
*/
#ifndef ___GRAFO_MATRIZ_ADJACENCIA_ND___

#define ___GRAFO_MATRIZ_ADJACENCIA_ND___

#include <string>
#include "TGrafo.h"

class TGrafoND : public TGrafo
{
public:
	TGrafoND(int n) : TGrafo(n){};
	TGrafoND(std::string arquivo) : TGrafo(arquivo){};

	void insereA(int v, int w) override;
	void removeA(int v, int w) override;
		
	int tipoConexidade();
	void exibirColoracaoSequencial();
};

#endif
