#include <stdlib.h>
#include <time.h>
#include "APIG23.h"
#include "APIParte2.h"
#include <stdio.h>

int main()
{
    double time_spent = 0.0;
    clock_t begin = clock();

    Grafo G = NULL;
    G = ConstruirGrafo();

    u32 N = NumeroDeVertices(G);
    u32 * Orden = calloc(N, sizeof(u32));
    u32 * Orden1 = calloc(N, sizeof(u32));
    u32 * Color = calloc(N, sizeof(u32));
    u32 * Color1 = calloc(N, sizeof(u32));

    for (u32 i = 0; i < N; i++){
        Orden[i] = i;
        Orden1[i] = i;
    }

    u32 color;
    u32 color1;
    char res;
    u32 selector = 0;
    u32 i = 0;
    color = Greedy (G, Orden, Color);
    color = Greedy (G, Orden1, Color1);

    while (i < 500){
        
        if(selector < 16){
            res = OrdenImparPar (N, Orden, Color);
            if (res == 1){
                break;
            }
            color = Greedy (G, Orden, Color);
            
            

            res = OrdenJedi (G, Orden1, Color1);
            if (res == 1){
                break;
            }
            color1 = Greedy (G, Orden1, Color1);
            selector ++;
        }
        else{
            
            res = OrdenImparPar (N, Orden1, Color1);
            if (res == 1){
                break;
            }
            color1 = Greedy (G, Orden1, Color1);

            res = OrdenJedi (G, Orden, Color);
            if (res == 1){
                break;
            }
            color1 = Greedy (G, Orden, Color);

            selector ++;
            if (selector == 32){
                selector = 0;
            }
        }
        i ++;
    }

    if (res == 1){
        return 1;
    }
    if (color <= color1){
        printf("Greedy coloreo con %u colores\n", color);
    }
    else{
        printf("Greedy coloreo con %u colores\n", color1);
    }
    DestruirGrafo(G);

    free(Orden);
    free(Color);

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds\n", time_spent);
    return 0;
}