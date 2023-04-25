#include <assert.h>
#include <stdlib.h>


#include "EstructuraGrafo23.h"
#include "list.h"
#include "tad_vertice.h"

struct s_vertice_t {
    u32 nombre;
    u32 grado;
    u32 indice;
    u32 * vecinos_array;
    list vecinos;
};

vertice vertice_vacio (){
    vertice v = NULL;
    return v;
}

vertice vertice_init (vertice v, u32 nombre){
    assert(v == NULL);

    v = malloc(sizeof (struct s_vertice_t));
    v->nombre = nombre;
    v->grado = 0;
    v->indice = max_u32;
    v->vecinos = empty_list();

    return v;
}

vertice vertice_sumar_vecino (vertice v, u32 vecino){
    assert (v != NULL);

    v->vecinos = addl(v->vecinos, vecino);

    v->grado = v->grado + 1;
    return v;
}

vertice vertice_indexar (vertice v, u32 indice){
    assert (v->indice == max_u32);
    v->indice = indice;

    return v;
}

u32 vertice_nombre (vertice v){
    return v->nombre;
}

u32 vertice_grado (vertice v){
    return v->grado;
}

u32 vertice_indice (vertice v){
    return v->indice;
}

u32 indice_vecino (vertice v, u32 indice){
    return v->vecinos_array[indice];
}

vertice vertice_destruir_vecinos(vertice v){
    assert (v != NULL);
    v->vecinos = destroy_list (v->vecinos);
    return v;
}

vertice vertice_destruir_nodo_con_array(vertice v){
    assert (v != NULL);
    free(v->vecinos_array);
    v->vecinos_array = NULL;
    free(v);
    return v;
}

vertice vertice_generar_array_adyacencia(vertice v){
    list lista = v->vecinos;
    unsigned int n = length(lista);
    for(unsigned int i = 0; i < n; i++)
    {
        v->vecinos_array[i] = head(lista);
        lista = tail(lista);
    }
    v = vertice_destruir_vecinos(v);
    return v;
}