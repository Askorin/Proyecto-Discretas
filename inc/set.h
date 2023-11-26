#ifndef SET_H
#define SET_H
#include <stdbool.h>

/* Conjunto de enteros */
typedef struct {
    int len;
    int* elementos;
} Set;

/* Inicializa un conjunto. */
Set* init_set();

/* Revisa si un conjunto tiene elementos. */
bool is_empty(Set*);

/* Añade un número al conjunto. */
void add_to_set(Set*, int);

/* Remueve un número del conjunto. */
void remove_from_set(Set*, int);

/* Imprime los elementos del conjunto. */
void print_set(Set*);

/* Revisa si un elemento en particular está en el conjunto. */
bool in_set(Set*, int);

/* Libera un conjunto */
void free_set(Set*);

#endif
