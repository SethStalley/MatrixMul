#ifndef __MULTIPLY_MATRICES_H
#define __MULTIPLY_MATRICES_H

#include <stdlib.h>
#include <time.h>
#include <sys/wait.h>
#include <sys/mman.h>
#include "fileManager.h"

struct timespec start, finish;
double elapsed;


void singleProcessMul();
void multiProcessMul();

#endif