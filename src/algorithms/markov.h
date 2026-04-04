#ifndef MARKOV_H
#define MARKOV_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "algorithm.h"
#include "../utils/ensemble.h"
#include "../core/tetris.h"
#include "../core/tetromino.h"
#include "../core/evaluation.h"



Piece* algorithm_06(Game* g, Piece* p, int depth);


Piece* algorithm_07(Game* g, Piece* p, int depth);



#endif
