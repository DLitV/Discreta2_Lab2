#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "cola.h"

typedef struct s_list_t * list;

struct s_list_t {
    list_elem elem;
    list next;
};

struct s_head_t {
    list first;
    list last;
    unsigned int size;
};

cola empty_queue (){
    cola l = malloc(sizeof(struct s_head_t));
    l->first = NULL;
    l->last = NULL;
    l->size = 0;
    return l;
}

cola add_queue (cola l, list_elem e){
    list p = NULL;
    p = malloc(sizeof(struct s_list_t));

    p->elem = e;
    p->next = NULL;

    if (l->first == NULL){
        l->first = p;
        l->last = p;
    }
    else{
        l->last->next = p;
        l->last = p;
    }

    l->size = l->size + 1;
    return l;
}

cola destroy_queue (cola l){
    list p;
    list aux = l->first;
    while ( aux != NULL){
        p = aux;
        aux = aux->next;
        p->next = NULL;
        free (p);
    }

    l->last = NULL;
    free (l);
    l = NULL;

    return l;
}


list_elem head_queue (cola l){

    list_elem e;

    e = l->first->elem;

    return e;
}

cola tail_queue (cola l){
    list p;
    p = l->first;
    l->first = l->first->next;
    l->size = l->size - 1;
    if (l->size == 0)
    {
        l->last = NULL;
    }
    
    p->next = NULL;
    free (p);
    
    return l;
}

unsigned int length_queue (cola l){
    return l->size;
}