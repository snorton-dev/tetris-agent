#include "evaluation.h"


// ==== 1. Fonctions cout ====

int eval_aggregate_height(Game* g) {
    int sum = 0;
    for (int col = 0; col < BOARD_WIDTH; col++) {
        for (int row = 0; row < BOARD_HEIGHT_SAFE; row++) {
            if (!board_cell_is_empty(g, row, col)) {
                sum += (BOARD_HEIGHT_SAFE - row); 
                break;
            }
        }
    }
    return sum;
}

int eval_max_height(Game* g){
    int highestColumn = 0;

    for (int i=0; i<BOARD_HEIGHT_SAFE; i++){
        for (int j=0; j<BOARD_WIDTH; j++){
            if (!board_cell_is_empty(g, i, j)){
                highestColumn = i;
            }
        }
    }

    return highestColumn;
}

int eval_holes(Game* g){

    int* isBuried = create_array(BOARD_WIDTH);
    int* holes = create_array(BOARD_WIDTH);

    for (int i=(BOARD_HEIGHT_SAFE-1); i>=0; i--){
        for (int j=0; j<BOARD_WIDTH; j++){
        
            if (!board_cell_is_empty(g, i, j)){
                if(isBuried[j] == 0){
                    isBuried[j] = 1;
                }
            } else {
                if (isBuried[j] == 1){
                    holes[j] +=1;
                }
            }

        }
    }
    int sum = sum_array(holes, BOARD_WIDTH);
    free(isBuried);
    free(holes);
    return sum;
}

int eval_landing_height(Piece* p) {
    int min_bottom = BOARD_HEIGHT;
    for (int i = 0; i < PIECE_MATRIX_SIDE; i++) {
        for (int j = 0; j < PIECE_MATRIX_SIDE; j++) {
            if (!piece_cell_is_empty(p, i, j)) {
                int cell_row = piece_x(p) + i;
                if (cell_row < min_bottom) {
                    min_bottom = cell_row;
                }
            }
        }
    }
    return min_bottom;
}

int eval_row_transitions(Game* g){
    int local_total = 0;
    int total = 0;
    for (int i=0 ; i<BOARD_HEIGHT_SAFE ; i++){
        local_total = 0;
        for (int j=0; j<BOARD_WIDTH -1; j++){
            if (board_cell_is_empty(g, i, j) != board_cell_is_empty(g, i+1, j)){
                local_total +=1;
            }
        }
        total += local_total;
    }
    return total;
}

int eval_column_transitions(Game* g){
    int local_total = 0;
    int total = 0;
    for (int j=0 ; j<BOARD_WIDTH ; j++){
        local_total = 0;
        for (int i=0; i<BOARD_HEIGHT_SAFE; i++){
            if (board_cell_is_empty(g, i, j) != board_cell_is_empty(g, i, j+1)){
                local_total +=1;
            }
        }
        total += local_total;
    }
    return total;
    
}

int eval_eroded_cells(Game* g, Piece* p){
    int cleared_lines = 0;
    int filled_cells = 0;

    int local_line = 0;
    int local_filled = 0;

    for (int i=0; i<BOARD_HEIGHT_SAFE ; i++){
        for (int j=0; j<BOARD_WIDTH ; j++){
            if (!board_cell_is_empty(g, i, j)){
                local_line += 1;
            }
            if (board_cell_is_empty(g, i, j) && !piece_cell_is_empty(p, i - piece_x(p), j -piece_y(p))){
                local_filled += 1;
            }
        }
        if (local_line == BOARD_WIDTH-1){
            cleared_lines +=1;
            filled_cells += local_filled;
        }
        local_line = 0;
        local_filled = 0;
    }
    return cleared_lines * filled_cells;
}

int eval_cumulative_wells(Game* g){
    int well_number = 0;
    int local_number = 0;
    for (int j=0; j<BOARD_WIDTH; j++){
        for (int i=0; i<BOARD_HEIGHT_SAFE; i++){
            bool lc;
            if (j==0){
                lc = true;
            } else {
                lc = !board_cell_is_empty(g, i, j-1);
            }
            bool rc;
            if (j==BOARD_WIDTH-1){
                rc = true;
            } else {
                rc = !board_cell_is_empty(g, i, j+1);
            }

            if (board_cell_is_empty(g,i,j) && lc && rc){
                local_number +=1;
            }
        }
        if (local_number > PIECE_MATRIX_SIDE){
            well_number +=1;
        }
        local_number = 0;
    }
    return well_number;
}


int evaluate_position_basic(Game* game, Piece* p){
    if (detect_game_over(game)){
        return 10000;
    } else {
        int e0 = eval_landing_height(p);
        return 1000 - e0;
    }
}


int evaluate_position_intermediate(Game* g, Piece* p){
    if (detect_game_over(g)){
        return 10000;
    } else {
        int e0 = eval_max_height(g);
        int e1 = eval_holes(g);
        int e5 = eval_landing_height(p);
        int eval = 10000 - e0*e1 - e5;
        return eval;
    }
}

int evaluate_position_advanced(Game* g, Piece* p){
    if (detect_game_over(g)){
        return 0;
    } else {
        int e1 = eval_holes(g);
        int e2 = eval_cumulative_wells(g);
        int e3 = eval_row_transitions(g);
        int e4 = eval_column_transitions(g);
        int e5 = eval_landing_height(p);
        int e6 = eval_eroded_cells(g, p);
        int eval = 10000 - 4*e1 - e2 - e3 - e4 - e5 + e6;
        return eval;
    }
}





