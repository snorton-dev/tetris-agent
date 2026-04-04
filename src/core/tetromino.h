#ifndef TETROMINO_H
#define TETROMINO_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../utils/utilities.h"

#define PIECE_MATRIX_SIDE   4
#define NUM_TETROMINO_TYPES 7
#define NUM_ROTATIONS       4

typedef struct Piece Piece;

// ==== 1. Tetrominos ====

Piece* piece_create(int type, int rotation, int x, int y);

Piece* piece_copy(Piece* p);

void piece_change_values(Piece* p, int x, int y, int r);

void piece_destroy(Piece* p);

void piece_display(Piece* p);

int piece_x(Piece* p);

int piece_y(Piece* p);

bool piece_cell_is_empty(Piece* p, int i, int j);


#endif
