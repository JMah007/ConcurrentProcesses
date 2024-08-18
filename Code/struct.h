#ifndef STRUCT_H
#define STRUCT_H

struct threadData 
{
	struct 
    {
	int threadOne[4];
    int threadTwo[4];
    int threadThree[4];
    int threadFour[4];
	}regions;

    int numFinishedThreads;
	int counter; 
    int delay;
    int Sol[9][9];
    int Row[9];
    int Col[9];
    int Sub[9];
}; 

#endif 