#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#include "EstructuraGrafo23.h"

Grafo ConstruirGrafo(){
    Grafo grafo = malloc(sizeof(GrafoSt));
    grafo->delta = grafo->m = grafo->n = 0;
    grafo->vertices = NULL;
    return grafo;
}
void DestruirGrafo(Grafo G){
    free(G->vertices);
    free(G);
}

u32 NumeroDeVertices(Grafo G){
    return G->n;
}
u32 NumeroDeLados(Grafo G){
    return G->m;
}
u32 Delta(Grafo G){
    return G->delta;
}
u32 Nombre(u32 i,Grafo G){
    return vertice_nombre(G->vertices[i]);
}
u32 Grado(u32 i,Grafo G){
    return vertice_grado(G->vertices[i]);
}
u32 IndiceVecino(u32 j,u32 i,Grafo G){
    return indice_vecino(G->vertices[i],j);
}

