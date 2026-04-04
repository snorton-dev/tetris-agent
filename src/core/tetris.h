#ifndef TETRIS_H
#define TETRIS_H

#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "tetromino.h"
#include "../utils/utilities.h"

#define BOARD_HEIGHT 25
#define BOARD_HEIGHT_SAFE 20
#define BOARD_WIDTH 10


typedef struct PieceBag PieceBag;
typedef struct Game Game;

// ==== 0. Gestion  des groupes de pièces ====

void bag_shuffle(PieceBag* bag);

PieceBag bag_init();

int get_bag_index(Game* game);

int* get_bag_sequence(Game* game);

void display_bag(Game* game);

Piece* next_piece(Game* game);

// ==== 1. Plateau de jeu ====

Game* game_init();

void game_display(Game* g, bool withScore, bool withCoordinates);

Game* game_clone(Game* g);

void game_destroy(Game* g);

// ==== 2. Fonctions utilitaires ====

int game_score(Game* g);

bool game_is_over(Game* g);

void change_game_over_value(Game* g, bool value);

bool board_cell_is_empty(Game* g, int i, int j);

bool piece_has_ground_or_support(Game* g, Piece* p);

bool piece_position_is_out_of_bounds(Piece* p);

bool piece_overlaps_existing_blocks(Game* g, Piece* p);

bool piece_is_completely_buried(Game* g, Piece* p);

bool piece_can_be_placed_here(Game* g, Piece* p);


// ==== 3. Administration d'une partie ====

Piece* next_piece(Game* g);

bool detect_game_over(Game* game);

void drop_rows_above(Game* g, int k);

void clean_board(Game* g);

void update_game(Game* g);

void place_piece_on_board(Game* game, Piece* piece,  bool place_as_ghost);



Game* simulateGame(Game* game, Piece* piece);

#endif