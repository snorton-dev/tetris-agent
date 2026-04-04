#include "driver.h"


void execute_algorithm(Game* g, Piece* p, int n, int depth){
    Piece* result = NULL;

    switch (n) {
        case 1:
            result = algorithm_01(g, p);
            break;
        case 2:
            result = algorithm_02(g, p);
            break;
        case 3:
            result = algorithm_03(g, p);
            break;
        case 4:
            result = algorithm_04(g, p);
            break;
        case 5:
            result = algorithm_05(g, p);
            break;
        case 6:
            result = algorithm_06(g, p, depth);
            break;
        case 7:
            result = algorithm_07(g, p, depth);
            break;
        default:
            printf("\n\tNuméro d'algorithme invalide : %d\n", n);
            change_game_over_value(g, true);
            return;
    }

    
    if (result == NULL) {
        printf("\n\tL'algorithme %d n'a pas pu placer la pièce.\n", n);
        change_game_over_value(g, true);
    } else {
        place_piece_on_board(g, result, true);
    }
    free(result);
}




// ==== 1. Fonctions principales de test


int run_single_game_loop(Game* g, int nb_algorithm, int depth){

    for (int k=0; k<MAX_RUN; k++){
        //display_set(g);

        update_game(g);
        if(game_is_over(g)){
            return k;
        }

        Piece* p = next_piece(g);
        piece_display(p);
        execute_algorithm(g, p, nb_algorithm, depth);
        piece_destroy(p);
        
        
        game_display(g, 1, 0);
    }   

    return MAX_RUN;
}

int run_single_game(){
    Game* g = game_init();

    int depth = 0;
    int nb_algorithm =  read_int_in_range("Algorithm number (1-7): ", 1, NB_ALGORITHMS);
    if (nb_algorithm > 5){
        depth =  read_int_in_range("Depth of thinking : ", 0, NB_ALGORITHMS);
    }
    system("clear");

    int nb_run = run_single_game_loop(g, nb_algorithm, depth);

    game_display(g, 1, 1);
    printf("\n\tGame ended on iteration %d.\n", nb_run);

    game_destroy(g);
    
    return 0;
    
}

void display_header(){
    printf("TIPE INTERFACE v%s \n\n", TIPE_VERSION);
}


void run_application_menu(){
    system("clear");
    display_header();
    printf("Application mode : \n 1. Testing \n 2. Analysis\n\n");
    int mode = read_int_in_range("Preferred mode (1-2): ", 1, 2);
    
   
    
    switch (mode) {
        case 1:
            run_single_game();
            break;
        case 2:
            run_analysis();
            break;
        default:
            printf("\n\tInvalid mode : %d\n", mode);
    }
    return;
}
