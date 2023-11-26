#include "../inc/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/* Esto es bastante inseguro! Jaja */
#define MAX 1000

/*
 * Esta función llama a la terminal para el ingreso de datos,
 * Recibe un puntero a un array de strings, y recibe un puntero a un entero.
 * El array de strings se sobrescribira de forma que:
 *   - El elemento i-esimo del array es un string que corresponde a la entrada de una dirección
 *   - El array tiene como numero de elementos al numero de entradas que se detectaron
 * El entero se sobreescribiria de forma que:
 *   - Ahora contiene el numero de entradas que se detectaron
 * 
 * Esta función devuelve:
 * 0 - Si se realizó con exito
 * 1 - Si hubo un error en su ejecución
*/

int load_input_as_string(char*** input_holder, int* number_of_inputs_holder) {
    int i;
    int counter;

    /* Recibimos el string de entrada */
    char input_str [MAX];
    scanf("%s", input_str);

    /* Revisamos si comienza por rutas */
    if (strcmp(input_str, "rutas") != 0) {
        printf("Entrada no válida: Utilice el comando \"rutas\".\n");
        return 1;
    }

    /* Recibimos el resto del string de entrada */
    for (int i = 0; i < MAX; i++) {
        char c = getchar();
        if (c == '\n') {
            input_str[i] = '\0';
            break;
        }
        input_str[i] = c;
    }

    /* Contamos cuantas comillas hay */
    i = 0;
    counter = 0;
    while (true) {
        char c = input_str[i];
        if (c == '\0') {
            break;
        }
        if (c == '\"') {
            counter += 1;
        }
        i++;
    }

    /* Cantidad de direcciones que debemos enviar */
    int n = counter / 2;
    char inputs[n][MAX];

    /* Armamamos las direcciones */
    int state = 0;
    int word_counter = 0;
    int letter_counter = 0;
    i = 0;
    while (true) {
        char c = input_str[i];

        //Estado: 0. No escribiendo; 1. Escribiendo.
        if (c == '\"') {
            if (state == 0) {
                state = 1;
                letter_counter = 0;
                }
            else if (state == 1) {
                inputs[word_counter][letter_counter] = '\0';
                state = 0;
                word_counter += 1;

                if (word_counter >= n) {break;}
            }
        }

        if (state == 1) {
            if (c != '\"') {
                inputs[word_counter][letter_counter] = c;
            }
            else {
                letter_counter += -1;
            }
        }

        i++;
        letter_counter += 1;
    }

    // Reservamos memoria
    char** output = NULL;
    output = realloc(output, n * sizeof(char *));
    for (int i = 0; i < n; i++) {
        int counter = 0;
        while (true) {
            char c = inputs[i][counter];
            if (c == '\0') {
                counter += 1;
                break;
            }
            counter += 1;
        }

        *(output + i) = NULL;
        *(output + i) = realloc(*(output + i), counter * sizeof(char));
    }

    // Escribimos en la entrada
    *(input_holder) = output;
    *(number_of_inputs_holder) = n;

    // Escribimos en la memoria reservada
    for (int i = 0; i < n; i++) {
        int j = 0;
        while (true) {
            char c = inputs[i][j];
            if (c == '\0') {
                *(*(*input_holder + i) + j) = inputs[i][j];
                break;
            }
            *(*(*input_holder + i) + j) = inputs[i][j];
            j += 1;
        }
    }

    return 0;
}
