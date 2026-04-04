#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

#include "utilities.h"

int read_int_in_range(const char* prompt, int min, int max) {
    char line[64];
    int value;

    while (1) {
        fputs(prompt, stdout);
        fflush(stdout);

        if (!fgets(line, sizeof(line), stdin)) {
            return -1;
        }
        char* endptr;
        value = strtol(line, &endptr, 10);
        if (endptr != line && (*endptr == '\0' || *endptr == '\n')) {
            if (value >= min && value <= max) {
                return value;
            }
        }
        printf("Invalid input. Please enter a number between %d and %d.\n", min, max);
    }
}

int maximum(int a, int b){
    if(a<b){
        return b;
    } else {
        return a;
    }
}

int minimum(int a, int b){
    if(a>b){
        return b;
    } else {
        return a;
    }
}
    
void print_array(int* t, int k) {
    printf("\nINDEX:  ");
    for (int i = 0; i < k; i++) {
        printf("%8d ", i);
    }
    printf("\n");
    printf("VALUES: ");
    for (int i = 0; i < k; i++) {
        printf("%8d ", t[i]);
    }
    printf("\n");
}

int* create_array(int n){
    if (n<=0) return NULL;

    int* t = malloc(n*sizeof(int));
    for (int i=0; i<n; i++){
        t[i] = 0;
    }
    return t;
}

int sum_array(int* t, int n){
    if (n<=0) return 0;
    
    int sum = 0;
    for (int i=0; i<n; i++){
        sum += t[i];
    }
    return sum;
}

void swap_array(int* t, int i, int j){
    int temp = t[i];
    t[i] = t[j];
    t[j] = temp;
}

int* random_array(int n){
    if (n<=0) return NULL;

    int* t = create_array(n);

    for (int i=0; i<n;i++){
        t[i] = i;
    }

    for (int a=0; a<n;a++){     // Melange de Fisher-Yates
        int b = rand()%n;
        swap_array(t, a, b);
    }
    return t;
}

void shuffle_array(int arr[], int n) {
    if (n <= 1) return;

    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        // swap
        int temp   = arr[i];
        arr[i]     = arr[j];
        arr[j]     = temp;
    }
}


void print_progressbar(int actual, int max) {
    
    while (actual > max){
        max = max*10;
    }
    float percentage = ((float) actual) / ((float) max);
    int total_blocks = PBWIDTH;
    int filled_blocks = (int)(percentage * total_blocks);
    int empty_blocks = total_blocks - filled_blocks;

    int percent = (int)(percentage * 100);

    printf("\r ");

    for (int i = 0; i < filled_blocks; i++)
        printf("%s", FULL_BLOCK);

    for (int i = 0; i < empty_blocks; i++)
        printf("%s", PART_BLOCK);

    printf("%3d%%", percent);
    printf("\t%d", actual);
    fflush(stdout);
}

bool isInArray(int* t, int size, int k, int min, int max){
    for (int i = min; i<= minimum(size-1, max); i++){
        if (t[i] == k){
            return true;
        }
    }
    return false;
}

void print_error(const char *msg) {
    printf(RED "ERROR: " RESET "%s\n\n", msg);
}



