#include "../inc/input.h"
#include "../inc/adjacency.h"
#include "../inc/linealize.h"
#include "../inc/path_finding.h"
#include "../inc/start.h"
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

    /* Imprimimos el texto de inicio */
    print_start();

    while (running) {
        /* 
         * Declaramos el arreglo de strings que contendrá el input
         * del usuario, y lo adquirimos.
         */
        int input_len;
        float** tuple_inputs = NULL; /* Heap */

        {
            int cond = load_input_as_coord(&tuple_inputs, &input_len);
            if (cond == 1 || input_len == 1) {
                /* El input produjó un error */
                continue;
            }
            if (cond == 2) {
                /* Se llamó al cierre del programa */
                break;
            }
        }
        

        /*
         * "Linealizamos" el tuple de coordeenadas, esto para uso en el algoritmo de dijkstra
         *  en una lista de adyacencia.
         */

        int linear_inputs[input_len];

        for (int i = 0; i < input_len; ++i) {
            linear_inputs[i] = tuple_to_int((int) tuple_inputs[i][0], (int) tuple_inputs[i][1], CANT_VERT);
        }

        get_path(input_len, linear_inputs, vertices_adyacencia);


        /* Liberamos memoria */
        for (int i = 0; i < input_len; ++i) {
            free(tuple_inputs[i]);
            tuple_inputs[i] = NULL;
        }
        free(tuple_inputs);
        tuple_inputs = NULL;
    }

    for (int i = 0; i < CANT_TOTAL; ++i) free_set(vertices_adyacencia[i]);

    return 0;
}


