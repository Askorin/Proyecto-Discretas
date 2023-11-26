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

    generate_adjacency();
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

        /*
         * "Linealizamos" el tuple de coordeenadas, esto para uso en el algoritmo de dijkstra
         *  en una lista de adyacencia.
         */
        int linear_inputs[3];
        for (int i = 0; i < input_len; ++i) {
            linear_inputs[i] = tuple_to_int((int) tuple_inputs[i][1], (int) tuple_inputs[i][0], CANT_VERT);
        }
        printf("\n");
        for (int i = 0; i < input_len; ++i) printf("%d, ", linear_inputs[i]); 
        printf("\n");



        /* Liberamos memoria */
        for (int i = 0; i < input_len; ++i) free(tuple_inputs[i]);
        free(tuple_inputs);


    }
    return 0;
}
