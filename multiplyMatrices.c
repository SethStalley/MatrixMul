#include "multiplyMatrices.h"

int **researveMemoryForMatrix(int **matrix, int n, int m);
void freeMatrix(int **matrix, int rows);
void printMatrix(int **matrix, int rows, int columns);

//Loads matrix from file into a 2D array, array must be freed after use
int **loadMatrix(int **ptr_Matrix, char *name, int *rows, int *columns) {
    FILE *matrixFile;

    //open file for reading
    matrixFile = openFile(name, "r");

    //read matrices size
    fscanf(matrixFile, "%d %d\n",rows,columns);
    ptr_Matrix = researveMemoryForMatrix(ptr_Matrix, *rows, *columns);

    //fill out matrix
    for(int i=0; i < *rows; i++) {
        for(int j=0; j < *columns ; j++) {
            fscanf(matrixFile, "%d", &ptr_Matrix[i][j] );
        }
    }

    //close file
    fclose(matrixFile);
    return ptr_Matrix;
}

void singleProcessMul() {
    int **matrixA = NULL, **matrixB = NULL, **matrixC;
    int rowsA, columnsA, rowsB, columnsB;

    //Fills our matrixA and matrixB pointers from FILE_A & FILE_B
    matrixA = loadMatrix(matrixA, FILE_A, &rowsA, &columnsA);
    matrixB = loadMatrix(matrixB, FILE_B, &rowsB, &columnsB);

    //reserver memory for our 'C'' (result) matrix
    matrixC = researveMemoryForMatrix(matrixC, rowsA, columnsB);

    //multiply
    for (int i=0; i< rowsA; i++) {
        for (int j=0; j < columnsB; j++) {
            int cellValue = 0;
            for (int z=0; z < rowsB; z++) {
                cellValue += matrixA[i][z] * matrixB[z][j];
            }
            matrixC[i][j] = cellValue;
        }
    }

    //free our memory
    freeMatrix(matrixA, rowsA);
    freeMatrix(matrixB, rowsB);
    freeMatrix(matrixC, rowsA);
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

void printMatrix(int **matrix, int rows, int columns) {
    for (int i=0; i<rows; i++) {
        for (int j=0; j<columns; j++) {
            printf("%d\t", matrix[i][j]);
        }
        printf("\n");
    }
}

