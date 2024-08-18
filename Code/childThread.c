#include <stdio.h>
#include "childThread.h"
#include "struct.h"
#include "misc.h"
#include <unistd.h>


/*This function is used by child thread1 to verify rows 1-3 and subgrids 1-3 of 9x9 suduku solution*/
void* threadOneFunc(void* arg)
{
    int startRow, endRow;
    int startCol, endCol;
    int i;
    int j = 0, k = 0;
    int duplicate = 0;
    int num;

    struct threadData* data = (struct threadData*)arg;
    

    pthread_mutex_lock(&mutex); 

    startRow = data->regions.threadOne[0];
    endRow = data->regions.threadOne[1];
    startCol = data->regions.threadOne[2];
    endCol = data->regions.threadOne[3];

    /* Verify Rows 1-3 */
    for(i=startRow; i<endRow+1; i++) /* Iterate to next row */
    {
       while(j != endCol+1 && duplicate!=1) /* Iterate to next element in row and compare it to every other element in row*/
        { 
            num = data->Sol[i][j];

            while(k!=endCol+1 && duplicate!=1) /* Check if num appears more than once in row */
            {
                if(k != j) /* Compare with every element in row except itself */
                {
                    if(num == data->Sol[i][k]) /* If duplicate exists */
                    {
                        duplicate = 1;
                    }
                }

                k++; /* Check if next element is a duplicate */
            }

            k = startCol; /* Resets column for next element duplicate check in the same row */
            j++; /* Check if next element in row has a duplicate */
        }

        j = startCol; /* Resets column for next row check */

        if(duplicate != 1) /* If row has no duplicate then its valid so express this in the Row array*/
        {
            data->Row[i] = 1;
            data->counter++;
        }

        duplicate = 0; /* Reset duplicate status for next row check */

        
    }

    validifySubs(data, data->regions.threadOne[0], data->regions.threadOne[1], data->regions.threadOne[2], data->regions.threadOne[3], 0);

    sleep(data->delay);

    data->numFinishedThreads++; /* Used to update condition for parent thread to get access to shared data */

    if(data->numFinishedThreads == 4) 
    {
        printf("Thread ID-1 is the last thread.\n");
    }

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex); 

    return NULL;
}

/*This function is used by child thread2 to verify rows 3-6 and subgrids 3-6 of 9x9 suduku solution*/
void* threadTwoFunc(void* arg)
{
    int startRow, endRow;
    int startCol, endCol;
    int i;
    int j = 0, k = 0;
    int duplicate = 0;
    int num;

    struct threadData* data = (struct threadData*)arg;
    
    pthread_mutex_lock(&mutex); 

    startRow = data->regions.threadTwo[0];
    endRow = data->regions.threadTwo[1];
    startCol = data->regions.threadTwo[2];
    endCol = data->regions.threadTwo[3];

    /* Verify Rows 4-6 */
    for(i=startRow; i<endRow+1; i++) /* Iterate to next row */
    {
       while(j != endCol+1 && duplicate!=1) /* Iterate to next element in row and compare it to every other element in row*/
        { 
            num = data->Sol[i][j];

            while(k!=endCol+1 && duplicate!=1) /* Check if num appears more than once in row */
            {
                if(k != j) /* Compare with every element in row except itself */
                {
                    if(num == data->Sol[i][k]) /* If duplicate exists */
                    {
                        duplicate = 1;
                    }
                }

                k++; /* Check if next element is a duplicate */
            }

            k = startCol; /* Resets column for next element duplicate check in the same row */
            j++; /* Check if next element in row has a duplicate */
        }

        j = startCol; /* Resets column for next row check */

        if(duplicate != 1) /* If row has no duplicate then its valid so express this in the Row array*/
        {
            data->Row[i] = 1;
            data->counter++;
        }

        duplicate = 0; /* Reset duplicate status for next row check */
    }

    validifySubs(data, data->regions.threadTwo[0], data->regions.threadTwo[1], data->regions.threadTwo[2], data->regions.threadTwo[3], 3);

    sleep(data->delay);

    data->numFinishedThreads++;

    if(data->numFinishedThreads == 4)
    {
        printf("Thread ID-2 is the last thread.\n");
    }

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex); 

    return NULL;
}

/*This function is used by child thread3 to verify rows 6-9 and subgrids 6-9 of 9x9 suduku solution*/
void* threadThreeFunc(void* arg)
{
    int startRow, endRow;
    int startCol, endCol;
    int i;
    int j = 0, k = 0;
    int duplicate = 0;
    int num;

    struct threadData* data = (struct threadData*)arg;
    
    pthread_mutex_lock(&mutex); 

    startRow = data->regions.threadThree[0];
    endRow = data->regions.threadThree[1];
    startCol = data->regions.threadThree[2];
    endCol = data->regions.threadThree[3];

    /* Verify Rows 7-9 */
    for(i=startRow; i<endRow+1; i++) /* Iterate to next row */
    {
       while(j != endCol+1 && duplicate!=1) /* Iterate to next element in row and compare it to every other element in row*/
        { 
            num = data->Sol[i][j];

            while(k!=endCol+1 && duplicate!=1) /* Check if num appears more than once in row */
            {
                if(k != j) /* Compare with every element in row except itself */
                {
                    if(num == data->Sol[i][k]) /* If duplicate exists */
                    {
                        duplicate = 1;
                    }
                }

                k++; /* Check if next element is a duplicate */
            }

            k = startCol; /* Resets column for next element duplicate check in the same row */
            j++; /* Check if next element in row has a duplicate */
        }

        j = startCol; /* Resets column for next row check */

        if(duplicate != 1) /* If row has no duplicate then its valid so express this in the Row array*/
        {
            data->Row[i] = 1;
            data->counter++;
        }

        duplicate = 0; /* Reset duplicate status for next row check */
    }

    validifySubs(data, data->regions.threadThree[0], data->regions.threadThree[1], data->regions.threadThree[2], data->regions.threadThree[3], 6);
    sleep(data->delay);

    data->numFinishedThreads++;
    if(data->numFinishedThreads == 4)
    {
        printf("Thread ID-3 is the last thread.\n");
    }

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex); 

    return NULL;
}

/*This function is used by child thread4 to verify columns 1-9 of the 9x9 suduku solution*/
void* threadFourFunc(void* arg)
{
    int startRow, endRow;
    int startCol, endCol;
    int i;
    int j = 0, k = 0;
    int duplicate = 0;
    int num;

    struct threadData* data = (struct threadData*)arg;
    
    pthread_mutex_lock(&mutex); 

    startRow = data->regions.threadFour[0];
    endRow = data->regions.threadFour[1];
    startCol = data->regions.threadFour[2];
    endCol = data->regions.threadFour[3];

    /* Verify Columns 1-9 */
    for(i=startCol; i<endCol+1; i++) /* Iterate to next column */
    {
       while(j != endRow+1 && duplicate!=1) /* Iterate to next element in column and compare it to every other element in column*/
        { 
            num = data->Sol[j][i];

            while(k!=endRow+1 && duplicate!=1) /* Check if num appears more than once in column */
            {
                if(k != j) /* Compare with every element in column except itself */
                {
                    if(num == data->Sol[k][i]) /* If duplicate exists */
                    {
                        duplicate = 1;
                    }
                }

                k++; /* Check if next element is a duplicate */
            }

            k = startRow; /* Resets row for next element duplicate check in the same column */
            j++; /* Check if next element in column has a duplicate */
        }

        j = startRow; /* Resets row for next column check */

        if(duplicate != 1) /* If column has no duplicate then its valid so express this in the Col array*/
        {
            data->Col[i] = 1;
            data->counter++;
        }

        duplicate = 0; /* Reset duplicate status for next column check */
    }
    
    sleep(data->delay);

    data->numFinishedThreads++;
    if(data->numFinishedThreads == 4)
    {
        printf("Thread ID-4 is the last thread.\n");
    }

    pthread_cond_signal(&cond);
    pthread_mutex_unlock(&mutex); 

    return NULL;
}


/*This function is used to verify a row of 3x3 subgrids for 9x9 soduku solution*/
void validifySubs(struct threadData* pdata, int startRow, int endRow, int startCol, int endCol, int subIdx)
{
    int row, col, i, j;
    int num;
    int duplicate;
    int compRow, compCol;

    
    for(i = startRow; i < endRow; i += 3) /* go to next row of 3x3 sub grid */
    { 
        for(j = startCol; j < endCol; j += 3) /* go to next column of 3x3 sub grid */
        { 
            duplicate = 0;
            
            for(row = i; row < i + 3; row++) /* go through each index in the current 3x3 subgrid */
            { 
                for(col = j; col < j + 3; col++) 
                {
                    num = pdata->Sol[row][col];
                    
                    for(compRow = i; compRow < i + 3; compRow++) /* Compare the current index with all other indexes in the subgrid */
                    {
                        for(compCol = j; compCol < j + 3; compCol++) 
                        {
                            if(row != compRow || col != compCol) 
                            { 
                                if(num == pdata->Sol[compRow][compCol]) /* if duplicate exists then dont comapre with the rest of the indexes in sub grid*/
                                { 
                                    duplicate = 1;
                                    break; 
                                }
                            }
                        }
                        if(duplicate)
                        { 
                            break;
                        }
                    }
                    if(duplicate)
                    {
                        break;
                    }
                }
                if (duplicate)
                {
                    break;
                }
            }

            if(!duplicate) /* If no duplicate found in the subgrid, mark it as valid */
            { 
                pdata->Sub[subIdx] = 1;
                pdata->counter++;
            }
            subIdx++; /* Move to next sub grid*/
        }
    }
}







