#include "ensemble.h"

/*struct Ensemble {
    bool values[NUM_TETROMINO_TYPES];
};*/

Ensemble ensemble_init(){
    Ensemble e;
    for (int i=0; i<NUM_TETROMINO_TYPES; i++){
        e.values[i] = false;
    }
    return e;
}

Ensemble ensemble_add(Ensemble e, int k){
    if (k>=0 && k<NUM_TETROMINO_TYPES){
        e.values[k] = true;
    }
    return e;
}

Ensemble ensemble_union(Ensemble e1, Ensemble e2){
    Ensemble e3 = ensemble_init();
    for (int i=0; i<NUM_TETROMINO_TYPES; i++){
        if (e1.values[i] || e2.values[i]){
            e3.values[i] = true;
        }
    }
    return e3;
}

Ensemble ensemble_intersection(Ensemble e1, Ensemble e2){
    Ensemble e3 = ensemble_init();
    for (int i=0; i<NUM_TETROMINO_TYPES; i++){
        if (e1.values[i] && e2.values[i]){
            e3.values[i] = true;
        }
    }
    return e3;
}

bool ensemble_find(Ensemble e, int k){
    if (k>=0 && k<NUM_TETROMINO_TYPES){
        return e.values[k];
    }
    return false;
}


void ensemble_display(Ensemble e){
    int n = NUM_TETROMINO_TYPES;
    printf("Ensemble:\n");
    printf("[");
    for (int i = 0; i < n; i++) {
        if (e.values[i]){
            printf("%d", i);
        } else {
            printf("_");
        }
        if (i!=(n-1)){
            printf(", ");
        }
    }
    printf("]\n");
}