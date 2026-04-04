#include "tetromino.h"

struct Piece {
    int type;       
    int rotation;  
    int x;
    int y;
    bool cells[PIECE_MATRIX_SIDE][PIECE_MATRIX_SIDE];   
};


// ==== 1. Valeurs des pièces ====

// TETROMINO
int PIECES[NUM_TETROMINO_TYPES][NUM_ROTATIONS][PIECE_MATRIX_SIDE][PIECE_MATRIX_SIDE] = {
    // Pièce I
    {
        {
            {0,0,0,0},
            {1,1,1,1},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0}
        },
        {
            {0,0,0,0},
            {1,1,1,1},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,1,0,0}
        }
    },
    // Pièce O
    {
        {
            {0,0,0,0},
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,1,1,0},
            {0,1,1,0},
            {0,0,0,0}
        }
    },
    // Pièce T (violet)
    {
        {
            {0,0,0,0},
            {1,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {1,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,1,0},
            {0,1,0,0},
            {0,0,0,0}
        }
    },
    // Pièce L 
    {
        {
            {0,0,0,0},
            {1,1,1,0},
            {1,0,0,0},
            {0,0,0,0}
        },
        {
            {1,1,0,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        {
            {0,0,1,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,0,0},
            {0,1,1,0},
            {0,0,0,0}
        }
    },
    // Pièce J (bleu foncé)
    {
        {
            {0,0,0,0},
            {1,1,1,0},
            {0,0,1,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {0,1,0,0},
            {1,1,0,0},
            {0,0,0,0}
        },
        {
            {1,0,0,0},
            {1,1,1,0},
            {0,0,0,0},
            {0,0,0,0}
        },
        {
            {0,1,1,0},
            {0,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        }
    },
    // Pièce S (vert clair)
    {
        {
            {0,0,0,0},
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0}
        },
        {
            {1,0,0,0},
            {1,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {0,1,1,0},
            {1,1,0,0},
            {0,0,0,0}
        },
        {
            {1,0,0,0},
            {1,1,0,0},
            {0,1,0,0},
            {0,0,0,0}
        }
    },
    // Pièce Z (rouge)
    {
        {
            {0,0,0,0},
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {1,1,0,0},
            {1,0,0,0},
            {0,0,0,0}
        },
        {
            {0,0,0,0},
            {1,1,0,0},
            {0,1,1,0},
            {0,0,0,0}
        },
        {
            {0,1,0,0},
            {1,1,0,0},
            {1,0,0,0},
            {0,0,0,0}
        }
    }
};

// ==== 2. Définiton des pièces ====

Piece* piece_create(int type, int rotation, int x, int y){
    if (!(type>=0)&&(type<NUM_TETROMINO_TYPES)&&(rotation>=0)&&(rotation<NUM_ROTATIONS)){
        return NULL;
    }  
    Piece* piece = malloc(sizeof(Piece));
    piece->type = type;
    piece->rotation = rotation;
    piece->x = x;
    piece->y = y;

    for (int i = 0; i < PIECE_MATRIX_SIDE; i++){
        for (int j = 0; j < PIECE_MATRIX_SIDE; j++){
            piece->cells[i][j] = PIECES[type][rotation][i][j];
        }
    }

    return piece;
}

Piece* piece_copy(Piece* piece){
    Piece* copy = piece_create(0, 0, 0, 0);
    copy->type = piece->type;
    copy->rotation = piece->rotation;
    copy->x = piece->x;
    copy->y = piece->y;

    for (int i = 0; i < PIECE_MATRIX_SIDE; i++){
        for (int j=0; j<PIECE_MATRIX_SIDE; j++){
            copy->cells[i][j] = piece->cells[i][j];
        }
    }

    return copy;
}

void piece_change_values(Piece* piece, int x, int y, int r){
    int type = piece->type;
    piece->rotation = r;
    piece->x = x;
    piece->y = y;
    for (int i = 0; i < PIECE_MATRIX_SIDE; i++){
        for (int j=0; j<PIECE_MATRIX_SIDE; j++){
            piece->cells[i][j] = PIECES[type][r][i][j];
        }
    }
}

void piece_destroy(Piece* piece){
    free(piece);
}

void piece_display(Piece* piece){
    for (int i=0;i<PIECE_MATRIX_SIDE;i++){
        printf("\t");
        for (int j=0;j<PIECE_MATRIX_SIDE;j++){
            if (piece->cells[i][j] == 0) {
                printf(". ");
            } else if (piece->cells[i][j] == 1) {
                printf("■ ");
            } else {
                printf("? ");
            }
        
        }
        if(i==0) printf("\tType: %d, rotation %d", piece->type, piece->rotation);
        if(i==1) printf("\tx: %2d y:%2d", piece->x, piece->y);
        printf("\n");
    }
}

// ==== 3. Fonctions utilitaires ====

int piece_x(Piece* piece){
    return piece->x;
}

int piece_y(Piece* piece){
    return piece->y;
}

bool piece_cell_is_empty(Piece* piece, int i, int j){
    if (i<0 || j<0 || i>=PIECE_MATRIX_SIDE || j>=PIECE_MATRIX_SIDE){
        return true;
    }
    return !piece->cells[i][j];
}



