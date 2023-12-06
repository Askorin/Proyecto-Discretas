#include "../inc/input.h"
#include "../inc/adjacency.h"
#include "../inc/linealize.h"
#include "../inc/path_finding.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

#define INFINITO 1000
#define NULL_VERTEX -1

const int CANT_VERT = 14;
const int CANT_HOR = 8;
const int CANT_TOTAL = 14 * 8;

int main() {
    bool running = true;

    /* Generamos la lista de adyacencia. */
    Set* vertices_adyacencia[CANT_TOTAL];
    generate_adjacency(vertices_adyacencia);


    while (running) {
        /* 
         * Declaramos el arreglo de strings que contendrá el input
         * del usuario, y lo adquirimos.
         */
        float input_len;
        float** tuple_inputs; /* Heap */

        if (load_input_as_coord(&tuple_inputs, &input_len)) {
            /* El input produjó un error*/
            printf("\nIngrese la entrada nuevamente:\n");
            continue;
        }

        /*
         * "Linealizamos" el tuple de coordeenadas, esto para uso en el algoritmo de dijkstra
         *  en una lista de adyacencia.
         */

        int linear_inputs[(int) input_len];

        for (int i = 0; i < (int) input_len; ++i) {
            linear_inputs[i] = tuple_to_int((int) tuple_inputs[i][0], (int) tuple_inputs[i][1], CANT_VERT);
        }

        get_path((int) input_len, linear_inputs, vertices_adyacencia);


        /* Liberamos memoria */
        for (int i = 0; i < input_len; ++i) free(tuple_inputs[i]);
        for (int i = 0; i < input_len; ++i) free_set(vertices_adyacencia[i]);
        free(tuple_inputs);
        running = false;
    }
    return 0;
}


