#include "../inc/set.h"
#include <stdio.h>
#include <stdbool.h>
#include <stdlib.h>
#include <string.h>

bool is_empty(Set* set) {
    return !set->len;
}

Set* init_set() {
    Set* set = malloc(sizeof(Set));
    set->len = 0;
    set->elementos = malloc(sizeof(int));
    return set;
}

void add_to_set(Set* set, int sujeto) {
    if (in_set(set, sujeto)) return;

    ++set->len;
    set->elementos = realloc(set->elementos, sizeof(int) * set->len);
    set->elementos[set->len - 1] = sujeto;
}

void remove_from_set(Set* set, int sujeto) {
    for (int i = 0; i < set->len; ++i) {
        if (set->elementos[i] == sujeto) {
            memmove(set->elementos + i, set->elementos + i + 1, sizeof(int) * (set->len - i - 1));
            --set->len;
            set->elementos = realloc(set->elementos, sizeof(int) * set->len);
            return;
        }
    }
}

void print_set(Set* set) {
    printf("len: %d\n", set->len);
    printf("{ ");
    for (int i = 0; i < set->len; ++i) {
        if (i == set->len - 1) {
            printf("%d", set->elementos[i]);
        } else {
            printf("%d, ", set->elementos[i]);
        }
    }
    printf(" }\n");
}

bool in_set(Set* set, int sujeto) {
    for (int i = 0; i < set->len; ++i) {
        if (set->elementos[i] == sujeto) {
            return true;
        }
    }
    return false;
}

void free_set(Set* set) {
    free(set->elementos);
    free(set);
}

