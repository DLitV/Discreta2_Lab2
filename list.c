#include <assert.h>
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#include "list.h"

struct s_list_t {
    list_elem elem;
    list next;
};

// para inicializar es mejor usar
// struct s_list_t
// ya es un nodo solo
// es "mejor" semanticamente

list empty_list (){
    list l = NULL;
    return l;
}

list addl (list l, list_elem e){
    list p = NULL;
    p = malloc(sizeof(struct s_list_t));
    
    p->elem = e;
    p->next = l;
    l = p;
    
    return l;
}

list destroy_list (list l){
    list p;

    while ( l != NULL){
        p = l;
        l = l->next;
        p->next = NULL;
        free (p);
    }

    return l;
}

bool is_empty (list l){
    bool b;
    b = (l == NULL);
    return b;
}

list_elem head (list l){
    assert (!is_empty(l));

    list_elem e;

    e = l->elem;

    return e;
}

list tail (list l){
    assert (!is_empty(l));
    list p;
    p = l;
    l = l->next;
    p->next = NULL;
    free (p);
    
    return l;
}

list addr (list l, list_elem e){
    list p;
    list aux;

    p = malloc(sizeof(struct s_list_t));
    p->elem = e;
    p->next = NULL;
    
    if (is_empty(l)){
        l = p;
    }
    else{

        aux = l;
        
        while (aux->next != NULL){
            aux = aux->next;
        }

        aux->next = p;
    }

    return l;
}

unsigned int length (list l){
    unsigned int n = 0;
    list p;
    
    p = l;
    while (p != NULL){
        n ++;
        p = p->next; 
    }

    return n;
}

list concat (list l0, list l1){
    list p;

    if (! is_empty (l0)){
        p = l0;

        while (p->next != NULL){
            p = p->next;
        }

        p->next = l1;
    }
    else{
        l0 = l1;
    }

    return l0;
}

list_elem index (list l, unsigned int n){
    assert (length(l) > n);

    list_elem e;
    list p;
    p = l;

    for (unsigned int i = 1; i < n; i++){
        p = p->next;
    }

    e = p->elem;

    return e;
}

list take (list l, unsigned int n){
    if (length(l) <= n){

    }

    else{

        list p;
        unsigned int i = 1;
        
        p = l;
        while ( i < n && p != NULL){
            p = p->next;
            i ++;
        }

        p->next = destroy_list(p->next);
    }

    return l;
}

list drop (list l, unsigned int n){
    if (length(l) <= n){
        l = destroy_list(l);
    }
    else{
        list p;
        unsigned int i = 0;

        while ( i < n && l != NULL){
            p = l;
            l = l->next;
            p->next = NULL;
            free (p);
            i ++;
        }
    }
    return l;
}

list copy_list (list l){
    list p = NULL;
    
    if (is_empty(l)){
    }
    else {
        p = malloc(sizeof(struct s_list_t));
        p->elem = l->elem;
        p->next = copy_list(l->next);
    }

    return p;
}

void dump_lista (list l){
    list p;

    if (is_empty (l)){
        printf("la lista no tiene elementos");
    }
    else{
        p = l;
        while (p != NULL){
            printf ("%i, ", p->elem);
            p = p->next;        
        }
    }
}