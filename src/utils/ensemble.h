#ifndef ENSEMBLE_H
#define ENSEMBLE_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../core/tetromino.h"

//typedef struct Ensemble Ensemble;

typedef struct Ensemble {
    bool values[NUM_TETROMINO_TYPES];
} Ensemble;

Ensemble ensemble_init();

Ensemble ensemble_add(Ensemble e, int k);

Ensemble ensemble_union(Ensemble e1, Ensemble e2);

Ensemble ensemble_intersection(Ensemble e1, Ensemble e2);

bool ensemble_find(Ensemble e, int k);

void ensemble_display(Ensemble e);

#endif