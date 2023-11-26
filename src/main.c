#include "../inc/input.h"
#include "../inc/parsing.h"
#include "../inc/adjacency.h"
#include "../inc/linealize.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INFINITO 1000
#define NULL_VERTEX -1

const int CANT_VERT = 14;
const int CANT_HOR = 8;
const int CANT_TOTAL = 14 * 8;


void dijkstra(int, int, Set*[CANT_TOTAL]);
void get_path(int, int, int[CANT_TOTAL]);

int main() {
    bool running = true;

    /* Generamos la lista de adyacencia. */
    Set* vertices_adyacencia[CANT_TOTAL];
    generate_adjacency(vertices_adyacencia);

    // Set* miset = init_set();
    // add_to_set(miset, 1);
    // add_to_set(miset, 2);
    // add_to_set(miset, 3);
    // add_to_set(miset, 4);
    // add_to_set(miset, 5);
    // print_set(miset);
    // printf("%d\n", miset->len);

    // remove_from_set(miset, 4);
    // print_set(miset);
    // printf("%d\n", miset->len);

    while (running) {
        /* 
         * Declaramos el arreglo de strings que contendrá el input
         * del usuario, y lo adquirimos.
         */
        float input_len;
        float** tuple_inputs; /* Heap */
        bool success = !load_input_as_coord(&tuple_inputs, &input_len);
        for (int i = 0; i < input_len; ++i) {
            printf("(%.2f, %.2f) ", tuple_inputs[i][0], tuple_inputs[i][1]);
        }
        printf("\n\n");

        /*
         * "Linealizamos" el tuple de coordeenadas, esto para uso en el algoritmo de dijkstra
         *  en una lista de adyacencia.
         */
        int n;
        if (input_len > 2) {n = 3;}
        else {n = 2;}
        int linear_inputs[n];

        for (int i = 0; i < n; ++i) {

            linear_inputs[i] = tuple_to_int((int) tuple_inputs[i][0], (int) tuple_inputs[i][1], CANT_VERT);
            printf("%d : ", linear_inputs[i]);
            print_set(vertices_adyacencia[linear_inputs[i]]);
        }
        printf("\n");

        // TEMPORAL
        if (input_len == 2) {
            int source = tuple_to_int((int) tuple_inputs[0][0], (int) tuple_inputs[0][1], CANT_VERT);

            int destiny = tuple_to_int((int) tuple_inputs[1][0], (int) tuple_inputs[1][1], CANT_VERT);
            dijkstra(source, destiny, vertices_adyacencia);
            printf("Done.\n");
        }


        /* Liberamos memoria */
        for (int i = 0; i < input_len; ++i) free(tuple_inputs[i]);
        for (int i = 0; i < input_len; ++i) free_set(vertices_adyacencia[i]);
        free(tuple_inputs);
        running = false;
    }
    return 0;
}


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
