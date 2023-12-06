#ifndef PATH_FINDING_H
#define PATH_FINDING_H
#include "../inc/set.h"

extern const int CANT_VERT;
extern const int CANT_HOR;
extern const int CANT_TOTAL;

void dijkstra(int, int, Set* ady[CANT_TOTAL]);

void get_path(int, int, int padre[CANT_TOTAL]);

#endif
