#include <iostream>
#include "TGrafoND.h"

void TGrafoND::insereA(int v, int w){
    TGrafo::insereA(v,w);
    TGrafo::insereA(w,v);
}
void TGrafoND::removeA(int v, int w) {
    TGrafo::removeA(v,w);
    TGrafo::removeA(w,v);
}	

int TGrafoND::tipoConexidade(){
    for (int i = 0; i < this->n; i++)
    {
        int sum = 0;
        for (int j = 0; j < this->n; j++){
            sum += this->adj[i][j];
            sum += this->adj[j][i];
        }
        if(sum==0)
            return 1;
    }
    return 0;
}

void TGrafoND::exibirColoracaoSequencial(){
    int *grupos = (int*)malloc(sizeof(int)*n);
    for (int i = 0; i < n; i++)
        grupos[i] = -1;
    
    int maxGrupoOcupado = 0;

    //para cada vertice
    for (int i = 0; i < n; i++)
    {
        //para cada grupo
        for (int j = 0; j < n; j++)
        {
            bool conecta = false;
            //verifica interseccao com vértices do grupo
            for (int k = 0; k < n; k++)
                if(adj[i][k]>0 && grupos[k]== j){
                    conecta = true;
                    break;
                }
            if(!conecta){
                grupos[i] = j;
                maxGrupoOcupado = maxGrupoOcupado>j?maxGrupoOcupado:j;
                break;
            }
        }
    }
    
    std::cout<<"Coloração dos vértices\n";
    for (int i = 0; i <= maxGrupoOcupado; i++)
    {
        std::cout<< "Grupo "<<i+1<<": {";
        bool primeiro = true;
        for (int j = 0; j < n; j++)
        {
            if(grupos[j] == i){
                if(!primeiro){
                    std::cout<<',';
                }
                primeiro = false;
                std::cout<< ' '<< j+1;
            }
        }
        std::cout<< " }\n";   
    }

    std::cout<<'\n';   

    free(grupos);
    
}
