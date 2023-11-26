#ifndef ADJACENCY_H
#define ADJACENCY_H
#include <set.h>

extern const int CANT_VERT;
extern const int CANT_HOR;

enum Direccion {
    ARRIBA, ABAJO, DERECHA, IZQUIERDA, AMBAS
};

void generate_adjacency(Set* vertices_adyacencia[CANT_VERT * CANT_HOR]);

#endif

