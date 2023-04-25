#include <stdio.h>
#include <stdbool.h>
#include "APIParte2.h"
#include "cola.h"
#include "EstructuraGrafo23.h"

//Greedy efectua un coloreo greedy del grafo G
//devuelve: cantidad de colores usados. Puede modificarse para devolver el coloreo en cuestion.
//          (2^32)-1 ante error de memoria.
u32 Greedy(Grafo G,u32* Orden,u32* Color){
    u32 n = NumeroDeVertices(G);
    u32 m = NumeroDeLados(G);
    u32 * coloreo = malloc(sizeof(u32)*n);

    //chequear error:
    if (coloreo = NULL)
    {
        return max_u32;
    }

    u32 colores = 1; //los colores totales usados
    for (u32 i = 0; i < n; i++)
    {
        //En esta implementacion el 0 significa "sin colorear"
        //coloreo va almacenando el color de cada vertice en el orden natural
        //esta funcion puede cambiarse para devolver el coloreo en si con "return coloreo;"
        coloreo[i] = 0;
    }
    
    for (u32 i = 0; i < n; i++)
    {
        //loop principal
        u32 vertice = Orden[i];
        u32 grado = Grado(vertice,G);
        u32 * vecinos = malloc(sizeof(u32)*grado);

        //si no tiene vecinos es automaticamente color 1 y pasamos al sig vertice
        if (grado == 0)
        {
            coloreo[vertice] = 1;
            continue;
        }
        
        //chequear error:
        if (vecinos = NULL)
        {
            return max_u32;
        }

        //armar lista de vecinos
        for (u32 j = 0; j < grado; j++)
        {   
            vecinos[j] = IndiceVecino(j,vertice,G);
        }
        

        //empezar asumiendo que el color no es
        //valido para entrar en el loop al menos 1 vez.
        //posible alternativa: implementar tal que el primer vertice coloreado sea
        //siempre color 1, pero seria un poco verboso de mas.
        u32 color = 1;
        bool color_valido = false;
        while (!color_valido)
        {
            //el color actual es valido hasta que se encuentre un vecino de ese color,
            //en cuyo caso el color actual aumenta en 1
            color_valido = true;
            for (u32 j = 0; j < grado; j++)
            {
                if (coloreo[vecinos[j]] == color)
                {
                    color_valido = false;
                    color++;
                    if (color > colores)
                    {
                        colores = color; //esto funciona solo porque los "nombres" de los colores son 1...n
                    }
                    break; //si ya hay un vecino del color actual no es necesario seguir
                           //viendo los demas vecinos, y se puede pasar al siguiente color
                }
            }
        }
        coloreo[vertice] = color; //si termina el for es porque el color actual es valido
    }
    return colores; //devuelve el total de colores usado
}



char OrdenImparPar(u32 n,u32* Orden,u32* Color){

                                //printf("cantidad de vertices: %u\n", n);

    u32 num_de_colores = 0;

    //veo cual es el maximo color usado, los colores van desde (0, num_de_colores) y hay num_de_colores + 1 colores
    for (u32 i = 0; i < n; i++)
    {
                                //printf("orden: %u   color: %u\n", Orden[i], Color[i]);
        if (Color[i] > num_de_colores){
            num_de_colores = Color[i];
        }
    }

                                //printf("colores usados: %u\n", num_de_colores);
                                //printf("\n\n\n\n\n");
    u32 mitad = num_de_colores / 2;


    //creo num_de_colores colas para guardar los vertices de forma ordenada
    cola * imparpar = calloc(num_de_colores + 1, sizeof(cola));

    if (imparpar == NULL)
    {
        printf("No se pudo alocar suficiente memoria para la lista de colas\n");
        return '1';
    }

    for (u32 i = 0; i < num_de_colores + 1; i++)
    {
        imparpar[i] = empty_list();
    }
    
    bool num_de_colores_es_impar = (num_de_colores % 2 == 1); 
    u32 indice = 0;
    for (u32 i = 0; i < n; i++)
    {
        if (num_de_colores_es_impar)
        {
            if (Color[i] % 2  == 0){
                indice = mitad + 1 + mitad - (Color[i] / 2);
            }
            else{
                indice = mitad - (Color[i] / 2);
            }
        }
        else{
            if (Color[i] % 2  == 0){
                indice = mitad + mitad - (Color[i] / 2);
            }
            else{
                indice = mitad - 1 - (Color[i] / 2);
            }
        }

        // por si alguna razon se usa un solo color para colorear los vertices
        if (num_de_colores == 0){
            indice = 0;
        }
        imparpar[indice] = add (imparpar[indice], i);
                                //printf("cola: %u   vertice: %u   color: %u\n", indice, i, Color [i]);
    }
                                //printf("\n\n\n\n\n");
    
    
    //paso el orden de imparpar a Orden
    indice = 0;
    for (u32 i = 0; i < num_de_colores + 1; i++)
    {
        u32 size =  length(imparpar[i]);
        for (u32 j = 0; j < size; j++)
        {
            Orden[indice] = head (imparpar[i]);
            imparpar[i] = tail (imparpar[i]);
                                //printf("orden: %u   vertice: %u   color: %u\n", indice, Orden[indice], Color [Orden[indice]]);
            indice = indice + 1;
        }
        
    }


                                //printf("\n\n\n\n\n\n");
                                //printf ("segundo for\n");
                                for (u32 i = 0; i < n; i++)
                                {
                                    printf("orden: %u   vertice: %u   color: %u\n", i, Orden[i], Color [Orden[i]]);
                                }
    
    
    for (u32 i = 0; i < num_de_colores + 1; i++)
    {
        imparpar[i] = destroy_list(imparpar[i]);
    }
    free (imparpar);

    return '0';
}
