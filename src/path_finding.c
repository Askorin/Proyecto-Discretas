#include "../inc/path_finding.h"
#include "../inc/linealize.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>

#define INFINITO 1000
#define NULL_VERTEX -1


void dijkstra(int source, Set* ady[CANT_TOTAL], int padre[CANT_TOTAL]) {
    int dist[CANT_TOTAL];
    Set* visto = init_set();
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
}


void get_path(int input_len, int input[input_len], Set* ady[CANT_TOTAL]) {

     char * v_streets[14] = {"Arturo Prat", "Serrano", "Salas", "Angol", "Lincoyan",
                           "Rengo", "Caupolican", "Anibal Pinto", "Colo Colo",
                           "Castellon", "Tucapel", "Orompello", "Ongolmo", "Paicavi"};
    char * h_streets[8] = {"Carrera", "Maipu", "Freire", "Barros Arana",
                           "O'Higgins", "San Martin", "Cochrane", "Chacabuco"};

    printf("El camino a seguir es:\n");    
    if (input_len > 2) {
        /* Movemos el indice uno al final */
        for (int i = 2; i < input_len; ++i) {
            int temp = input[i];
            input[i] = input[i - 1];
            input[i - 1] = temp;
        }

        for (int i = 0; i < input_len - 1; ++i) {
            int source = input[i];
            int destiny = input[i + 1];
            int padre[CANT_TOTAL];
            dijkstra(source, ady, padre);
            int path_len = 0;
            int* path = generate_path(source, destiny, padre, &path_len);

            for (int i = path_len - 1; i >= 0; --i) {
                printf("%s con %s\n",h_streets[path[i]/14],v_streets[path[i]%14]);
            }
            free(path);
        }

    } else if (input_len == 2) {
        int source = input[0];
        int destiny = input[1];
        int padre[CANT_TOTAL];
        dijkstra(source, ady, padre);
        int path_len = 0;
        int* path = generate_path(source, destiny, padre, &path_len);

        for (int i = path_len - 1; i >= 0; --i) {
            printf("%s con %s\n",h_streets[path[i]/14],v_streets[path[i]%14]);
        }
        printf("\n");
        free(path);
        
    } else {
        printf("No implementado.\n");
        return;
    }

}

int* generate_path(int source, int destiny, int padre[CANT_TOTAL], int* path_len) {
    int vertex = destiny;
    int* path = NULL;
    while (vertex != source) {
        ++(*path_len);
        path = realloc(path, sizeof(int) * (*path_len));
        path[(*path_len) - 1] = vertex;
        vertex = padre[vertex];
    }
    return path;
}
