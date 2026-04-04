#include "algorithm.h"

// ==== 0. Fonctions utilitaires ====



Piece* sanitize_piece(Game* g, Piece* p1, Piece* p2){
    if (piece_can_be_placed_here(g, p1)){
        piece_destroy(p2);
        return p1;
    } else {
        piece_destroy(p1);
        p1 = algorithm_03(g, p2);
        piece_destroy(p2);
        return p1;
    }
}

// ==== 1. Algorithme test ====

// On empile les pièces
Piece* algorithm_01(Game* g, Piece* p){
    int rot = 0;
    int row = -5;
    int col = 0;
    piece_change_values(p, row, col, rot);
    
    while (!piece_can_be_placed_here(g, p) && row < BOARD_HEIGHT){
        piece_change_values(p, row, col, rot);
        row+=1;
    }

    if (piece_can_be_placed_here(g, p)){
        Piece* best_piece = piece_copy(p);
        return best_piece;
    } else {
        return NULL;
    }
}

// ==== 2. Algorithme aléatoire ====

Piece* algorithm_02(Game* g, Piece* p){
    int rot = rand() % NUM_ROTATIONS;
    int row = -5;
    int col = rand() % BOARD_WIDTH;
    piece_change_values(p, row, col, rot);
    
    while (!piece_can_be_placed_here(g, p) && row < BOARD_HEIGHT){
        for (int k=0; k<(BOARD_WIDTH*BOARD_HEIGHT);k++){
            col = rand() % BOARD_WIDTH;
            rot = rand() % NUM_ROTATIONS;
            piece_change_values(p, row, col, rot);
            if (piece_can_be_placed_here(g, p)){
                Piece* best_piece = piece_copy(p);
                return best_piece;
            }
        }
        row +=1;
    }
    if (piece_can_be_placed_here(g, p)){
        Piece* best_piece = piece_copy(p);
        return best_piece;
    } else {
        return NULL;
    }
}

// ==== 3. Algorithme glouton simple ====

Piece* algorithm_03(Game* g, Piece* p){

    Piece* best_piece = piece_copy(p);
    int best_evaluation = 10000;

    int r_temp = rand() % NUM_ROTATIONS;
    int row = -5;
    piece_change_values(p, row, -5, r_temp);
    
    while (!piece_can_be_placed_here(g, best_piece) && row < BOARD_HEIGHT){
        for (int col=(-5); col<BOARD_WIDTH + 5; col++){
            for (int rot=0; rot<NUM_ROTATIONS; rot++){
                piece_change_values(p, row, col, rot);
                int evaluation = evaluate_position_basic(g, p);

                if (piece_can_be_placed_here(g, p) && evaluation < best_evaluation){
                    piece_destroy(best_piece);
                    best_piece = piece_copy(p);
                    best_evaluation = evaluation;
                }
            }
        }
            
        row +=1;
    }
    
    if (piece_can_be_placed_here(g, best_piece)){
        return best_piece;
    } else {
        return NULL;
    }
}

// === 4. Algorithme linéaire simple ===

Piece* algorithm_04(Game* g, Piece* p){

    Piece* backup = piece_copy(p);

    int best_evaluation = 0;
    int new_evaluation = 0;
    Piece* best_piece = piece_copy(p);

    for (int row=-5; row<BOARD_WIDTH +5; row++){
        for (int col=-5; col<BOARD_HEIGHT_SAFE+2; col++){
            for (int rot=0; rot<NUM_ROTATIONS; rot++){
                piece_change_values(p, row, col, rot);

                if (piece_can_be_placed_here(g, p)){
                    Game* simulation = simulateGame(g, p);
                    new_evaluation = evaluate_position_intermediate(simulation, p);
                    game_destroy(simulation);

                    if (new_evaluation > best_evaluation){
                        piece_change_values(best_piece, row, col, rot);
                        best_evaluation = new_evaluation;
                    }
                }
            }
        }
    }
    return sanitize_piece(g, best_piece, backup);
}

// === 4. Algorithme linéaire complerowe ===

Piece* algorithm_05(Game* g, Piece* p){

    Piece* backup = piece_copy(p);

    int best_evaluation = 0;
    int new_evaluation = 0;
    Piece* best_piece = piece_copy(p);

    for (int row=-5; row<BOARD_WIDTH +5; row++){
        for (int col=-5; col<BOARD_HEIGHT_SAFE+2; col++){
            for (int rot=0; rot<NUM_ROTATIONS; rot++){
                piece_change_values(p, row, col, rot);

                if (piece_can_be_placed_here(g, p)){
                    Game* simulation = simulateGame(g, p);
                    new_evaluation = evaluate_position_advanced(simulation, p);
                    game_destroy(simulation);

                    if (new_evaluation > best_evaluation){
                        piece_change_values(best_piece, row, col, rot);
                        best_evaluation = new_evaluation;
                    }
                }
            }
        }
    }
    return sanitize_piece(g, best_piece, backup);
}

