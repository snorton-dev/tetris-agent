#include "tetris.h"

#define CELL_EMPTY  0
#define CELL_LOCKED 1
#define CELL_GHOST  2


struct PieceBag {
    int sequence[NUM_TETROMINO_TYPES];
    int next_index;
};

struct Game {
    int board[BOARD_HEIGHT][BOARD_WIDTH];
    PieceBag bag;
    int score; 
    bool game_over;
    
};


// ==== 0. Gestion  des groupes de pièces ====

void bag_shuffle(PieceBag* bag) {
    if (!bag) return;
    for (int i = 0; i < NUM_TETROMINO_TYPES; i++) {
        bag->sequence[i] = i;
    }

    shuffle_array(bag->sequence, NUM_TETROMINO_TYPES);
    bag->next_index = 0;
}

PieceBag bag_init() {
    PieceBag bag;
    bag_shuffle(&bag);  
    return bag;
}

int get_bag_index(Game* game){
    return game->bag.next_index;
}

int* get_bag_sequence(Game* game){
    return game->bag.sequence;
}

void display_bag(Game* game){
    PieceBag* bag = &game->bag;
    printf("Piece bag :\n");
    printf("Index : %d\n", bag->next_index);
    for (int i=(bag->next_index); i<NUM_TETROMINO_TYPES; i++){
        Piece* p = piece_create(bag->sequence[i], 0, 0, 0);
        piece_display(p);
        free(p);
    }
    return;
}

Piece* next_piece(Game* game){
    PieceBag *bag = &game->bag;
    if (bag->next_index == NUM_TETROMINO_TYPES){
        bag_shuffle(bag);
    }

    int type = bag->sequence[bag->next_index];
    bag->next_index +=1;
    return piece_create(type, 0, 0, 0);
}


// ==== 1. Plateau de jeu ====

Game* game_init(){
    Game* game= malloc(sizeof(Game));
    if (!game) return NULL;

    for (int i=0; i<BOARD_HEIGHT; i++){
        for(int j=0; j<BOARD_WIDTH; j++){
            game->board[i][j] = 0;
        }
    }

    game->bag = bag_init();
    game->score = 0;
    game->game_over = false;

    return game;
}

void game_destroy(Game* game){
    if (!game) return;
    free(game);
}

void game_display(Game* game, bool withScore, bool withCoordinates) {

    printf("\n\n\n\n");

    for (int i = BOARD_HEIGHT_SAFE-1; i >=0; i--) {
        printf("     ");
        if(withCoordinates){
                printf("%2d ", i);
            }
        for (int j = 0; j < BOARD_WIDTH; j++) {

            

            if(!game->game_over){
                if (game->board[i][j] == 0) {
                    printf(". ");
                }  else if (game->board[i][j] == 1){
                    printf("■ ");
                } else if (game->board[i][j] == 2) {
                    printf("▨ ");
                } else {
                    printf("? ");
                }
            } else {
                if (game->board[i][j] == 0) {
                    printf(RED "□ " RESET);
                } else if (game->board[i][j] == 1) {
                    printf(RED "■ " RESET);
                } else if (game->board[i][j] == 2) {
                    printf(RED "▨ " RESET);
                } else {
                    printf("? ");
                }
            }
        }
        printf("\n");
    }
    if (withCoordinates){
        printf("        ");
        for (int i=0;i<BOARD_WIDTH;i++){
            printf("%d ", i);
        }
        printf("\n");
    }
    if(withScore){
        printf("\n        SCORE : %d\n", game->score);
    }
    printf("\n");
}

Game* game_clone(Game* game) {
    Game* ng = game_init();

    for (int i=0;i<BOARD_HEIGHT;i++){
        for (int j=0;j<BOARD_WIDTH;j++){
            ng->board[i][j] = game->board[i][j];
        }
    }

    ng->score = game->score;
    ng->game_over = game->game_over;
    return ng;
}


// ==== 2. Fonctions utilitiaires ====

int game_score(Game* game){
    return game->score;
}

bool game_is_over(Game* game){
    return game->game_over;
}


void change_game_over_value(Game* game, bool value){
    game->game_over = value;
}

bool board_cell_is_empty(Game* game, int i, int j){
    if (i<0 || i>=BOARD_HEIGHT || j<0 || j>BOARD_WIDTH){
        printf("board_cell_is_empty : Index (%d, %d) out of bound.\n", i, j);
        return true;
    }
    if (game->board[i][j] == 0){
        return true;
    } else {
        return false;
    }
}

bool piece_has_ground_or_support(Game* game, Piece* p){
    int x = piece_x(p);
    int y = piece_y(p);

    for(int i = 0;i<PIECE_MATRIX_SIDE;i++){
        for(int j = 0; j<PIECE_MATRIX_SIDE;j++){
            if (!piece_cell_is_empty(p, i, j)){
                if ((x+i) == 0){                            
                    return true;
                } else if (!board_cell_is_empty(game, x+i-1, y+j)){   
                    return true;
                }
            }
        }
    }
    return false;
}

bool piece_position_is_out_of_bounds(Piece* p){
    int x = piece_x(p);
    int y = piece_y(p);

    for (int i=0;i<PIECE_MATRIX_SIDE;i++){
        for (int j=0;j<PIECE_MATRIX_SIDE;j++){
            if (!piece_cell_is_empty(p, i, j)){
                int c_x = x + i;
                int c_y = y + j;
                if(c_x<0 || c_y<0 || c_x >= BOARD_HEIGHT || c_y >= BOARD_WIDTH){
                    return true;
                }
            }
        }
    }
    return false;
}

bool piece_overlaps_existing_blocks(Game* game, Piece* p){
    int x = piece_x(p);
    int y = piece_y(p);

    for (int i=0;i<PIECE_MATRIX_SIDE;i++){
        for (int j=0;j<PIECE_MATRIX_SIDE;j++){
            if (!piece_cell_is_empty(p, i, j)){
                int c_x = x + i;
                int c_y = y + j;
                if(!board_cell_is_empty(game, c_x, c_y)){
                    return true;
                    
                }
            }
        }
    }
    return false;
}

bool piece_is_completely_buried(Game* game, Piece* p){
    int x = piece_x(p);
    int y = piece_y(p);

    int top_cells = 0;
    int buried_top_cells = 0;

    for (int j=0; j<PIECE_MATRIX_SIDE; j++){
        int max_i = 0;
        for (int i=0; i<PIECE_MATRIX_SIDE; i++){
            if (!piece_cell_is_empty(p, i, j)){
                max_i = i;
            }
        }

        int c_x = x + max_i + 1;
        int c_y = y + j;

        if (!piece_cell_is_empty(p, max_i, j)){
            top_cells +=1;
            if(!board_cell_is_empty(game, c_x, c_y)){
                buried_top_cells +=1;
            }
        }
        max_i = 0;

    }

    return top_cells == buried_top_cells;
}

bool piece_can_be_placed_here(Game* game, Piece* p){
    bool withErrors = false;

    if (piece_position_is_out_of_bounds(p)){
        if (withErrors){
            printf("Out of bound.\n");
        }
        return false;
    } else if (piece_overlaps_existing_blocks(game, p)){
        if (withErrors){
            printf("Collided\n");
        }
        return false;
    } else if (!piece_has_ground_or_support(game, p)){
        if (withErrors){
            printf("No support\n");
        }
        return false;
    } else if (piece_is_completely_buried(game, p)){
        if (withErrors){
            printf("Buried\n");
        }
        return false;
    } else {
        return true;
    }
}



// ==== 3. Administration d'une partie ====


// On regarde si le tampon est utilisé
bool detect_game_over(Game* game){
    for (int i=(BOARD_HEIGHT_SAFE -1);i<BOARD_HEIGHT;i++){
        for (int j=0;j<BOARD_WIDTH;j++){
            if (!board_cell_is_empty(game, i,j)){
                return true;
            }
        }
    }
    return false;
}


bool is_full_row(Game* game, int row){
    int filled_cells = 0;
    for (int j=0; j<BOARD_WIDTH;j++){
        if (!board_cell_is_empty(game, row, j)){
            filled_cells +=1;
        }
        if (game->board[row][j] == CELL_GHOST){
                game->board[row][j] = CELL_LOCKED;
        }
    }
    return (filled_cells == BOARD_WIDTH);
}

void drop_rows_above(Game* game, int row){
    for (int i = row; i < BOARD_HEIGHT_SAFE; i++) {
        for (int j = 0; j< BOARD_WIDTH; j++){
            game->board[i][j] = game->board[i+1][j];
        }
    }
}

static int score_for_lines(int count){
    static const int scores[] = {0, 100, 300, 500, 800};
    if (count <= 4){
        return scores[count];
    } else {
        return 800 + (count - 4) * 200;
    }
}

int collapse_full_lines(Game *game) {
    int lines_cleared = 0;

    for (int row = 0; row < BOARD_HEIGHT_SAFE; ){
        if (is_full_row(game, row)){
            drop_rows_above(game, row);
            lines_cleared++;
        }
        else{
            row++;
        }
    }

    game->score += score_for_lines(lines_cleared);
    return lines_cleared;
}

void update_game(Game* game){
    if (detect_game_over(game)){
        game->game_over = true;
    }
    collapse_full_lines(game);
    
}

void place_piece_on_board(Game* game, Piece* piece,  bool place_as_ghost){
    int x = piece_x(piece);
    int y = piece_y(piece);

    for (int i = 0; i<PIECE_MATRIX_SIDE; i++){
        for (int j = 0; j<PIECE_MATRIX_SIDE; j++){
            if (!piece_cell_is_empty(piece, i, j)){
                if (place_as_ghost){
                    game->board[x+i][y+j] = CELL_GHOST;
                } else {
                    game->board[x+i][y+j] = CELL_LOCKED;
                }
            }
        }
    }

}


Game* simulateGame(Game* game, Piece* piece){
    Game* simulation = game_clone(game);
    if (piece_can_be_placed_here(game, piece)){
        place_piece_on_board(simulation, piece, false);
    }
    update_game(simulation);
    return simulation;
}