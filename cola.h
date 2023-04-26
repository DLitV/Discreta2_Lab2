#ifndef _LIST_H
#define _LIST_H

#include "EstructuraGrafo23.h"

typedef struct s_head_t * cola;

typedef u32 list_elem;

cola empty_queue();
/* {- Crea una cola vacía. -} */

cola add_queue (cola l, list_elem e);
/* {- Agrega el elemento e al final de la cola l. -} */

cola destroy_queue (cola l);
/* {- Libera memoria en caso que sea necesario. -} */

list_elem head_queue (cola l);
/* {- Devuelve el primer elemento de la cola l -}
{- PRE: not is_empty(l) -} */

cola tail_queue (cola l);
/* {- Elimina el primer elemento de la cola l -}
{- PRE: not is_empty(l) -}
 */

unsigned int length_queue (cola l);
/* {- Devuelve la cantidad de elementos de la cola l -} */

#endif