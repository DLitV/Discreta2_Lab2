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
    u32 * Color = calloc(N, sizeof(u32));

    for (u32 i = 0; i < N; i++)
    {
        Orden[i] = i;
    }

    u32 color = Greedy(G, Orden, Color);

    printf("\n\ngreedy pinto con %u colores\n\n", color);

    char res = OrdenImparPar(N, Orden, Color);
    
    res = res;

    DestruirGrafo(G);

    free(Orden);
    free(Color);

    clock_t end = clock();
    time_spent += (double)(end - begin) / CLOCKS_PER_SEC;
    printf("The elapsed time is %f seconds\n", time_spent);
    return 0;
}