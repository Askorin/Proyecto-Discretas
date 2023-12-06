#include "../inc/path_finding.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define INFINITO 1000
#define NULL_VERTEX -1


void dijkstra(int source, int destiny, Set* ady[CANT_TOTAL]) {
    int dist[CANT_TOTAL];
    Set* visto = init_set();
    int padre[CANT_TOTAL];
    int peso = 1;

    for (int i = 0; i < CANT_TOTAL; ++i) {
        dist[i] = INFINITO;
        padre[i] = NULL_VERTEX;
    }
    dist[source] = 0;
    
    /* 
     * Mientras la cantidad de vértices vistos sea menor a la
     * cantidad de vértices totales, iteramos.
     * Esto es idéntico a decir que queremos iterar mientras
     * exista un vértice que no haya sido visitado.
     */
    while (visto->len < CANT_TOTAL) {
        int u;

        /* Encontramos algún vértice arbitrario no visto. */
        for (int i = 0; i < CANT_TOTAL; ++i) {
            if (!in_set(visto, i)) {
                u = i;
                break;
            }
        }
        
        /* 
         * u será el vértice a menor distancia de la fuente, que no
         * haya sido visitado.
         */
        for (int i = 0; i < CANT_TOTAL; ++i) {
            if (in_set(visto, i)) continue;
            if (dist[i] < dist[u]) {
                u = i; 
            }
        }

        add_to_set(visto, u);

        /* Iteramos sobre los vértices adyacentes a u */
        for (int i = 0; i < ady[u]->len; ++i) {
            int v = ady[u]->elementos[i];

            /* 
             * Si la distancia entre source y v es mayor a la distancia entre
             * source y u más un paso, entonces, esta es la nueva distancia,
             * y el camino más corto (hasta ahora) involucra este camino.
             */
            if (dist[v] > dist[u] + peso) {
                dist[v] = dist[u] + peso;
                padre[v] = u;
            }
        }
    }
    free_set(visto);

    get_path(source, destiny, padre);
}


void get_path(int source, int destiny, int padre[CANT_TOTAL]) {
    int vertex = destiny;
    int* path = NULL;
    int path_len;
    while (vertex != source) {
        ++path_len;
        path = realloc(path, sizeof(int) * path_len);
        path[path_len - 1] = vertex;
        vertex = padre[vertex];
    }

    for (int i = path_len - 1; i >= 0; --i) {
        printf("%d ", path[i]);
    }
    printf("\n");
    free(path);
}
