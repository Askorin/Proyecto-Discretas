#include "../inc/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>


/* Esto es bastante inseguro! Jaja */
#define MAX 1000

/*
 * Recibe un string y lo invierte.
 * Cumple la misma funcionalidad que la función strrev,
 * pero esta ultima esta solo en algunas versiones de la libreria <string.h>.
*/
void string_reverse(char* str)
{
    /* Revisamos si el string esta vacio */
    if (!str) {
        return;
    }
    /* Puntero al inicio y final del string */
    int i = 0;
    int j = strlen(str) - 1;
 
    /* Invertimos el string */
    while (i < j) {
        char c = str[i];
        str[i] = str[j];
        str[j] = c;
        i++;
        j--;
    }
}

/*
 * Esta función llama a la terminal para el ingreso de datos,
 * Recibe un puntero a un array de strings, y recibe un puntero a un entero.
 * El array de strings se sobrescribira de forma que:
 *   - El elemento i-esimo del array es un string que corresponde a la entrada de una dirección
 *   - El array tiene como numero de elementos al numero de entradas que se detectaron
 * El puntero al entero se sobrescribira de forma que:
 *   - Ahora contiene el numero de entradas que se detectaron
 * 
 * Esta función devuelve:
 * 0 - Si se realizó con exito
 * 1 - Si hubo un error en su ejecución
 * 2 - Si se llamó al cierre del programa
*/
int load_input_as_string(char*** input_holder, int* number_of_inputs_holder) {
    int i;
    int counter;

    /* Recibimos el string de entrada */
    printf("\nIngrese su instrucción:\n");

    char input_str [MAX];
    scanf("%s", input_str);

    /* Revisamos si comienza por salir */
    if (strcmp(input_str, "salir") == 0) {
        printf("Cerrando programa.\n");
        return 2;
    }

    /* Revisamos si comienza por rutas */
    if (strcmp(input_str, "rutas") != 0) {
        printf("Entrada no válida: Utilice el comando rutas\n");
        /* Debemos vaciar el buffer */
        while (true) {
            char c = getchar();
            if (c == '\n') {
                break;
            }
        }
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

    /* Revisamos si las comillas estan balanceadas */
    if (counter % 2 != 0) {
        printf("Entrada no válida (Comillas no balanceadas): Use comillas solo para indicar direcciones\n");
        return 1;
    }
    if (counter == 0) {
        printf("Entrada no válida: Use comillas para indicar dirrecciones\n");
        return 1;
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

        /* Manejamos el error de escribir fuera de las comillas*/
        if (state == 0 && c != '\"' && c != '\0' && c != ' ') {
            printf("Entrada no válida: Encierre los parámetros en comillas\n");
            return 1;
        }

        i++;
        letter_counter += 1;
    }

    /* Reservamos memoria */
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

    /* Escribimos en la entrada */
    *(input_holder) = output;
    *(number_of_inputs_holder) = n;

    /* Escribimos en la memoria reservada */
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

/*
 * Esta función escribe una coordenada a partir de un string que contiene una dirección,
 * Recibe el string que contiene la dirección y dos punteros de números flotantes.
 * Los punteros se sobrescribiran de forma que:
 *   - El primero contendrá al primer elemento de la coordenada representada por la dirección
 *   - El segundo contendrá al segundo elemento de la coordenada representada por la dirección
 * Es importante especificar como funciona el sistema coordenado:
 *   - El origen es donde se intersecta la calle horizontal más a la izquierda
 *     con la calle vertical más arriba (Vistas desde Google Map)
 *   - El eje x es el vertical
 *   - El eje y es el horizontal
 * De esta forma, es analogo a como funciona la enumeración de una matriz.
 * 
 * Esta función devuelve:
 * 0 - Si se realizó con exito
 * 1 - Si hubo un error en su ejecución
*/
int get_coordinate_from_address(char * address, float * x_holder, float * y_holder) {
    /* Copiamos la entrada en un string */
    char str[MAX];
    strcpy(str, address);
    
    /* Separamos el nombre de la calle del número de inmueble */
    string_reverse(str); // Se invierte porque los espacios son problematicos en el nombre de una calle
    int street_number;
    {
        char * temp = strtok(str, " "); // Obtenemos el número, pero invertido
        string_reverse(temp);           // por lo tanto, lo invertimos de nuevo

        /* Manejamos el error de una entrada vacia */
        if (!temp) {
            printf("Entrada no válida: Se entregó una dirección vacia\n");
            return 1;
        }

        /* Manejamos el error de un numero de inmueble invalido */
        int i = 0;
        while (true) {
            char c = temp[i];
            if (c == '\0') {
                break;
            }
            if (strchr("-0123456789", c) == NULL) {
                printf("Entrada no válida: El formato de la entrada es "
                       "\"[Nombre calle] [Número de inmueble]\"\n");
                return 1;
            }
            i++;
        }

        street_number = atoi(temp); // Ojo, por ejemplo, atoi("500a") devuelve 500, por eso la verificación
    }
	char * street_name = strtok(NULL, "");
    string_reverse(street_name);

    /* Manejamos el error de una entrada sin calle*/
    if (!street_name) {
        printf("Entrada no válida: El formato de la entrada es "
               "\"[Nombre calle] [Número de inmueble]\"\n");
        return 1;
    }

    /* Creamos las variables de coordenadas */
    float x;
    float y;

    /* Definimos las calles horizontales */
    int h_streets_number = 8;
    char * h_streets[8] = {"Carrera", "Maipu", "Freire", "Barros Arana",
                           "O'Higgins", "San Martin", "Cochrane", "Chacabuco"};
    int h_streets_first_address = 0;

    /* Revisamos si es una calle horizontal */
    int cond = false;
    for (int i = 0; i < h_streets_number; i++) {
        if (strcmp(street_name, h_streets[i]) == 0) {
            cond = true;

            x = (float)i;
            y = ((float)(street_number - h_streets_first_address)) / 100;
        }
    }

    /* Se detecto que es una calle horizontal */
    if (cond) {
        *(x_holder) = x;
        *(y_holder) = y;

        /* Manejamos el error de ingresar un numero de inmueble fuera de rango*/
        if (y < 0.0 || y > 13.0) {
            printf("Entrada no válida: La direccion %s %d "
                   "esta fuera del rango del programa\n", street_name, street_number);
            printf("Intente ingresando la misma calle pero con un número de inmueble entre 0 y 1300\n");
            return 1;
        }

        return 0;
    }

    /* Definimos las calles verticales */
    int v_streets_number = 14;
    char * v_streets[14] = {"Arturo Prat", "Serrano", "Salas", "Angol", "Lincoyan",
                           "Rengo", "Caupolican", "Anibal Pinto", "Colo Colo",
                           "Castellon", "Tucapel", "Orompello", "Ongolmo", "Paicavi"};
    int v_streets_first_address = 100;

    /* Revisamos si es una calle vertical */
    cond = false;
    for (int i = 0; i < v_streets_number; i++) {
        if (strcmp(street_name, v_streets[i]) == 0) {
            cond = true;

            x = 7.0 - ((float)(street_number - v_streets_first_address)) / 100;
            y = (float)i;
        }
    }

    /* Se detecto que es una calle vertical */
    if (cond) {
        *(x_holder) = x;
        *(y_holder) = y;

        /* Manejamos el error de ingresar un numero de inmueble fuera de rango */
        if (x < 0.0 || x > 7.0) {
            printf("Entrada no válida: La direccion %s %d "
                   "esta fuera del rango del programa\n", street_name, street_number);
            printf("Intente ingresando la misma calle pero con un número de inmueble entre 100 y 800\n");
            return 1;
        }

        return 0;
    }

    /* Revisamos si es la diagonal */
    if ( strcmp(street_name, "Pedro Aguirre Cerda") == 0
      || strcmp(street_name, "Diagonal") == 0 ) {
        x = 8.0 - ((float)(street_number)) / 100;
        y = 14.0 - ((float)(street_number)) / 100;
        *(x_holder) = x;
        *(y_holder) = y;

        /* Manejamos el error de ingresar un numero de inmueble fuera de rango */
        if (street_number < 100 || street_number > 400) {
            printf("Entrada no válida: La direccion %s %d "
                   "esta fuera del rango del programa\n", street_name, street_number);
            printf("Intente ingresando la misma calle pero con un número de inmueble entre 100 y 400\n");
            return 1;
        }

        return 0;
    }

    /* El programa no encontró la calle especificada, manejamos el error */
    printf("Entrada no válida: La calle %s no existe\n", street_name);
    printf("Verifique que la calle que se esta intentando ingresar coincida exactamente "
           "en nombre con las calles que maneja el programa\n");
    return 1; // El programa falló
}

/*
 * Esta función llama a la terminal para el ingreso de datos,
 * Lee la entrada, las interpreta como direcciones, y almacena las coordenadas correspondientes
 * Recibe: 
 *   - Un puntero a un array (otro puntero) de tuples (otro puntero) de numeros flotantes
 *     Se puede pensar como el puntero a una colección de coordenadas (tuples)
 *   - Un puntero a un entero
 * La colección de coordenadas se sobrescribira de forma que:
 *   - El elemento i-esimo de la colección es la coordenada que corresponde
 *     a la entrada de la i-esima dirección ingresada
 *   - La colección tiene como numero de coordenadas al numero de entradas que se detectaron
 * El puntero al entero se sobrescribira de forma que:
 *   - Ahora contiene el numero de entradas que se detectaron
 * 
 * Esta función devuelve:
 * 0 - Si se realizó con exito
 * 1 - Si hubo un error en su ejecución
 * 2 - Si se llamó al cierre del programa
*/
int load_input_as_coord(float *** coord_collection_holder, float * number_of_coords_holder) {
    char ** input;
    int n;

    { 
        int cond = load_input_as_string(&input, &n);
        if (cond == 1) {
            return 1; //La función falló
        }
        if (cond == 2) {
            return 2; //Se llamó al cierre del programa
        }
    }


    float point_x[n];
    float point_y[n];
    for (int i = 0; i < n; i++) {
        if (get_coordinate_from_address(input[i], &point_x[i], &point_y[i])) {
            return 1; //La función falló
        }
    }

    //Reservamos en la memoria
    float ** coord_collection = NULL;

    coord_collection = realloc(coord_collection, n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        *(coord_collection + i) = realloc(*(coord_collection + i), 2 * sizeof(float));
    }

    // Escribimos en la entrada
    *(coord_collection_holder) = coord_collection;
    *(number_of_coords_holder) = n;

    //Escribimos en la memoria reservada
    for (int i = 0; i < n; i++) {
        *(*(*coord_collection_holder + i) + 0) = point_x[i];
        *(*(*coord_collection_holder + i) + 1) = point_y[i];
    }

    //Liberamos memoria
    for (int i = 0; i < n; i++) {
        free(input[i]);
    }
    free(input);

	return 0;
}
