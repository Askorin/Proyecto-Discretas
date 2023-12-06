#ifndef PATH_FINDING_H
#define PATH_FINDING_H
#include "set.h"

extern const int CANT_VERT;
extern const int CANT_HOR;
extern const int CANT_TOTAL;

void dijkstra(int, Set* ady[CANT_TOTAL], int padre[CANT_TOTAL]);

void get_path(int input_len, int input[input_len], Set* ady[CANT_TOTAL]);

int* generate_path(int source, int destiny, int padre[CANT_TOTAL], int* path_len);

#endif
