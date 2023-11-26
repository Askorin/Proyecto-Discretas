#include "../inc/linealize.h"
#include <stdio.h>
#include <stdlib.h>

int tuple_to_int(int a, int b, int n) {
    return a * n + b;
}

int* int_to_tuple(int c, int n) {
    int* retval = malloc(sizeof(int) * 2);

    retval[0] = c / n;
    retval[1] = c % n; 

    return retval;
}
