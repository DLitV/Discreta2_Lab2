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

    for (u32 i = 0; i < N; i++)
    {
        Orden[i] = i;
        Orden1[i] = i;
    }

    u32 color;
    char res;
    u32 selector = 0;
    u32 i = 0;
    color = Greedy (G, Orden, Color);
    color = Greedy (G, Orden1, Color1);

    while (i < 512)
    {
        if(selector < 16){
            color = Greedy (G, Orden, Color);
            res = OrdenImparPar (N, Orden, Color);
            printf("greedy OrdenImparPar pinto con %u colores, selector %u\n", color, selector);

            color = Greedy (G, Orden1, Color1);
            res = OrdenJedi (G, Orden1, Color1);
            printf("greedy OrdenJedi pinto con %u colores, selector %u\n", color, selector);
            selector ++;
        }
        else{
            
            color = Greedy (G, Orden1, Color1);
            res = OrdenImparPar (N, Orden1, Color1);
            printf("greedy OrdenImparPar pinto con %u colores, selector %u\n", color, selector);

            color = Greedy (G, Orden, Color);
            res = OrdenJedi (G, Orden, Color);
            printf("greedy OrdenJedi pinto con %u colores, selector %u\n", color, selector);

            selector ++;
            if (selector == 32)
            {
                selector = 0;
            }
        }
        res = res;
        i ++;
    }

    DestruirGrafo(G);

    free(Orden);
    free(Color);

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds\n", time_spent);
    return 0;
}