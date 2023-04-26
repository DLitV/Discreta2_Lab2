#include <stdlib.h>
#include <search.h>
 
 
#include "EstructuraGrafo23.h"
#include "list.h"
#include "tad_vertice.h"
#include "int_to_str.h"
 
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
    v = malloc(sizeof (struct s_vertice_t));
    v->nombre = nombre;
    v->grado = 0;
    v->indice = max_u32;
    v->vecinos_array = NULL;
    v->vecinos = empty_list();
 
    return v;
}
 
vertice vertice_sumar_vecino (vertice v, u32 vecino){
    v->vecinos = addl_list(v->vecinos, vecino);
 
    v->grado = v->grado + 1;
    return v;
}
 
vertice vertice_indexar (vertice v, u32 indice){
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
    v->vecinos = destroy_list (v->vecinos);
    return v;
}
 
vertice vertice_destruir_nodo_con_array(vertice v){
    if (v->vecinos_array != NULL)
    {
        free(v->vecinos_array);
        v->vecinos_array = NULL;
    }
    free(v);
    return v;
}
 
vertice vertice_generar_array_adyacencia(vertice v){
    list lista = v->vecinos;
    unsigned int n = v->grado;
    v->vecinos_array = calloc (n, sizeof(u32));
    u32 nombre;
    ENTRY entry;
    ENTRY * puntero_hash;
    for(unsigned int i = 0; i < n; i++)
    {
        nombre = head_list(lista);
        lista = tail_list(lista);
        char * str = int_to_string(nombre);
        entry.key = str;
        entry.data = NULL;
        puntero_hash = hsearch(entry, FIND);
        
        if (puntero_hash == NULL)
        {
            lista = destroy_list (lista);
            lista = NULL;
            free (str);
            v = vertice_destruir_nodo_con_array (v);
            return NULL;
        }
        
        v->vecinos_array[i] = vertice_indice(puntero_hash->data);
        free (str);
    }
    return v;
}