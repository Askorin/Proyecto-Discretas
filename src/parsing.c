#include "../inc/parsing.h"
#include "../inc/input.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>

#define MAX 1000

void strrev(char* str)
{
    // if the string is empty
    if (!str) {
        return;
    }
    // pointer to start and end at the string
    int i = 0;
    int j = strlen(str) - 1;
 
    // reversing string
    while (i < j) {
        char c = str[i];
        str[i] = str[j];
        str[j] = c;
        i++;
        j--;
    }
}

int get_coordinate_from_direction(char * direction, float * x_holder, float * y_holder) {
    // Obtenemos la calle y el numero a partir de la direccion
    char str[MAX];
    strcpy(str, direction);
    strrev(str); // Se invierte porque los espacios son problematicos en el nombre de una calle

    int street_number;
    {
        char * temp = strtok(str, " ");
        strrev(temp);
        street_number = atoi(temp);
    }
	char * street_name = strtok(NULL, "");
    strrev(street_name);

    // Creamos las variables de coordenadas
    float x;
    float y;

    // Definimos las calles horizontales
    char * h_streets[3] = {"Carrera", "Maipu", "Freire"};
    int h_streets_number = 3;
    int h_streets_first_direction = 0;

    // Revisamos si es una calle horizontal
    int cond = false;
    for (int i = 0; i < h_streets_number; i++) {
        if (strcmp(street_name, h_streets[i]) == 0) {
            cond = true;

            x = ((float)(street_number - h_streets_first_direction)) / 100;
            y = (float)i;
        }
    }

    // Se detecto que es una calle horizontal
    if (cond) {
        *(x_holder) = x;
        *(y_holder) = y;
        return 0;
    }

    // Definimos las calles verticales
    char * v_streets[3] = {"Arturo Prat", "Serrano", "Salas"};
    int v_streets_number = 3;
    int v_streets_first_direction = 100;

    // Revisamos si es una calle vertical
    cond = false;
    for (int i = 0; i < v_streets_number; i++) {
        if (strcmp(street_name, v_streets[i]) == 0) {
            cond = true;

            x = (float)i;
            y = 7.0 - ((float)(street_number - v_streets_first_direction)) / 100;
        }
    }

    // Se detecto que es una calle vertical
    if (cond) {
        *(x_holder) = x;
        *(y_holder) = y;
        return 0;
    }

    // El programa falló
    printf("Entrada no válida: Ingrese una dirección válida\n");
    return 0;
}

int load_input_as_coord(float *** coord_collection_holder, float * number_of_coords_holder) {
    char ** input;
    int n;
    if (load_input_as_string(&input, &n)) {
        return 1; //La función falló
    }

    /*
    printf("%d\n", n);
    // Imprimimos las direcciones (Temporal)
    for (int i = 0; i < n; i++) {
        printf("%s\n", input[i]);
    }
    */
    float point_x[n];
    float point_y[n];
    for (int i = 0; i < n; i++) {
        if (get_coordinate_from_direction(input[i], &point_x[i], &point_y[i])) {
        return 1; //La función falló
        }
    }

    //Reservamos en la memoria
    float x;
    float * point;
    float ** coord_collection = NULL;

    coord_collection = (float **) realloc(coord_collection, n * sizeof(float *));
    for (int i = 0; i < n; i++) {
        *(coord_collection + i) = (float *) realloc(*(coord_collection + i), 2 * sizeof(float));
    }

    // Escribimos en la entrada
    *(coord_collection_holder) = coord_collection;
    *(number_of_coords_holder) = n;

    //Escribimos en la memoria reservada
    for (int i = 0; i < n; i++) {
        *(*(*coord_collection_holder + i) + 0) = point_x[i];
        *(*(*coord_collection_holder + i) + 1) = point_y[i];
    }
	return 0;
}
