#ifndef _LIST_H
#define _LIST_H

#include "EstructuraGrafo.h"

typedef struct s_head_t * cola;

typedef u32 list_elem;

cola empty_list ();
/* {- Crea una cola vacía. -} */

cola add (cola l, list_elem e);
/* {- Agrega el elemento e al final de la cola l. -} */

cola destroy_list (cola l);
/* {- Libera memoria en caso que sea necesario. -} */

list_elem head (cola l);
/* {- Devuelve el primer elemento de la cola l -}
{- PRE: not is_empty(l) -} */

cola tail (cola l);
/* {- Elimina el primer elemento de la cola l -}
{- PRE: not is_empty(l) -}
 */

unsigned int length (cola l);
/* {- Devuelve la cantidad de elementos de la cola l -} */

#endif