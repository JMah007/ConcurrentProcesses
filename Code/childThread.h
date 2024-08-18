#ifndef CHILDTHREAD_H
#define CHILDTHREAD_H

#include "struct.h"

void* threadOneFunc(void* arg);
void* threadTwoFunc(void* arg);
void* threadThreeFunc(void* arg);
void* threadFourFunc(void* arg);

void validifySubs(struct threadData* pdata, int startRow, int endRow, int startCol, int endCol, int subIdx);

#endif 