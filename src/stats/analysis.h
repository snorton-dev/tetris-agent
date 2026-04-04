#ifndef ANALYSIS_H
#define ANALYSIS_H

#include <stdlib.h>
#include <stdbool.h>
#include <math.h>

#include "../algorithms/algorithm.h"
#include "../algorithms/markov.h"
#include "../cli/driver.h"
#include "../core/tetromino.h"
#include "../utils/utilities.h"

#define MAX_TRIAL 100
#define AVERAGE_RUN 1000

typedef struct Report Report;


void run_analysis();

#endif