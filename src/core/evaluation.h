#ifndef EVALUATION_H
#define EVALUATION_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "../algorithms/algorithm.h"
#include "tetromino.h"
#include "tetris.h"

int eval_max_height(Game* g);

int eval_holes(Game* g);

int eval_landing_height(Piece* p);

int eval_row_transitions(Game* g);

int eval_column_transitions(Game* g);

int eval_eroded_cells(Game* g,Piece* p);

int eval_cumulative_wells(Game* g);

void display_evaluation(Game* g, Piece* p);

int evaluate_position_basic(Game* game, Piece* p);

int evaluate_position_intermediate(Game* g,Piece* p);

int evaluate_position_advanced(Game* g,Piece* p);



#endif
