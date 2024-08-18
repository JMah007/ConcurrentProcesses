#include <stdio.h>
#include "parentThread.h"
#include "struct.h"

/*This function extracts 9x9 grid of digits and stores them in a 2d array*/
void processFile(int arr[9][9], int rows, int cols, char* pfileName)
{
    FILE* fp;
    int i = 0, j = 0;
    int num = 0;

    fp = fopen(pfileName, "r");

   
    if(fp != NULL) /* Check if file exists */
    {
        while(fscanf(fp, "%d", &num) != EOF)
        { 
            if(j == 9) /* checks to see if row is full */
            {
                i++;
                j = 0;
            }
            arr[i][j] = num;
            j++;
        }
        fclose(fp); 
        printf("File read successfully!\n");
    }
    else
    {
        perror("Cannot open file");
    }
   return;
}


/*This function initialises a struct containing shared data that all threads must access*/
void initialiseStruct(struct threadData* pstruct, int delay, int solArr[9][9])
{
    int i;
    int j = 0, k = 0;

    pstruct->regions.threadOne[0] = 0;
    pstruct->regions.threadOne[1] = 2;
    pstruct->regions.threadOne[2] = 0;
    pstruct->regions.threadOne[3] = 8;

    pstruct->regions.threadTwo[0] = 3;
    pstruct->regions.threadTwo[1] = 5;
    pstruct->regions.threadTwo[2] = 0;
    pstruct->regions.threadTwo[3] = 8;

    pstruct->regions.threadThree[0] = 6;
    pstruct->regions.threadThree[1] = 8;
    pstruct->regions.threadThree[2] = 0;
    pstruct->regions.threadThree[3] = 8;

    pstruct->regions.threadFour[0] = 0;
    pstruct->regions.threadFour[1] = 8;
    pstruct->regions.threadFour[2] = 0;
    pstruct->regions.threadFour[3] = 8;

    pstruct->numFinishedThreads = 0;
    pstruct->counter = 0;
    pstruct->delay = delay;

    for(i=0; i<9; i++)
    {
        pstruct->Sub[i] = 0;
        pstruct->Row[i] = 0;
        pstruct->Col[i] = 0;
    }
 
    while(j != 9)  /* keep filling until last row is filled*/
    {
        if(k == 9) /* checks to see if row is full */
        {
            j++;
            k = 0;
        }

        pstruct->Sol[j][k] = solArr[j][k];
        k++;
    }     
}


 /* This function prints results produced by child threads*/
void printResults(struct threadData* pstruct)
{
    int valid;
    int i;

    /* Display thread 1*/
    printf("\nThread ID-1:");
    valid = 1; /* Reset validity to true */

    for(i=0; i<3; i++) /* display what rows are invalid */
    {
        if(pstruct->Row[i] == 0)
        {
            printf(" row %d,", i+1);
            valid = 0;
        }
    }

    for(i=0; i<3; i++) /* display what subgrids are invalid*/
    {
        if(pstruct->Sub[i] == 0)
        {
            printf(" sub-grid %d,", i+1);
            valid = 0;
        }
        
    }

    /* Print whether thread is valid or invalid*/
    if(valid == 1)
    {
        printf(" valid");
    }
    else{
        printf(" is invalid");
    }


    /* Display thread 2*/
    printf("\nThread ID-2:");
    valid = 1;

    for(i=3; i<6; i++) /* display rows that are invalid */
    {
        if(pstruct->Row[i] == 0)
        {
            printf(" row %d,", i+1);
            valid = 0;
        }
    }

    for(i=3; i<6; i++) /* display subgrids that are invalid */
    {
        if(pstruct->Sub[i] == 0){
            printf(" sub-grid %d,", i+1);
            valid = 0;
        }
        
    }

    /* display if thread is valid or invalid */
    if(valid == 1){
        printf(" valid");
    }
    else{
        printf(" is invalid");
    }


    /* Display thread 3*/
    printf("\nThread ID-3:");
    valid = 1;

    for(i=6; i<9; i++) /* display rows that are invalid */
    {
        if(pstruct->Row[i] == 0)
        {
            printf(" row %d,", i+1);
            valid = 0;
        }
    }
    
    for(i=6; i<9; i++) /* display subgrids that are invalid */
    {
        if(pstruct->Sub[i] == 0)
        {
            printf(" sub-grid %d,", i+1);
            valid = 0;
        }
        
    }

    /* display if thread is valid or invalid */
    if(valid == 1)
    {
        printf(" valid");
    }
    else{
        printf(" is invalid");
    }


    /* Display thread 4*/
    printf("\nThread ID-4:");
    valid = 1;

    for(i=0; i<9; i++) /* display columns that are invalid */
    {
        if(pstruct->Col[i] == 0)
        {
            printf(" column %d,", i+1);
            valid = 0;
        }

    }
    
    /* display if thread is valid or invalid */
    if(valid == 1)
    {
        printf(" valid");
    }
    else{
        printf(" is invalid");
    }


    /* Display total counter */
    if(pstruct->counter != 27)
    {
        printf("\n\nThere are in total %d valid rows, columns, and sub-grids, and the solution is invalid\n", pstruct->counter);
    }
    else
    {
        printf("\n\nThere are %d valid sub-grids, and thus the solution is valid\n", pstruct->counter);
    }
}
