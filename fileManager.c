#include "fileManager.h"

int runningDir(char *path, int size);

FILE* openFile(char *name, char *mode) {
    FILE *pFile;
    char path[1024];
    int success;

    success = runningDir(path, sizeof(path));   
    if(success) {
        strcat(path, "/data/");
        strcat(path, name);
        pFile = fopen(path, mode);
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