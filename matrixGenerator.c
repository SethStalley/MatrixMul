#include "matrixGenerator.h"
#include "fileManager.h"


int runningDir(char *path, int size);
void generateMatrix(FILE *file, int, int);

void generateMatrices(int numRows, int numColumns, int numColumns2) {
    FILE *fileA, *fileB;

    //open file output stream
    fileA = openFile(FILE_A, "w");
    fileB = openFile(FILE_B, "w");

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

