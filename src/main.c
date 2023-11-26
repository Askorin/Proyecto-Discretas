#include "../inc/input.h"
#include "../inc/parsing.h"
#include "../inc/adjacency.h"
#include "../inc/linealize.h"
#include <stdbool.h>
#include <stdio.h>
#include <stdlib.h>

const int CANT_VERT = 14;
const int CANT_HOR = 8;

int main() {
    bool running = true;

    /* Generamos la lista de adyacencia. */
    Set* vertices_adyacencia[CANT_VERT * CANT_HOR];
    generate_adjacency(vertices_adyacencia);

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



        /* Liberamos memoria */
        for (int i = 0; i < input_len; ++i) free(tuple_inputs[i]);
        free(tuple_inputs);

        running = false;
    }
    return 0;
}
