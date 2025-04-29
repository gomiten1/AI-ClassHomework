#include <stdio.h>
#include <stdlib.h>
#include <math.h>

// Function to allocate memory for a states x states matrix
double** allocateMatrix(int states) {
    double **matrix = (double**)malloc(states * sizeof(double *));
    if (matrix == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    for (int i = 0; i < states; i++) {
        matrix[i] = (double*)malloc(states * sizeof(double));
        if (matrix[i] == NULL) {
            fprintf(stderr, "Memory allocation failed\n");
            exit(EXIT_FAILURE);
        }
    }
    return matrix;
}

// Function to initialize the matrix with 
// gambler's problem
// probability of winning = 0.49
// probability of losing = 0.51
void initializeMatrix(double **matrix, int states){
    for (int i = 0; i < states; i++){
        for (int j = 0; j < states; j++){
            if (i == 0 && j == 0){
                matrix[i][j] = 1;
            } else if (i == states - 1 && j == states - 1){
                matrix[i][j] = 1;
            } else if (i == j-1 && i != 0){
                matrix[i][j] = 0.49;
            } else if (i == j + 1 && i != states - 1){
                matrix[i][j] = 0.51;
            } else {
                matrix[i][j] = 0;
            }
        }
    }
}

// Function to print matrix
void printMatrix(double **matrix, int states){
    for (int i = 0; i < states; i++){
        for (int j = 0; j < states; j++){
            printf("%lf ", matrix[i][j]);
        }
        printf("\n");
    }
}

// Function to free the allocated memory
void freeMatrix(double **matrix, int states) {
    for (int i = 0; i < states; i++) {
        free(matrix[i]);
    }
    free(matrix);
}

// Function to allocate the vector
double* allocateVector(int states) {
    double *vector = (double*)malloc(states * sizeof(double));
    if (vector == NULL) {
        fprintf(stderr, "Memory allocation failed\n");
        exit(EXIT_FAILURE);
    }
    return vector;
}

// Functions to initialize the vector
// the starting state is either 10 or 100
void initializeVectorAt10(double *vector, int states){
    for (int i = 0; i < states; i++){
        if (i == 10){
            vector[i] = 1;
        } else {
            vector[i] = 0;
        }
    }
}

void initializeVectorAt100(double *vector, int states){
    for (int i = 0; i < states; i++){
        if (i == 100){
            vector[i] = 1;
        } else {
            vector[i] = 0;
        }
    }
}

// Function to calculate the steady state probabilities
// it iterates until the difference between the current and previous state is less than 0.0001
// meanig, the matrix has converged
// therefore a steady state has been reached
void calculateSteadyState(double **matrix, double *vector, int states, int counter) {
    double *prev_vector = allocateVector(states);

    for(int iter = 0; iter < counter; iter++) {
        for (int i = 0; i < states; i++) {
            prev_vector[i] = vector[i];
        }
        for (int i = 0; i < states; i++) {
            vector[i] = 0;
            for (int j = 0; j < states; j++) {
                vector[i] += matrix[i][j] * prev_vector[j];
            }
        }
        
    }

    double sum = 0;
    for (int i = 0; i < states; i++) {
        sum += vector[i];
    }
    for (int i = 0; i < states; i++) {
        vector[i] /= sum;
    }
    free(prev_vector);
}

// Function to print vector
void printVector(double *vector, int states) {
    for (int i = 0; i < states; i++) {
        printf("%lf ", vector[i]);
    }
    printf("\n");
}







int main(){
    // Declare variables
    int states;
    double **matrix;
    double *vector;
    int counter = 10000; 

    // Number of states is read from the user (at least 1k)
    printf("Enter the number of states: ");
    scanf("%d", &states);
    if (states < 1000){
        fprintf(stderr, "Number of states must be at least 1000\n");
        exit(EXIT_FAILURE);
    }

    // Allocate memory for the transition matrix
    matrix = allocateMatrix(states);
    vector = allocateVector(states);
    // Initialize the matrix and vector
    initializeMatrix(matrix, states);
    initializeVectorAt10(vector, states);
    printf("Initial vector:\n");
    printVector(vector, states);
    // Print the matrix
    printf("Transition matrix:\n");
    printMatrix(matrix, states);
    // Calculate the steady state probabilities
    calculateSteadyState(matrix, vector, states, counter);
    // Print the steady state probabilities
    printf("Steady state probabilities:\n");
    printVector(vector, states);
    // Free the allocated memory
    freeMatrix(matrix, states);
    free(vector);
    return 0;

}
