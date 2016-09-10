#ifndef __FILE_MANGER_H
#define __FILE_MANGER_H

#include <stdio.h>
#include <string.h>
#include <unistd.h>

#define FILE_A "A"
#define FILE_B "B"
#define FILE_C "C"


/*
* *mode is the mode with which to open the file. "w" or "r", for example.
* Opened file must be closed after use.
*/
FILE* openFile(char *name, char *mode);

#endif