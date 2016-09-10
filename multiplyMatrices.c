#include "multiplyMatrices.h"

int **researveMemoryForMatrix(int **matrix, int n, int m);
void freeMatrix(int **matrix, int rows);

//Loads matrix from file into a 2D array, array must be freed after use
int **loadMatrix(int **ptr_Matrix, char *name, int *rows) {
    FILE *matrixFile;
    int m, n;

    //open file for reading
    matrixFile = openFile(name, "r");

    //read matrices size
    fscanf(matrixFile, "%d %d\n",&m,&n);
    ptr_Matrix = researveMemoryForMatrix(ptr_Matrix, m,n);

    //fill out matrix
    for(int i=0; i<m; i++) {
        for(int j=0; j<n ; j++) {
            fscanf(matrixFile, "%d", &ptr_Matrix[i][j] );
        }
    }

    //close file
    fclose(matrixFile);
    *rows = m;
    return ptr_Matrix;
}

void singleProcessMul() {
    int **matrixA = NULL, **matrixB = NULL;
    int rowsA, rowsB;

    //Fills our matrixA and matrixB pointers from FILE_A & FILE_B
    matrixA = loadMatrix(matrixA, FILE_A, &rowsA);
    matrixB = loadMatrix(matrixB, FILE_B, &rowsB);

    //free our memory
    freeMatrix(matrixA, rowsA);
    freeMatrix(matrixB, rowsB);
}

//reserver memory for a int matrix size N * M
int **researveMemoryForMatrix(int **matrix, int m, int n){
    matrix = malloc(sizeof(*matrix) * m);

    for(int i=0; i<m; i++) {
        matrix[i] = malloc(sizeof(*matrix[i]) * n);
    }
    
    return matrix;
}

void freeMatrix(int **matrix, int rows) {
    if(matrix) {
        for(int i=0; i < rows; i++)
            free(matrix[i]);
            
        free(matrix);
    }
}

