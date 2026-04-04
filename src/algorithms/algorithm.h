#ifndef ALGORITHM_H
#define ALGORITHM_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../core/tetris.h"
#include "../core/tetromino.h"
#include "../core/evaluation.h"

Piece* sanitize_piece(Game* g, Piece* p1, Piece* p2);

Piece* algorithm_01(Game* g, Piece* p);

Piece* algorithm_02(Game* g, Piece* p);

Piece* algorithm_03(Game* g, Piece* p);

Piece* algorithm_04(Game* g, Piece* p);

Piece* algorithm_05(Game* g, Piece* p);



#endif