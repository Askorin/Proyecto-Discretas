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
        if (load_input_as_coord(&tuple_inputs, &input_len)) {
            /* El input produjó un error*/
            printf("\nIngrese la entrada nuevamente:\n");
            continue;
        }
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
        else {n = input_len;}
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


