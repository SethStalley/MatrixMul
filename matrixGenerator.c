#include "matrixGenerator.h"

FILE* openFile(char *name);
int runningDir(char *path, int size);
void generateMatrix(FILE *file, int, int);

void generateMatrices(int numRows, int numColumns, int numColumns2) {
    FILE *fileA, *fileB;

    //open file output stream
    fileA = openFile(FILE_A);
    fileB = openFile(FILE_B);

    //set random seed based on time
    srand(time(NULL));

    //file files with randomly generated matrices
    generateMatrix(fileA, numRows, numColumns);
    generateMatrix(fileB, numColumns, numColumns2);

    //close our files
    fclose(fileA);
    fclose(fileB);
}

void generateMatrix(FILE *file, int rows, int columns) {
    int randNumber;

    //print file header
    fprintf(file,"%d %d\n", rows,columns);

    for(int i=0; i<rows; i++) {
        for(int j=0; j<columns; j++) {
            randNumber = (rand() % 200 - 100);
            fprintf(file,"%d ",randNumber);
        }
        fprintf(file,"\n");
    }

}

FILE* openFile(char *name) {
    FILE *pFile;
    char path[1024];
    int success;

    success = runningDir(path, sizeof(path));   
    if(success) {
        strcat(path, "/data/");
        strcat(path, name);
        pFile = fopen(path, "w");
        return pFile;
    } 

    return 0;
}

int runningDir(char *path, int size) {
    if (getcwd(path, size) != NULL)
        return 1;
    perror("getcwd() error");
    return 0;
}
