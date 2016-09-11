#include <stdlib.h>

#include "matrixGenerator.h"
#include "multiplyMatrices.h"

int convertArgvParamsToInt(char *argv[], int *x, int *y, int *z);

int main(int argc, char *argv[]) {

    if(argc == 4){
        int numColumns, numRows, numColumns2;

        int success = convertArgvParamsToInt(argv,&numRows,&numColumns, &numColumns2);

        if(success) {
            //generate matrices
            generateMatrices(numRows, numColumns, numColumns2);

            //multiply matrices using a single process
            singleProcessMul();

            //finally using multiple processes
            multiProcessMul();
        }else {
            printf("Arguments must be Numbers!\n");
        }
        
    } else {
        printf("Invalid number of arguments!\n"
        "Call program with the number of columns and rows of the matrix\n");
    }

    
    
    return 0;
}
 

int convertArgvParamsToInt(char *argv[], int *x, int *y, int *z) {
    *x = atoi(argv[1]);
    *y = atoi(argv[2]);
    *z = atoi(argv[3]);

    if(*x && *y && *z) {
        return 1;
    }

    return 0;
}