#include "analysis.h"

struct Report {
    int piece_placed;
    int score;
};

float calculate_average(float* table, int n){
    float sum = 0;
    for (int i=0; i<n; i++){
        sum += table[i];
    }
    float average = (float)sum / n;
    return average;
}

float calculate_variance(float* table, int n, float average){
    float sum = 0;
    for (int i=0; i<n; i++){
        float val = (table[i] - average);
        sum += val*val;
    }
    return sum / (float)n;
}

float calculate_standard_deviation(float variance){
    return sqrtf(variance);
}


Report run_single_analysis(int nb_algorithm, int depth){
    Game* game = game_init();
    Report report = {0, 0};

    for (int k=0; k<MAX_RUN; k++){
        update_game(game);
        if(game_is_over(game)){
            report.piece_placed = k;
            report.score = game_score(game);
            game_destroy(game);
            return report;
        } else {
            Piece* piece = next_piece(game);
            execute_algorithm(game, piece, nb_algorithm, depth);
            piece_destroy(piece);
            print_progressbar(k, AVERAGE_RUN);
        }
    }   
    report.score = game_score(game);
    game_destroy(game);
    return report;
}

void analyse_results(float* array, int n){
    float average = calculate_average(array, n);
    float variance = calculate_variance(array, n, average);
    float standard_deviation = calculate_standard_deviation(variance);

    printf("Average : %.2f\n", average);
    printf("Variance : %.2f\n", variance);
    printf("Standard deviation : %.2f\n", standard_deviation);
}

void run_analysis(){

    int depth = 0;
    int nb_algorithm =  read_int_in_range("Algorithm number (1-7): ", 1, NB_ALGORITHMS);
    if (nb_algorithm > 5){
        printf("WARNING: This type of algorithms may play for an indeterminate amount of time.\n");
        depth =  read_int_in_range("Depth of thinking : ", 0, NB_ALGORITHMS);
    }
    int nb_trial = read_int_in_range("Number of trials : ", 1, MAX_TRIAL-1);
    system("clear");
    float piece_placed_array[MAX_TRIAL];
    float score_array[MAX_TRIAL];

    printf("Begining analysis of <Algorithm %d> on %d attempt.\n", nb_algorithm, nb_trial);
    for (int i=0; i<nb_trial; i++){
        printf("\rStarting trial %d.                       \n", i+1);
        Report report = run_single_analysis(nb_algorithm, depth);
        piece_placed_array[i] = report.piece_placed;
        score_array[i] = report.score;
    }
    printf("\rAnalysis completed.                           \n");    
    
    printf("\nPIECE PLACED :\n");
    analyse_results(piece_placed_array, nb_trial);
    printf("\nSCORE :\n");
    analyse_results(score_array, nb_trial);
}