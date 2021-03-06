#include "multiplyMatrices.h"

int **researveMemoryForMatrix(int **matrix, int n, int m);
void freeMatrix(int **matrix, int rows);
void printMatrix(int **matrix, int rows, int columns);
void writeMatrixToFile(int **matrix, int rows, int columns);
int **researveGlobalMemoryForMatrix(int **matrix, int m, int n);

int **global_matrix;

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

    //time the process
    clock_gettime(CLOCK_MONOTONIC, &start);

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

    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    double time_spent = elapsed;
    printf("Single Process Mul Time in Sec: %f\n", time_spent);

    writeMatrixToFile(matrixC, rowsA, columnsB);

    //free our memory
    freeMatrix(matrixA, rowsA);
    freeMatrix(matrixB, rowsB);
    freeMatrix(matrixC, rowsA);
}

void multiProcessMul() {
    int **matrixA = NULL, **matrixB = NULL, **matrixC;
    int rowsA, columnsA, rowsB, columnsB;
    pid_t pid;

    //Fills our matrixA and matrixB pointers from FILE_A & FILE_B
    matrixA = loadMatrix(matrixA, FILE_A, &rowsA, &columnsA);
    matrixB = loadMatrix(matrixB, FILE_B, &rowsB, &columnsB);

    //reserved a global shared memory space for matrix C
    matrixC = researveGlobalMemoryForMatrix(global_matrix, rowsA, columnsB);

    //time the process
    clock_gettime(CLOCK_MONOTONIC, &start);

    //multiply
    for (int i=0; i< rowsA; i++) {
        //fork our process
        if (pid > 0)
            pid = fork();
        
        //child process runs following
        if(pid == 0) {
            for (int j=0; j < columnsB; j++) {
                int cellValue = 0;
                for (int z=0; z < rowsB; z++) {
                    cellValue += matrixA[i][z] * matrixB[z][j];
                }
                matrixC[i][j] = cellValue;

                //child is done, free memory and kill it
                freeMatrix(matrixA, rowsA);
                freeMatrix(matrixB, rowsB);
                exit(0); 
            }
        }
    }

    //parent wait for child processes to end
    int status;
    waitpid(-1,&status,WNOHANG);

    clock_gettime(CLOCK_MONOTONIC, &finish);
    elapsed = (finish.tv_sec - start.tv_sec);
    elapsed += (finish.tv_nsec - start.tv_nsec) / 1000000000.0;

    double time_spent = elapsed;
    printf("Multiple Process Mul Time in Sec: %f\n", time_spent);

    writeMatrixToFile(matrixC, rowsA, columnsB);

    //free our memory
    freeMatrix(matrixA, rowsA);
    freeMatrix(matrixB, rowsB);
}

//reserver memory for a int matrix size N * M
int **researveGlobalMemoryForMatrix(int **matrix, int m, int n){

    matrix = mmap(NULL, sizeof(*matrix) * m, PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);

    for(int i=0; i<m; i++) {
        matrix[i] = mmap(NULL, sizeof(*matrix[i]) * n, PROT_READ | PROT_WRITE, 
                    MAP_SHARED | MAP_ANONYMOUS, -1, 0);
    }
    
    return matrix;
}

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

void writeMatrixToFile(int **matrix, int rows, int columns) {
    FILE *file;
    //open file for writting
    file = openFile(FILE_C, "w");

    //print file header
    fprintf(file,"%d %d\n", rows,columns);

    for(int i=0; i<rows; i++) {
        for(int j=0; j<columns; j++) {
            fprintf(file,"%d ",matrix[i][j]);
        }
        fprintf(file,"\n");
    }

    fclose(file);
}

