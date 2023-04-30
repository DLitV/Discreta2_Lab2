#include <stdio.h>
#include <stdbool.h>
#include "APIParte2.h"
#include "cola.h"
#include "EstructuraGrafo23.h"

//Greedy efectua un coloreo greedy del grafo G
//devuelve: cantidad de colores usados. Puede modificarse para devolver el coloreo en cuestion.
//          (2^32)-1 ante error de memoria.
u32 Greedy(Grafo G, u32* Orden, u32* Color){
    u32 n = NumeroDeVertices(G);
    u32 colores = 0;
    for (u32 i = 0; i < n; i++){
        Color[i] = n;
    }
    u32 * colores_usados = calloc(n, sizeof(u32));;
    for (u32 i = 0; i < n; i++){
        colores_usados[i] = 0;
    }
    for (u32 i = 0; i < n; i++){
        u32 vertice = Orden[i];
        u32 grado = Grado(vertice, G);
        for (u32 j = 0; j < grado; j++){
            u32 vecino = IndiceVecino(j, vertice, G);
            if (Color[vecino] != n) {
                colores_usados[Color[vecino]] = vertice+1;
            }
        }
        u32 min_color = 0;
        while (colores_usados[min_color] == vertice+1) {
            min_color++;
        }
        Color[vertice] = min_color;
        colores_usados[min_color] = vertice+1;
        if (min_color > colores){
            colores = min_color;
        }
    }
    free (colores_usados);
    return colores+1;




    // for (u32 j = 0; j < n; j++)
    // {
    //     u32 vertice = Orden[j];
    //     u32 grado = Grado(vertice, G);
    //     printf("vertice: %u   color: %u\n", vertice, Color[vertice]);
    //         printf("    ");
    //         for (u32 i = 0; i < grado; i++)
    //         {
    //             printf("%u  ", IndiceVecino(i, vertice, G));
    //         }
    //         printf ("\n\n");
    // }

    // return colores+1;

                                                        // u32 indice = 0;
                                                        // for (u32 i = 0; i < NumeroDeVertices(G); i++)
                                                        // {
                                                        //     indice = Orden[i];
                                                        //     Color[indice] = i % colores; 
                                                        // }

                                                        // return colores + 1;
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
        imparpar[i] = empty_queue();
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
        imparpar[indice] = add_queue (imparpar[indice], i);
                                //printf("cola: %u   vertice: %u   color: %u\n", indice, i, Color [i]);
    }
                                //printf("\n\n\n\n\n");
    
    
    //paso el orden de imparpar a Orden
    indice = 0;
    for (u32 i = 0; i < num_de_colores + 1; i++)
    {
        u32 size =  length_queue(imparpar[i]);
        for (u32 j = 0; j < size; j++)
        {
            Orden[indice] = head_queue (imparpar[i]);
            imparpar[i] = tail_queue (imparpar[i]);
                                //printf("orden: %u   vertice: %u   color: %u\n", indice, Orden[indice], Color [Orden[indice]]);
            indice = indice + 1;
        }
        
    }


                                //printf("\n\n\n\n\n\n");
                                //printf ("segundo for\n");
                                // for (u32 i = 0; i < n; i++)
                                // {
                                //     printf("orden: %u   vertice: %u   color: %u\n", i, Orden[i], Color [Orden[i]]);
                                // }
    
    
    for (u32 i = 0; i < num_de_colores + 1; i++)
    {
        imparpar[i] = destroy_queue(imparpar[i]);
    }
    free (imparpar);

    return '0';
}


char OrdenJedi(Grafo G,u32* Orden,u32* Color){

    u32 v;
    //Calculo nro de colores
    u32 num_de_colores = 0;
    u32 n = NumeroDeVertices(G);

    for (u32 i = 0; i < n; i++)
    {

        if (Color[i] > num_de_colores){
            num_de_colores = Color[i];
        }
    }

    u32 *accumulator_jedi = calloc(num_de_colores + 1, sizeof(int));
    //Pongo todos los valores en 0
    for (u32 i = 0; i < num_de_colores + 1; i++)
    {
        accumulator_jedi[i] = 0;
    }

    //Creo un arreglo de listas de tamaño num_de_colores + 1
    cola * jedi = calloc(num_de_colores + 1, sizeof(cola));

    if (jedi == NULL)
    {
        printf("No se pudo alocar suficiente memoria para la lista de colas\n");
        return '1';
    }

    for (u32 i = 0; i < num_de_colores + 1; i++)
    {
        jedi[i] = empty_queue();
    }

    //Agrego los vertices a las listas de acuerdo a su color
    //y sumo el grado del vértice al acumulador de cada color
    for (u32 i = 0; i < n; i++)
    {
        jedi[Color[i]] = add_queue(jedi[Color[i]], i);
        accumulator_jedi[Color[i]] = accumulator_jedi[Color[i]] + Grado(i, G);
    }

    //Multiplico el acumulado de cada color por el color
    for (u32 i = 0; i < num_de_colores + 1; i++)
    {
        accumulator_jedi[i] = accumulator_jedi[i] * i;
    }

                                                    // u32 *debug = calloc(num_de_colores + 1, sizeof(int));
                                                    // u32 indice_debug = 0;

    //Paso las cada lista de jedi al arreglo orden, empezando por la que tiene el mayor acumulado
    v = 0;
    while (v < n) 
    {
        u32 max = 0;
        u32 color = 0;

        for (u32 j = 0; j < num_de_colores + 1; j++)
        {
            if (accumulator_jedi[j] > max){
                max = accumulator_jedi[j];
                color = j;
            }
        }
                                                    // debug [indice_debug] = accumulator_jedi[color];
                                                    // indice_debug ++;
        accumulator_jedi[color] = 0;
        u32 size =  length_queue(jedi[color]);
        for (u32 j = 0; j < size; j++)
        {
            Orden[v] = head_queue (jedi[color]);
            jedi[color] = tail_queue (jedi[color]);
            v = v + 1;
        }
    }
                                                    // for (u32 i = 0; i < n; i++)
                                                    // {
                                                    //     printf("orden: %u   vertice: %u   color: %u   peso del color: %u\n", i, Orden[i], Color [Orden[i]], debug[num_de_colores - Color [Orden[i]]]);
                                                    // }

    
    //libero memoria
    for (u32 i = 0; i < num_de_colores + 1; i++)
    {
        jedi[i] = destroy_queue(jedi[i]);
    }
    free(accumulator_jedi);
    free (jedi);

    return '0';
}

 