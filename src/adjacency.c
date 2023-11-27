#include "../inc/adjacency.h"
#include "../inc/set.h"
#include <stdio.h>

/* Cantidad de calles verticales. */
extern const int CANT_VERT;

/* Cantidad de calles horizontales */
extern const int CANT_HOR;

void generate_adjacency(Set* vertices_adyacencia[CANT_VERT * CANT_HOR]) {
// Definimos las direcciones de las calles, estas estan dadas de izquierda a derecha (verticales) y arriba a abajo (horizontales)

    /* 
     * Definimos las direcciones de las calles, estas están ordenadas de izquierda a derecha
     * para las verticales, y de arriba a abajo para las horizontales.
     */
    int calles_horizontales[] = {AMBAS, DERECHA, IZQUIERDA, DERECHA, IZQUIERDA, DERECHA, IZQUIERDA, AMBAS};
    int calles_verticales[] = {ARRIBA, ABAJO, ARRIBA, ABAJO, ARRIBA, ABAJO, ARRIBA, ABAJO, ARRIBA, ABAJO, ARRIBA, ABAJO, ARRIBA, AMBAS};

    /* Esta es una matriz que nos permite tener una forma de visualizar los vértices. */
    int id[CANT_VERT][CANT_HOR];

    int contador = 0;
    for (int i = 0; i < CANT_HOR; ++i) {
        for (int j = 0; j < CANT_VERT; ++j) {
            id[j][i] = contador++;
        }
    }

    /* Imprimimos la matriz para poder ver las relaciones. */
    // for (int i = 0; i < CANT_HOR; ++i) {
    //     for (int j = 0; j < CANT_VERT; ++j) {
    //         printf("(%3d) ", id[i][j]);
    //     }
    //     printf("\n\n");
    // }

    /* 
     * Ahora generamos una lista de adyacencia para cada vértices. 
     * Cada vértice está relacionado con un conjunto de números.
     */

    // Set* vertices_adyacencia[CANT_VERT * CANT_HOR];

    /* Inicializamos los conjuntos de adyacencia de cada vértice. */
    for (int i = 0; i < CANT_VERT * CANT_HOR; ++i) {
        vertices_adyacencia[i] = init_set();
    }
    
    /* 
     * Creamos las relaciones entre los vértices de calles que van horizontalmente, siempre
     * teniendo en cuenta las direcciones.
     */

    for (int i = 0; i < CANT_HOR; ++i) {
        switch (calles_horizontales[i]) {
            case DERECHA:
                for (int j = 0; j < CANT_VERT - 1; ++j) {
                    add_to_set(vertices_adyacencia[i * CANT_VERT + j], i * CANT_VERT + j + 1);
                }
                break;
            case IZQUIERDA:
                for (int j = 1; j < CANT_VERT; ++j) {
                    add_to_set(vertices_adyacencia[i * CANT_VERT + CANT_VERT - j], i * CANT_VERT + CANT_VERT - j - 1);
                }
                break;
            case AMBAS:
                for (int j = 0; j < CANT_VERT - 1; ++j) {
                    add_to_set(vertices_adyacencia[i * CANT_VERT + j], i * CANT_VERT + j + 1);
                }
                for (int j = 1; j < CANT_VERT; ++j) {
                    add_to_set(vertices_adyacencia[i * CANT_VERT + CANT_VERT - j], i * CANT_VERT + CANT_VERT - j - 1);
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
    for (int i = 0; i < CANT_VERT; ++i) {
        switch (calles_verticales[i]) {
            case ABAJO:
                for (int j = 0; j < CANT_HOR - 1; ++j) {
                    add_to_set(vertices_adyacencia[i + j * CANT_VERT], i + (j + 1) * CANT_VERT);
                }
                break;
            case ARRIBA:
                for (int j = 1; j < CANT_HOR; ++j) {
                    add_to_set(vertices_adyacencia[i + (CANT_HOR - j) * CANT_VERT], i + (CANT_HOR - 1 - j) * CANT_VERT);
                }
                break;
            case AMBAS:
                for (int j = 0; j < CANT_HOR - 1; ++j) {
                    add_to_set(vertices_adyacencia[i + j * CANT_VERT], i + (j + 1) * CANT_VERT);
                }
                for (int j = 1; j < CANT_HOR; ++j) {
                    add_to_set(vertices_adyacencia[i + (CANT_HOR - j) * CANT_VERT], i + (CANT_HOR - 1 - j) * CANT_VERT);
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
    remove_from_set(vertices_adyacencia[97],96 );

    /* Agregamos los de la diagonal, se supone que va desde abajo hacia arriba (?). */
    add_to_set(vertices_adyacencia[111], 96);
    add_to_set(vertices_adyacencia[96], 81);
    add_to_set(vertices_adyacencia[81], 66);
    remove_from_set(vertices_adyacencia[96], 97);
    remove_from_set(vertices_adyacencia[81], 96);
    remove_from_set(vertices_adyacencia[96], 111);

    /* Imprimimos los vértices adyacentes para verificar. */
    // for (int i = 0; i < CANT_VERT * CANT_HOR; ++i) {
    //     printf("V:DA de %3d: ", i);
    //     print_set(vertices_adyacencia[i]);
    // }
}
