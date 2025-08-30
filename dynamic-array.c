// Dynamic arrays in C programming Language...

#include <stdio.h>
#include <stdlib.h>


void dynamic_array_push(int **arr, int *nelements, int num) {
    int *tmp = realloc(*arr, (*nelements + 1) * sizeof(int));
    if (!tmp) {
        perror("realloc failed");
        return; // leave old array untouched
    }
    *arr = tmp; // update caller's pointer
    (*arr)[*nelements] = num;
    (*nelements)++;
}
int main() {
    return 0;
}