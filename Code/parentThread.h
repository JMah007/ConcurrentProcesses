#ifndef PARENTTHREAD_H
#define PARENTTHREAD_H

#include "struct.h"

void processFile(int arr[9][9], int rows, int cols, char* pfileName);
void initialiseStruct(struct threadData* pstruct, int delay, int solArr[9][9]);
void printResults(struct threadData* pstruct);

#endif 