#ifndef TEST_H
#define TEST_H

#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <stdbool.h>

#include "../algorithms/algorithm.h"
#include "../algorithms/markov.h"
#include "../core/tetromino.h"
#include "../stats/analysis.h"
#include "../utils/ensemble.h"
#include "../utils/utilities.h"

#define TIPE_VERSION "5.03"
#define NB_ALGORITHMS 7
#define MAX_RUN 1000000

void run_application_menu();
int run_single_game();

int run_single_game_loop(Game* g, int nb_algorithm, int depth);


void execute_algorithm(Game* g, Piece* p, int n, int depth);

#endif

