#ifndef UTILITIES_H
#define UTILITIES_H

#include <stdio.h>
#include <math.h>

#define PBWIDTH 20
#define FULL_BLOCK "█"
#define PART_BLOCK "▒"

#define RESET   "\x1b[0m"
#define BOLD    "\x1b[1m"
#define RED     "\x1b[31m"
#define GREEN   "\x1b[32m"
#define YELLOW  "\x1b[33m"


int read_int_in_range(const char* prompt, int min, int max);

void print_error(const char *msg);

int maximum(int a, int b);
int minimum(int a, int b);

void print_array(int* t, int k);
int* create_array(int n);
int sum_array(int* t, int n);
void swap_array(int* t, int i, int j);
int* random_array(int n);
bool isInArray(int* t, int size, int k, int min, int max);
void shuffle_array(int arr[], int n);

void print_progressbar(int actual, int max);

#endif