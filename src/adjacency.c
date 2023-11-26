#include "../inc/adjacency.h"
#include "../inc/set.h"
#include <stdio.h>

/* Cantidad de calles verticales. */
const int x = 14;

/* Cantidad de calles horizontales */
const int y = 8;

void generate_adjacency() {
// Definimos las direcciones de las calles, estas estan dadas de izquierda a derecha (verticales) y arriba a abajo (horizontales)

    /* 
     * Definimos las direcciones de las calles, estas están ordenadas de izquierda a derecha
     * para las verticales, y de arriba a abajo para las horizontales.
     */
    int calles_horizontales[] = {AMBAS, DERECHA, IZQUIERDA, DERECHA, IZQUIERDA, DERECHA, IZQUIERDA, AMBAS};
    int calles_verticales[] = {ARRIBA, ABAJO, ARRIBA, ABAJO, ARRIBA, ABAJO, ARRIBA, ABAJO, ARRIBA, ABAJO, ARRIBA, ABAJO, ARRIBA, AMBAS};

    /* Esta es una matriz que nos permite tener una forma de visualizar los vértices. */
    int id[x][y];

    int contador = 0;
    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
            id[j][i] = contador++;
        }
    }

    /* Imprimimos la matriz para poder ver las relaciones. */
    for (int i = 0; i < y; ++i) {
        for (int j = 0; j < x; ++j) {
            printf("(%3d) ", id[i][j]);
        }
        printf("\n\n");
    }

    /* 
     * Ahora generamos una lista de adyacencia para cada vértices. 
     * Cada vértice está relacionado con un conjunto de números.
     */

    Set* vertices_adyacencia[x * y];

    /* Inicializamos los conjuntos de adyacencia de cada vértice. */
    for (int i = 0; i < x * y; ++i) {
        vertices_adyacencia[i] = init_set();
    }
    
    /* 
     * Creamos las relaciones entre los vértices de calles que van horizontalmente, siempre
     * teniendo en cuenta las direcciones.
     */

    for (int i = 0; i < y; ++i) {
        switch (calles_horizontales[i]) {
            case DERECHA:
                for (int j = 0; j < x - 1; ++j) {
                    add_to_set(vertices_adyacencia[i * x + j], i * x + j + 1);
                }
                break;
            case IZQUIERDA:
                for (int j = 1; j < x; ++j) {
                    add_to_set(vertices_adyacencia[i * x + x - j], i * x + x - j - 1);
                }
                break;
            case AMBAS:
                for (int j = 0; j < x - 1; ++j) {
                    add_to_set(vertices_adyacencia[i * x + j], i * x + j + 1);
                }
                for (int j = 1; j < x; ++j) {
                    add_to_set(vertices_adyacencia[i * x + x - j], i * x + x - j - 1);
                }
                break;
            default:
                break;
        }
    }

    /* 
     * Creamos las relaciones entre los vértices de calles que van verticalmente, siempre
     * teniendo en cuenta las direcciones.
     */
    for (int i = 0; i < x; ++i) {
        switch (calles_verticales[i]) {
            case ABAJO:
                for (int j = 0; j < y - 1; ++j) {
                    add_to_set(vertices_adyacencia[i + j * x], i + (j + 1) * x);
                }
                break;
            case ARRIBA:
                for (int j = 1; j < y; ++j) {
                    add_to_set(vertices_adyacencia[i + (y - j) * x], i + (y - 1 - j) * x);
                }
                break;
            case AMBAS:
                for (int j = 0; j < y - 1; ++j) {
                    add_to_set(vertices_adyacencia[i + j * x], i + (j + 1) * x);
                }
                for (int j = 1; j < y; ++j) {
                    add_to_set(vertices_adyacencia[i + (y - j) * x], i + (y - 1 - j) * x);
                }
                break;
            default:
                break;
        }
    }
    
    /* Se eliminan los caminos peatonales. */
    remove_from_set(vertices_adyacencia[21], 35);
    remove_from_set(vertices_adyacencia[35], 49);
    remove_from_set(vertices_adyacencia[49], 50);
    remove_from_set(vertices_adyacencia[50], 51);

    /* Agregamos los de la diagonal, se supone que va desde abajo hacia arriba (?). */
    remove_from_set(vertices_adyacencia[111], 96);
    remove_from_set(vertices_adyacencia[96], 81);
    remove_from_set(vertices_adyacencia[81], 66);

    /* Imprimimos los vértices adyacentes para verificar. */
    for (int i = 0; i < x * y; ++i) {
        printf("V:DA de %3d: ", i);
        print_set(vertices_adyacencia[i]);
    }
}
