#include "markov.h"

/*
    Policy is Algorithm 5
    Value is calculated by the standard evaluation
*/


float auxiliary6(Game* g, Piece* previous_piece, int depth, int layer){
    printf("Layer : (%d/%d)\n", layer, depth);
    game_display(g, 0, 0);
    //piece_display(previous_piece);

    if (layer >= depth || detect_game_over(g)){
        int eval = evaluate_position_advanced(g, previous_piece);
        return eval;

    } else {
        float average = 0;

        for (int i=0; i<NUM_TETROMINO_TYPES; i++){
            Piece* tmp = piece_create(i, 0, 0, 0);
            Piece* action = algorithm_05(g, tmp);
            Game* new_board = simulateGame(g, action);
            average += ((float) 1/NUM_TETROMINO_TYPES)*(auxiliary6(new_board, action, depth, layer + 1));
            piece_destroy(tmp);
            piece_destroy(action);
            game_destroy(new_board);
        }
        return average;
    }
}

Piece* algorithm_06(Game* g, Piece* p, int depth){
    Piece* backup = piece_copy(p);

    float best_evaluation = 0;
    float new_evaluation = 0;
    Piece* best_piece = piece_copy(p);

    for (int x=-5; x<BOARD_WIDTH +5; x++){
        for (int y=-5; y<BOARD_HEIGHT_SAFE+2; y++){
            for (int r=0; r<NUM_ROTATIONS; r++){
                piece_change_values(p, x, y, r);

                if (piece_can_be_placed_here(g, p)){
                    Game* simulation = simulateGame(g, p);
                    new_evaluation = auxiliary6(simulation, p, depth, 0);
                    game_destroy(simulation);
                    
                    if (new_evaluation > best_evaluation){
                        piece_change_values(best_piece, x, y, r);
                        best_evaluation = new_evaluation;
                        //printf("Best evaluation : %d\n", best_evaluation);
                    }
                }
            }
        }
    }
    //piece_display(best_piece);

    return sanitize_piece(g, best_piece, backup);
}



Ensemble create_subset(Game* g){
    Ensemble ensemble = ensemble_init();
    int* sequence = get_bag_sequence(g);
    int index = get_bag_index(g);

    for (int i=0; i<index; i++){
        ensemble_add(ensemble, sequence[i]);
    }
    return ensemble;
}


float auxiliary7(Game* g, Piece* previous_piece, int depth, int layer, Ensemble subset){
    //printf("Layer : (%d/%d)\n", layer, depth);
    //game_display(g, 0, 1);
    //piece_display(previous_piece);
    //ensemble_display(subset);

    if (layer >= depth || detect_game_over(g)){
        int eval = evaluate_position_advanced(g, previous_piece);
        return eval;

    } else {
        float average = 0;

        for (int i=0; i<NUM_TETROMINO_TYPES; i++){
            if (layer <= (NUM_TETROMINO_TYPES - get_bag_index(g))){
                if(ensemble_find(subset, i)){
                    int eval = evaluate_position_advanced(g, previous_piece);
                    return eval;
                } else {
                    Ensemble new_subset = ensemble_add(subset, i);
                    Piece* tmp = piece_create(i, 0, 0, 0);
                    Piece* action = algorithm_05(g, tmp);
                    Game* new_board = simulateGame(g, action);
                    average += (1.0/NUM_TETROMINO_TYPES)*(auxiliary7(new_board, action, depth, layer + 1, new_subset));
                    piece_destroy(tmp);
                    piece_destroy(action);
                    game_destroy(new_board);
                }
            } else {
                Piece* tmp = piece_create(i, 0, 0, 0);
                Piece* action = algorithm_05(g, tmp);
                Game* new_board = simulateGame(g, action);
                average += ((float) 1/NUM_TETROMINO_TYPES)*(auxiliary7(new_board, action, depth, layer + 1, subset));
                piece_destroy(tmp);
                piece_destroy(action);
                game_destroy(new_board);
            }
        }
        return average;
    }
}

Piece* algorithm_07(Game* g, Piece* p, int depth){
    Piece* backup = piece_copy(p);

    float best_evaluation = 0;
    float new_evaluation = 0;
    Piece* best_piece = piece_copy(p);

    for (int x=-5; x<BOARD_WIDTH +5; x++){
        for (int y=-5; y<BOARD_HEIGHT_SAFE+2; y++){
            for (int r=0; r<NUM_ROTATIONS; r++){
                piece_change_values(p, x, y, r);

                if (piece_can_be_placed_here(g, p)){
                    Game* simulation = simulateGame(g, p);

                    Ensemble e = create_subset(simulation);

                    new_evaluation = auxiliary7(simulation, p, depth, 0, e);
                    game_destroy(simulation);
                    
                    if (new_evaluation > best_evaluation){
                        piece_change_values(best_piece, x, y, r);
                        best_evaluation = new_evaluation;
                    }
                }
            }
        }
    }
    return sanitize_piece(g, best_piece, backup);
}



